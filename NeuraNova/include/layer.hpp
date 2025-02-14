#ifndef NEURANOVA_LAYER_HPP
#define NEURANOVA_LAYER_HPP

#include "../include/utils.hpp"

#include <vector>
#include <string>
#include <cstdint>

/**
 * DenseLayer: (output_dim, input_dim) per weights e (output_dim, 1) per bias
*/
class DenseLayer {
public:
    DenseLayer(int input_dim,
               int output_dim,
               const std::string& activation,
               float learning_rate,
               float beta1,
               float beta2,
               float epsilon);

    struct LayerState {
        std::vector<float> weights;
        std::vector<float> bias;
        std::vector<float> m_weights;
        std::vector<float> v_weights;
        std::vector<float> m_bias;
        std::vector<float> v_bias;
        int t;
    };

    LayerState get_weights() const;
    void set_weights(const LayerState& state);

    // Forward
    // input_data         shape: (input_dim,  batch_size)
    // Restituisce output shape: (output_dim, batch_size)
    std::vector<float> forward(const std::vector<float>& input_data,
                               int batch_size);

    // Backward + Adam
    // grad_output            shape: (output_dim, batch_size)
    // Restituisce grad_input shape: (input_dim,  batch_size)
    std::vector<float> backward(const std::vector<float>& grad_output,
                                int batch_size);

    int getOutputDim() const { return _outputDim; }

private:
    int _inputDim;
    int _outputDim;

    std::string _activation;
    float _learningRate;
    float _beta1;
    float _beta2;
    float _epsilon;
    int _t;

    // Pesi
    std::vector<float> _weights; // shape (output_dim * input_dim)
    std::vector<float> _bias;    // shape (output_dim)

    // Momenti per Adam
    std::vector<float> _m_weights;
    std::vector<float> _v_weights;
    std::vector<float> _m_bias;
    std::vector<float> _v_bias;

    // Cache
    std::vector<float> _input;            // shape (input_dim  * batch_size)
    std::vector<float> _output;           // shape (output_dim * batch_size)
    std::vector<float> _activation_cache; // shape (output_dim * batch_size)

    // Funzioni attivazione
    void reluForward(std::vector<float>& z);
    void reluBackward(std::vector<float>& grad_z, const std::vector<float>& z);

    void sigmoidForward(std::vector<float>& z);
    void sigmoidBackward(std::vector<float>& grad_z, const std::vector<float>& out);

    void identityForward(std::vector<float>& z);
    void identityBackward(std::vector<float>& grad_z);

    // Inizializzatori
    void initWeightsHe(int input_dim, int output_dim);
    void initWeightsGlorot(int input_dim, int output_dim);
};

#endif // NEURANOVA_LAYER_HPP