#include "../include/loss.hpp"

#include <cmath>
#include <limits>
#include <algorithm>
#include <stdexcept>

float SoftmaxCrossEntropy::forward(const std::vector<float>& logits,
                                   const std::vector<float>& labels,
                                   int output_dim, int batch_size) {
    if (logits.size() != labels.size()) {
        throw std::runtime_error("Dimensioni logits/labels non corrispondono in SoftmaxCrossEntropy");
    }

    _outputDim = output_dim;
    _batchSize = batch_size;
    _logits = logits;
    _labels = labels;
    _dLogits.resize(logits.size());

    float loss = 0.f;

    for (int b = 0; b < batch_size; b++) {
        float maxLogit = -std::numeric_limits<float>::infinity();
        for (int i = 0; i < output_dim; i++) {
            float val = logits[i * batch_size + b];
            if (val > maxLogit) {
                maxLogit = val;
            }
        }

        // Calcola la somma di exp(logit - maxLogit)
        float sumExp = 0.f;
        for (int i = 0; i < output_dim; i++) {
            float ex = std::exp(logits[i * batch_size + b] - maxLogit);
            sumExp += ex;
        }

        // Calcola softmax e cross-entropy
        for (int i = 0; i < output_dim; i++) {
            float ex = std::exp(logits[i * batch_size + b] - maxLogit);
            float prob = ex / sumExp;

            // labels[i * batch_size + b] => valore one-hot
            float lbl = labels[i * batch_size + b];
            if (lbl > 0.f) {
                loss -= lbl * std::log(prob + 1e-15f); // cross-entropy
            }
        }
    }

    loss /= static_cast<float>(batch_size);
    return loss;
}

// Per la softmax cross-entropy, dLogits = (softmax(logits) - labels)
const std::vector<float>& SoftmaxCrossEntropy::backward() {
    // dLogits = prob - labels
    std::fill(_dLogits.begin(), _dLogits.end(), 0.f);

    for (int b = 0; b < _batchSize; b++) {
        float maxLogit = -std::numeric_limits<float>::infinity();
        for (int i = 0; i < _outputDim; i++) {
            float val = _logits[i * _batchSize + b];
            if (val > maxLogit) {
                maxLogit = val;
            }
        }

        float sumExp = 0.f;
        for (int i = 0; i < _outputDim; i++) {
            sumExp += std::exp(_logits[i * _batchSize + b] - maxLogit);
        }
        for (int i = 0; i < _outputDim; i++) {
            float ex = std::exp(_logits[i * _batchSize + b] - maxLogit);
            float prob = ex / sumExp;
            _dLogits[i * _batchSize + b] = (prob - _labels[i * _batchSize + b]);
        }
    }

    for (auto &v : _dLogits) {
        v /= static_cast<float>(_batchSize);
    }
    return _dLogits;
}
