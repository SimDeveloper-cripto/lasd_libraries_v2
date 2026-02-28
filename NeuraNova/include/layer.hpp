#ifndef NEURANOVA_LAYER_HPP
#define NEURANOVA_LAYER_HPP

#include "../include/activation.hpp"
#include "../include/optimizer.hpp"
#include "../include/utils.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class DenseLayer {
public:
  DenseLayer(int input_dim, int output_dim,
             std::unique_ptr<Activation> activation,
             std::unique_ptr<Optimizer> optimizer);

  // copy const/assign needed due to unique_ptr in FeedForward std::vector
  DenseLayer(const DenseLayer &other);
  DenseLayer &operator=(const DenseLayer &other) = delete;
  DenseLayer(DenseLayer &&) noexcept = default;
  DenseLayer &operator=(DenseLayer &&) noexcept = default;

  struct LayerState {
    std::vector<float> weights;
    std::vector<float> bias;
  };

  LayerState get_weights() const;
  void set_weights(const LayerState &state);

  // Forward
  // input_data size: (input_dim * batch_size)
  // returns a const ref to the internal _output vector
  const std::vector<float> &forward(const std::vector<float> &input_data,
                                    int batch_size);

  // Backward
  // grad_output size: (output_dim * batch_size)
  // returns a const ref to the internal _grad_input vector
  const std::vector<float> &backward(const std::vector<float> &grad_output,
                                     int batch_size);

  int getOutputDim() const { return _outputDim; }

private:
  int _inputDim;
  int _outputDim;

  std::unique_ptr<Activation> _activationFn;
  std::unique_ptr<Optimizer> _optimizer;

  std::vector<float> _weights; // shape (output_dim * input_dim)
  std::vector<float> _bias;    // shape (output_dim)

  // Temporary values kept across forward -> backward
  std::vector<float> _input; // shape (input_dim  * batch_size) stored as copy
                             // (or ref if careful)

  // Pre-allocated buffers to avoid memory allocations during train
  std::vector<float> _output;     // shape (output_dim * batch_size)
  std::vector<float> _grad_z;     // shape (output_dim * batch_size)
  std::vector<float> _grad_input; // shape (input_dim  * batch_size)

  std::vector<float> _W_T;          // shape (input_dim  * output_dim)
  std::vector<float> _input_T;      // shape (batch_size * input_dim)
  std::vector<float> _grad_weights; // shape (output_dim * input_dim)
  std::vector<float> _sum_gb;       // shape (output_dim)

  void initWeightsHe(int input_dim, int output_dim);
  void initWeightsGlorot(int input_dim, int output_dim);
  void reallocateBuffers(int batch_size);
  int _currentBufferSize = 0;
};

#endif // NEURANOVA_LAYER_HPP