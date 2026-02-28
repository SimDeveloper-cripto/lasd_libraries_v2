#ifndef NEURANOVA_OPTIMIZER_HPP
#define NEURANOVA_OPTIMIZER_HPP

#include <vector>

class Optimizer {
public:
  virtual ~Optimizer() = default;

  virtual void init(int num_weights, int num_bias) = 0;

  virtual void step(std::vector<float> &weights, std::vector<float> &bias,
                    const std::vector<float> &grad_weights,
                    const std::vector<float> &grad_bias) = 0;
};

class AdamOptimizer : public Optimizer {
public:
  AdamOptimizer(float learning_rate = 0.001f, float beta1 = 0.9f,
                float beta2 = 0.999f, float epsilon = 1e-8f);

  void init(int num_weights, int num_bias) override;

  void step(std::vector<float> &weights, std::vector<float> &bias,
            const std::vector<float> &grad_weights,
            const std::vector<float> &grad_bias) override;

private:
  float _learningRate;
  float _beta1;
  float _beta2;
  float _epsilon;
  int _t;

  std::vector<float> _m_weights;
  std::vector<float> _v_weights;
  std::vector<float> _m_bias;
  std::vector<float> _v_bias;
};

#endif // NEURANOVA_OPTIMIZER_HPP
