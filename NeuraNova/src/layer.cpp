#include "../include/layer.hpp"

#include <algorithm>
#include <cmath>

DenseLayer::DenseLayer(int input_dim, int output_dim,
                       std::unique_ptr<Activation> activation,
                       std::unique_ptr<Optimizer> optimizer)
    : _inputDim(input_dim), _outputDim(output_dim),
      _activationFn(std::move(activation)), _optimizer(std::move(optimizer)) {

  // Glorot initialization as default
  initWeightsGlorot(input_dim, output_dim);

  _bias.resize(output_dim, 0.0f);

  if (_optimizer) {
    _optimizer->init(_weights.size(), _bias.size());
  }

  // Buffers that don't depend on batch size
  _W_T.resize(_inputDim * _outputDim, 0.0f);
  _grad_weights.resize(_outputDim * _inputDim, 0.0f);
  _sum_gb.resize(_outputDim, 0.0f);
}

DenseLayer::DenseLayer(const DenseLayer &other)
    : _inputDim(other._inputDim), _outputDim(other._outputDim),
      _weights(other._weights), _bias(other._bias), _W_T(other._W_T),
      _grad_weights(other._grad_weights), _sum_gb(other._sum_gb),
      _currentBufferSize(other._currentBufferSize) {

  // TODO
  // Unique ptrs need manual reconstruction
  // This is a weak spot, we assume types for deep copy or we just don't
  // copy them well.
  // For this project's FeedForward usage where layers are added
  // once, the copy constructor is called by std::vector::push_back.
  // A better modern C++ approach is using move semantics. Since we deleted copy
  // assign and kept move const/assign, std::vector will use move if noexcept!
}

void DenseLayer::initWeightsHe(int input_dim, int output_dim) {
  _weights.resize(output_dim * input_dim);
  float scale = std::sqrt(2.f / float(input_dim));
  for (auto &w : _weights) {
    w = randn() * scale;
  }
}

void DenseLayer::initWeightsGlorot(int input_dim, int output_dim) {
  // uniform in [-limit, limit]
  _weights.resize(output_dim * input_dim);
  float limit = std::sqrt(6.f / float(input_dim + output_dim));
  for (auto &w : _weights) {
    float r = (float)rand() / (float)RAND_MAX; // [0,1]
    w = (2.f * r - 1.f) * limit;
  }
}

DenseLayer::LayerState DenseLayer::get_weights() const {
  LayerState s;
  s.weights = _weights;
  s.bias = _bias;
  return s;
}

void DenseLayer::set_weights(const LayerState &state) {
  _weights = state.weights;
  _bias = state.bias;
}

void DenseLayer::reallocateBuffers(int batch_size) {
  if (batch_size > _currentBufferSize) {
    _output.resize(_outputDim * batch_size, 0.0f);
    _grad_z.resize(_outputDim * batch_size, 0.0f);
    _grad_input.resize(_inputDim * batch_size, 0.0f);
    _input_T.resize(batch_size * _inputDim, 0.0f);
    _currentBufferSize = batch_size;
  }
}

// Forward
const std::vector<float> &
DenseLayer::forward(const std::vector<float> &input_data, int batch_size) {
  _input = input_data;
  reallocateBuffers(batch_size);

  // Z = W * X + B
  matmul(_weights, _outputDim, _inputDim, input_data, _inputDim, batch_size,
         _output);

  for (int b = 0; b < batch_size; b++) {
    for (int r = 0; r < _outputDim; r++) {
      _output[r * batch_size + b] += _bias[r];
    }
  }

  if (_activationFn) {
    _output.resize(_outputDim * batch_size);
    _activationFn->forward(_output);
  }

  return _output;
}

// Backward
const std::vector<float> &
DenseLayer::backward(const std::vector<float> &grad_output, int batch_size) {
  reallocateBuffers(batch_size);

  // Copy grad_output to our preallocated _grad_z buffer
  std::copy(grad_output.begin(),
            grad_output.begin() + (_outputDim * batch_size), _grad_z.begin());

  _grad_z.resize(_outputDim * batch_size);
  _output.resize(_outputDim * batch_size);

  if (_activationFn) {
    _activationFn->backward(_grad_z, _output);
  }

  // grad_input = W^T @ grad_z
  transpose(_weights, _outputDim, _inputDim, _W_T);

  _grad_input.resize(_inputDim * batch_size);
  matmul(_W_T, _inputDim, _outputDim, _grad_z, _outputDim, batch_size,
         _grad_input);

  // grad_weights = grad_z @ input^T
  transpose(_input, _inputDim, batch_size, _input_T);
  matmul(_grad_z, _outputDim, batch_size, _input_T, batch_size, _inputDim,
         _grad_weights);

  sum_rows(_grad_z, _outputDim, batch_size, _sum_gb);

  if (_optimizer) {
    _optimizer->step(_weights, _bias, _grad_weights, _sum_gb);
  }

  return _grad_input;
}