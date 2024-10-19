#pragma once

#include "layer.hpp"

#include <vector>
#include <iostream>

/* [DESCRIPTION]
    --> This is the architecture for a MULTI-LAYER NEURAL NETWORK
    --> To be specific, a FULL-CONNECTED MULTI-LAYER NEURAL NETWORK

    Neuron --> Layer --> NeuralNetwork
*/

namespace NNDL {
    class NeuralNetwork {
    private:
        std::vector<Layer> layers;  // Vector of Layers (each Layer contains a Vector of Neurons!)

    public:
        NeuralNetwork(const std::vector<std::vector<Neuron>>& neurons_per_layer);
        std::vector<std::vector<double>> Forward(const std::vector<std::vector<double>>& input_data);
    };
}