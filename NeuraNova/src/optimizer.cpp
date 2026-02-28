#include "../include/optimizer.hpp"
#include <cmath>

AdamOptimizer::AdamOptimizer(float learning_rate, float beta1, float beta2,
                             float epsilon)
    : _learningRate(learning_rate), _beta1(beta1), _beta2(beta2),
      _epsilon(epsilon), _t(0) {}

void AdamOptimizer::init(int num_weights, int num_bias) {
  _t = 0;
  _m_weights.assign(num_weights, 0.0f);
  _v_weights.assign(num_weights, 0.0f);

  _m_bias.assign(num_bias, 0.0f);
  _v_bias.assign(num_bias, 0.0f);
}

void AdamOptimizer::step(std::vector<float> &weights, std::vector<float> &bias,
                         const std::vector<float> &grad_weights,
                         const std::vector<float> &grad_bias) {
  _t += 1;

  for (size_t i = 0; i < grad_weights.size(); i++) {
    _m_weights[i] = _beta1 * _m_weights[i] + (1.f - _beta1) * grad_weights[i];
    _v_weights[i] = _beta2 * _v_weights[i] +
                    (1.f - _beta2) * grad_weights[i] * grad_weights[i];
  }

  for (size_t i = 0; i < grad_bias.size(); i++) {
    _m_bias[i] = _beta1 * _m_bias[i] + (1.f - _beta1) * grad_bias[i];
    _v_bias[i] =
        _beta2 * _v_bias[i] + (1.f - _beta2) * grad_bias[i] * grad_bias[i];
  }

  float bias_correction1 = 1.f - std::pow(_beta1, float(_t));
  float bias_correction2 = 1.f - std::pow(_beta2, float(_t));

  for (size_t i = 0; i < weights.size(); i++) {
    float m_hat = _m_weights[i] / bias_correction1;
    float v_hat = _v_weights[i] / bias_correction2;
    weights[i] -= _learningRate * m_hat / (std::sqrt(v_hat) + _epsilon);
  }

  for (size_t i = 0; i < bias.size(); i++) {
    float m_hat = _m_bias[i] / bias_correction1;
    float v_hat = _v_bias[i] / bias_correction2;
    bias[i] -= _learningRate * m_hat / (std::sqrt(v_hat) + _epsilon);
  }
}
