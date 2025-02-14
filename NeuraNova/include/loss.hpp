#ifndef NEURANOVA_LOSS_HPP
#define NEURANOVA_LOSS_HPP

#include <vector>

class LossFunction {
public:
    virtual ~LossFunction() = default;

    // Forward pass: logits shape (output_dim * batch_size), labels shape uguale
    virtual float forward(const std::vector<float>& logits,
                          const std::vector<float>& labels,
                          int output_dim, int batch_size) = 0;

    // Restituisce il gradiente dL/dZ (stessa shape di logits)
    virtual const std::vector<float>& backward() = 0;
};

class SoftmaxCrossEntropy : public LossFunction {
private:
    std::vector<float> _logits;
    std::vector<float> _labels;
    std::vector<float> _dLogits;
    int _outputDim = 0;
    int _batchSize = 0;

public:
    SoftmaxCrossEntropy() = default;
    virtual ~SoftmaxCrossEntropy() = default;

    float forward(const std::vector<float>& logits,
                  const std::vector<float>& labels,
                  int output_dim, int batch_size) override;

    const std::vector<float>& backward() override;
};

#endif // NEURANOVA_LOSS_HPP