#include "../include/activation.hpp"
#include <algorithm>
#include <cmath>

// ReLU
void Relu::forward(std::vector<float> &z) {
  for (auto &val : z) {
    val = std::max(0.0f, val);
  }
}

void Relu::backward(std::vector<float> &grad_z, const std::vector<float> &z) {
  for (size_t i = 0; i < grad_z.size(); i++) {
    grad_z[i] = (z[i] > 0.f) ? grad_z[i] : 0.f;
  }
}

// Sigmoid
void Sigmoid::forward(std::vector<float> &z) {
  for (auto &val : z) {
    val = 1.f / (1.f + std::exp(-val));
  }
}

void Sigmoid::backward(std::vector<float> &grad_z,
                       const std::vector<float> &out) {
  for (size_t i = 0; i < grad_z.size(); i++) {
    grad_z[i] *= out[i] * (1.f - out[i]);
  }
}

// Identity
void Identity::forward(std::vector<float> &z) { (void)z; }

void Identity::backward(std::vector<float> &grad_z,
                        const std::vector<float> &out) {
  (void)grad_z;
  (void)out;
}
