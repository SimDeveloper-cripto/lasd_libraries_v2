#include "../include/loss.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

float SoftmaxCrossEntropy::forward(const std::vector<float> &logits,
                                   const std::vector<float> &labels,
                                   int output_dim, int batch_size) {

  if (logits.size() < (size_t)(output_dim * batch_size) ||
      labels.size() < (size_t)(output_dim * batch_size)) {
    throw std::runtime_error(
        "[ERROR] SoftmaxCrossEntropy(): logits/labels do not correspond.");
  }

  float loss = 0.f;
  _outputDim = output_dim;
  _batchSize = batch_size;
  _logits = logits;
  _labels = labels;
  _dLogits.resize(output_dim * batch_size);

  // batch_size as leading dimension
  for (int b = 0; b < batch_size; b++) {
    float maxLogit = -std::numeric_limits<float>::infinity();
    for (int i = 0; i < output_dim; i++) {
      float val = logits[i * batch_size + b];
      if (val > maxLogit) {
        maxLogit = val;
      }
    }

    float sumExp = 0.f;
    for (int i = 0; i < output_dim; i++) {
      float ex = std::exp(logits[i * batch_size + b] - maxLogit);
      sumExp += ex;
    }

    // Softmax & Cross-Entropy
    for (int i = 0; i < output_dim; i++) {
      float ex = std::exp(logits[i * batch_size + b] - maxLogit);
      float prob = ex / sumExp;

      // labels[i * batch_size + b]: one-hot value
      float lbl = labels[i * batch_size + b];
      if (lbl > 0.f) {
        loss -= lbl * std::log(prob + 1e-15f); // cross-entropy
      }
    }
  }

  loss /= static_cast<float>(batch_size);
  return loss;
}

// dLogits = (softmax(logits) - labels)
// dLogits = prob - labels
const std::vector<float> &SoftmaxCrossEntropy::backward() {
  std::fill(_dLogits.begin(), _dLogits.begin() + (_outputDim * _batchSize),
            0.f);

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

  for (int i = 0; i < _outputDim * _batchSize; i++) {
    _dLogits[i] /= static_cast<float>(_batchSize);
  }
  return _dLogits;
}