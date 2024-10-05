#pragma once

#include "layer.hpp"

#include <vector>
#include <iostream>

/* [DESCRIPTION]
    --> This is the architecture for a MULTI-LAYER NEURAL NETWORK.
    --> To be specific, a FULL-CONNECTED MULTI-LAYER NEURAL NETWORK.

    Structcure (going backwards): NeuralNetwork --> Layer --> Neuron.
    Note: each Neuron's activation function is defined in activation_functions.hpp
*/

namespace NNDL {
    class NeuralNetwork {
    private:
        std::vector<Layer> layers;  // Vector of Layers (each Layer contains a Vector of Neurons!)

    public:
        NeuralNetwork(const std::vector<std::vector<Neuron>>& neurons_per_layer);
        NeuralNetwork(const NeuralNetwork& other);
        NeuralNetwork(NeuralNetwork&& other) noexcept;
        ~NeuralNetwork() = default;

        NeuralNetwork& operator=(const NeuralNetwork& other);
        NeuralNetwork& operator=(NeuralNetwork&& other) noexcept;
        bool operator==(const NeuralNetwork& other) const;

        std::vector<double> Forward(const std::vector<double>& input_data);
        // void Train(const std::vector<std::vector<double>>& training_data, const std::vector<std::vector<double>>& expected_output, double learning_rate, int epochs);
    };
}