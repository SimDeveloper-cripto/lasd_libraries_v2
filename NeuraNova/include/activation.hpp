#ifndef NEURANOVA_ACTIVATION_HPP
#define NEURANOVA_ACTIVATION_HPP

#include <vector>

class Activation {
public:
  virtual ~Activation() = default;

  virtual void forward(std::vector<float> &z) = 0;

  virtual void backward(std::vector<float> &grad_z,
                        const std::vector<float> &out) = 0;
};

class Relu : public Activation {
public:
  void forward(std::vector<float> &z) override;
  void backward(std::vector<float> &grad_z, const std::vector<float> &z)
      override; // using z as out here since relu doesn't depend on out in our
                // prev impl
};

class Sigmoid : public Activation {
public:
  void forward(std::vector<float> &z) override;
  void backward(std::vector<float> &grad_z,
                const std::vector<float> &out) override;
};

class Identity : public Activation {
public:
  void forward(std::vector<float> &z) override;
  void backward(std::vector<float> &grad_z,
                const std::vector<float> &out) override;
};

#endif // NEURANOVA_ACTIVATION_HPP
