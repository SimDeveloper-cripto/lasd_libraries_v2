#include "../include/feedforward.hpp"

#include <cmath>
#include <limits>
#include <random>
#include <iostream>
#include <algorithm>

FeedForward::FeedForward(LossFunction* loss_fn) : _lossFn(loss_fn) {}

FeedForward::~FeedForward() {}

void FeedForward::add_layer(const DenseLayer& layer) {
    _layers.push_back(layer);
}

std::vector<float> FeedForward::predict(const std::vector<float>& input_X,
                                        int input_dim, int batch_size) {
    std::vector<float> output = input_X;
    int current_dim = input_dim;

    for (auto& layer : _layers) {
        output = layer.forward(output, batch_size);
        current_dim = layer.getOutputDim();
    }
    return output; // shape: (current_dim * batch_size)
}

void FeedForward::train(const std::vector<float>& X, const std::vector<float>& y,
                        int input_dim, int num_samples,
                        int epochs,
                        const std::vector<float>& X_val, const std::vector<float>& y_val,
                        int val_samples,
                        int batch_size) {
    float best_val_loss    = std::numeric_limits<float>::infinity();
    int stopping_counter   = 0;
    int stopping_criterion = 10;

    _bestWeights.clear();
    for (auto& layer : _layers) {
        _bestWeights.push_back(layer.get_weights());
    }

    std::vector<int> indices(num_samples);
    for (int i = 0; i < num_samples; i++) {
        indices[i] = i;
    }

    for (int epoch = 1; epoch <= epochs; epoch++) {
        std::shuffle(indices.begin(), indices.end(), std::mt19937{std::random_device{}()});

        // Mini-batch
        float epoch_loss = 0.f;
        for (int start = 0; start < num_samples; start += batch_size) {
            int end = std::min(start + batch_size, num_samples);
            int current_batch_size = end - start;

            // Preparo i batch X_batch, y_batch
            // shape: X_batch => (input_dim,  current_batch_size)
            //        y_batch => (output_dim, current_batch_size)
            std::vector<float> X_batch(input_dim * current_batch_size);
            std::vector<float> y_batch(_layers.back().getOutputDim() * current_batch_size);

            for (int b = 0; b < current_batch_size; b++) {
                int idx = indices[start + b];

                for (int d = 0; d < input_dim; d++) {
                    X_batch[d * current_batch_size + b] = X[d * num_samples + idx];
                }

                int output_dim = _layers.back().getOutputDim();
                for (int od = 0; od < output_dim; od++) {
                    y_batch[od * current_batch_size + b] = y[od * num_samples + idx];
                }
            }

            // Forward
            auto logits = predict(X_batch, input_dim, current_batch_size);

            // Loss
            float loss = _lossFn->forward(logits, y_batch,
                                          _layers.back().getOutputDim(),
                                          current_batch_size);
            epoch_loss += loss * current_batch_size;

            // Backward
            const auto& grad = _lossFn->backward();
            auto grad_back = grad;

            // BackPropagation
            for (int i = (int)_layers.size() - 1; i >= 0; i--) {
                grad_back = _layers[i].backward(grad_back, current_batch_size);
            }
        }

        epoch_loss /= float(num_samples);
        float val_loss = computeValidationLoss(X_val, y_val, input_dim, val_samples, batch_size);

        std::cout << "epoch " << epoch << "/" << epochs
                  << ", train_loss: " << epoch_loss
                  << " val_loss: " << val_loss << std::endl;

        // Early stopping
        if (val_loss < best_val_loss) {
            best_val_loss    = val_loss;
            stopping_counter = 0;

            _bestWeights.clear();
            for (auto& layer : _layers) {
                _bestWeights.push_back(layer.get_weights());
            }
        } else {
            stopping_counter++;
        }

        if (stopping_counter >= stopping_criterion) {
            std::cout << "Early stopping at epoch " << epoch << std::endl;
            break;
        }
    }

    for (size_t i = 0; i < _layers.size(); i++) {
        _layers[i].set_weights(_bestWeights[i]);
    }
}

float FeedForward::getAccuracy(const std::vector<float>& X_test,
                               const std::vector<float>& y_test_onehot,
                               int input_dim,
                               int test_samples) {
    // Forward
    int batch_size = test_samples;
    auto logits    = predict(X_test, input_dim, batch_size);

    int output_dim = _layers.back().getOutputDim();
    int correct = 0;
    for (int b = 0; b < test_samples; b++) {
        float max_logit  = -99999999.f;
        int   pred_class = -1;

        float max_label  = -99999999.f;
        int   true_class = -1;

        for (int od = 0; od < output_dim; od++) {
            float l = logits[od * test_samples + b];
            if (l > max_logit) {
                max_logit = l;
                pred_class = od;
            }

            float t = y_test_onehot[od * test_samples + b];
            if (t > max_label) {
                max_label = t;
                true_class = od;
            }
        }
        if (pred_class == true_class) {
            correct++;
        }
    }
    float acc = float(correct) / float(test_samples);
    return acc;
}

float FeedForward::computeValidationLoss(const std::vector<float>& X_val,
                                         const std::vector<float>& y_val,
                                         int input_dim,
                                         int val_samples,
                                         int batch_size) {
    // Forward su X_val a batch
    float total_loss = 0.f;
    int output_dim   = _layers.back().getOutputDim();

    for (int start = 0; start < val_samples; start += batch_size) {
        int end = std::min(start + batch_size, val_samples);
        int current_batch_size = end - start;

        std::vector<float> X_batch(input_dim * current_batch_size);
        std::vector<float> y_batch(output_dim * current_batch_size);

        for (int b = 0; b < current_batch_size; b++) {
            int idx = start + b;
            for (int d = 0; d < input_dim; d++) {
                X_batch[d * current_batch_size + b] = X_val[d * val_samples + idx];
            }
            for (int od = 0; od < output_dim; od++) {
                y_batch[od * current_batch_size + b] = y_val[od * val_samples + idx];
            }
        }

        auto logits = predict(X_batch, input_dim, current_batch_size);
        float loss  = _lossFn->forward(logits, y_batch, output_dim, current_batch_size);
        total_loss  += loss * current_batch_size;
    }

    total_loss /= float(val_samples);
    return total_loss;
}