#ifndef NEURANOVA_FEEDFORWARD_HPP
#define NEURANOVA_FEEDFORWARD_HPP

#include "../include/layer.hpp"
#include "../include/loss.hpp"
#include "../include/network.hpp"
#include <vector>

class FeedForward : public Network {
public:
  FeedForward(LossFunction *loss_fn);
  ~FeedForward();

  void add_layer(DenseLayer &&layer);

  const std::vector<float> &predict(const std::vector<float> &input_X,
                                    int input_dim, int batch_size) override;

  void train(const std::vector<float> &X, const std::vector<float> &y,
             int input_dim, int num_samples, int epochs,
             const std::vector<float> &X_val, const std::vector<float> &y_val,
             int val_samples, int batch_size) override;

  float getAccuracy(const std::vector<float> &X_test,
                    const std::vector<float> &y_test_onehot, int input_dim,
                    int test_samples) override;

private:
  std::vector<DenseLayer> _layers;
  LossFunction *_lossFn;

  std::vector<DenseLayer::LayerState> _bestWeights;

  float computeValidationLoss(const std::vector<float> &X_val,
                              const std::vector<float> &y_val, int input_dim,
                              int val_samples, int batch_size,
                              std::vector<float> &val_X_batch,
                              std::vector<float> &val_y_batch);
};

#endif // NEURANOVA_FEEDFORWARD_HPP