#ifndef NEURANOVA_NETWORK_HPP
#define NEURANOVA_NETWORK_HPP

#include <vector>

class Network {
public:
    virtual ~Network() = default;

    // Effettua forward su input_X [input_dim * batch_size]
    // Restituisce logits [output_dim * batch_size]
    virtual std::vector<float> predict(const std::vector<float>& input_X,
                                       int input_dim, int batch_size) = 0;

    virtual void train(const std::vector<float>& X, const std::vector<float>& y,
                       int input_dim, int num_samples,
                       int epochs,
                       const std::vector<float>& X_val, const std::vector<float>& y_val,
                       int val_samples,
                       int batch_size) = 0;

    virtual float getAccuracy(const std::vector<float>& X_test,
                              const std::vector<float>& y_test_onehot,
                              int input_dim,
                              int test_samples) = 0;
};

#endif // NEURANOVA_NETWORK_HPP