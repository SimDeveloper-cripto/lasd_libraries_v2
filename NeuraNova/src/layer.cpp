#include "../include/layer.hpp"

#include <cmath>
#include <stdexcept>
#include <algorithm>

DenseLayer::DenseLayer(int input_dim,
                       int output_dim,
                       const std::string& activation,
                       float learning_rate,
                       float beta1,
                       float beta2,
                       float epsilon)
    : _inputDim(input_dim), _outputDim(output_dim),
      _activation(activation),
      _learningRate(learning_rate),
      _beta1(beta1), _beta2(beta2), _epsilon(epsilon),
      _t(0)
{
    if (activation == "relu") {
        initWeightsHe(input_dim, output_dim);
    } else {
        initWeightsGlorot(input_dim, output_dim);
    }

    _bias.resize(output_dim, 0.0f);

    _m_weights.resize(_weights.size(), 0.0f);
    _v_weights.resize(_weights.size(), 0.0f);
    _m_bias.resize(_bias.size(), 0.0f);
    _v_bias.resize(_bias.size(), 0.0f);
}

void DenseLayer::initWeightsHe(int input_dim, int output_dim) {
    _weights.resize(output_dim * input_dim);
    float scale = std::sqrt(2.f / float(input_dim));
    for (auto &w : _weights) {
        w = randn() * scale;
    }
}

void DenseLayer::initWeightsGlorot(int input_dim, int output_dim) {
    _weights.resize(output_dim * input_dim);
    float limit = std::sqrt(6.f / float(input_dim + output_dim));
    for (auto &w : _weights) {
        // uniform in [-limit, limit]
        float r = (float)rand() / (float)RAND_MAX; // [0,1]
        w = (2.f * r - 1.f) * limit;
    }
}

DenseLayer::LayerState DenseLayer::get_weights() const {
    LayerState s;
    s.weights    = _weights;
    s.bias       = _bias;
    s.m_weights  = _m_weights;
    s.v_weights  = _v_weights;
    s.m_bias     = _m_bias;
    s.v_bias     = _v_bias;
    s.t          = _t;
    return s;
}

void DenseLayer::set_weights(const LayerState& state) {
    _weights   = state.weights;
    _bias      = state.bias;
    _m_weights = state.m_weights;
    _v_weights = state.v_weights;
    _m_bias    = state.m_bias;
    _v_bias    = state.v_bias;
    _t         = state.t;
}

void DenseLayer::reluForward(std::vector<float>& z) {
    for (auto& val : z) {
        val = std::max(0.0f, val);
    }
}

void DenseLayer::sigmoidForward(std::vector<float>& z) {
    for (auto& val : z) {
        val = 1.f / (1.f + std::exp(-val));
    }
}

void DenseLayer::identityForward(std::vector<float>& z) {}

void DenseLayer::reluBackward(std::vector<float>& grad_z, const std::vector<float>& z) {
    // grad_z[i] *= (z[i] > 0)
    for (size_t i = 0; i < grad_z.size(); i++) {
        grad_z[i] = (z[i] > 0.f) ? grad_z[i] : 0.f;
    }
}

void DenseLayer::sigmoidBackward(std::vector<float>& grad_z, const std::vector<float>& out) {
    // grad_z[i] *= out[i] * (1 - out[i])
    for (size_t i = 0; i < grad_z.size(); i++) {
        grad_z[i] *= out[i] * (1.f - out[i]);
    }
}

void DenseLayer::identityBackward(std::vector<float>& grad_z) {}

// Forward
std::vector<float> DenseLayer::forward(const std::vector<float>& input_data,
                                       int batch_size) {
    _input = input_data; // shape (inputDim * batch_size)

    // Z = W * X + B
    // W shape: (outputDim, inputDim)
    // X shape: (inputDim,  batch_size)
    // Z shape: (outputDim, batch_size)
    auto Z = matmul(_weights, _outputDim, _inputDim,
                    input_data, _inputDim, batch_size);

    for (int b = 0; b < batch_size; b++) {
        for (int r = 0; r < _outputDim; r++) {
            Z[r * batch_size + b] += _bias[r];
        }
    }

    if (_activation == "relu") {
        reluForward(Z);
    } else if (_activation == "sigmoid") {
        sigmoidForward(Z);
    } else if (_activation == "identity") {
        identityForward(Z);
    } else {
        throw std::runtime_error("Unsupported activation: " + _activation);
    }

    _output = Z;
    return _output;
}

// Backward
std::vector<float> DenseLayer::backward(const std::vector<float>& grad_output,
                                        int batch_size) {
    // grad_output shape: (outputDim, batch_size)
    _t += 1;

    std::vector<float> grad_z = grad_output;

    if (_activation == "relu") { 
        reluBackward(grad_z, _output);
    } else if (_activation == "sigmoid") {
        sigmoidBackward(grad_z, _output);
    } else if (_activation == "identity") {
        identityBackward(grad_z);
    }

    // grad_input = W^T @ grad_z
    // W          shape: (outputDim, inputDim)
    // grad_z     shape: (outputDim, batch_size)
    // grad_input shape: (inputDim,  batch_size)

    // Per matmul vogliamo W^T shape: (inputDim, outputDim)
    auto W_T = transpose(_weights, _outputDim, _inputDim);
    auto grad_input = matmul(W_T, _inputDim, _outputDim,
                             grad_z, _outputDim, batch_size);

    // grad_weights = grad_z @ input^T
    // grad_z  shape: (outputDim, batch_size)
    // input^T shape: (batch_size, inputDim)
    // => (outputDim, inputDim)
    auto input_T = transpose(_input, _inputDim, batch_size);
    auto grad_weights = matmul(grad_z, _outputDim, batch_size,
                               input_T, batch_size, _inputDim);

    auto sum_gb = sum_rows(grad_z, _outputDim, batch_size);

    // ADAM
    for (size_t i = 0; i < grad_weights.size(); i++) {
        _m_weights[i] = _beta1 * _m_weights[i] + (1.f - _beta1) * grad_weights[i];
        _v_weights[i] = _beta2 * _v_weights[i] + (1.f - _beta2) * grad_weights[i] * grad_weights[i];
    }

    for (size_t i = 0; i < sum_gb.size(); i++) {
        _m_bias[i] = _beta1 * _m_bias[i] + (1.f - _beta1) * sum_gb[i];
        _v_bias[i] = _beta2 * _v_bias[i] + (1.f - _beta2) * sum_gb[i] * sum_gb[i];
    }

    float bias_correction1 = 1.f - std::pow(_beta1, float(_t));
    float bias_correction2 = 1.f - std::pow(_beta2, float(_t));

    for (size_t i = 0; i < _weights.size(); i++) {
        float m_hat = _m_weights[i] / bias_correction1;
        float v_hat = _v_weights[i] / bias_correction2;
        _weights[i] -= _learningRate * m_hat / (std::sqrt(v_hat) + _epsilon);
    }

    for (int i = 0; i < _outputDim; i++) {
        float m_hat = _m_bias[i] / bias_correction1;
        float v_hat = _v_bias[i] / bias_correction2;
        _bias[i] -= _learningRate * m_hat / (std::sqrt(v_hat) + _epsilon);
    }

    return grad_input;
}
