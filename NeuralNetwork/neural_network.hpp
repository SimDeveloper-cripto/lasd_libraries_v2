#pragma once

#include "layer.hpp"
#include <vector>

namespace NNDL {
    class NeuralNetwork {
    private:
        std::vector<Layer> layers;  // Vector of Layers

    public:
        NeuralNetwork(const std::vector<int>& topology); // Example: {3, 4, 2} for a 3-layer NN
        NeuralNetwork(const NeuralNetwork& other);
        NeuralNetwork(NeuralNetwork&& other) noexcept;
        ~NeuralNetwork() = default;

        NeuralNetwork& operator=(const NeuralNetwork& other);
        NeuralNetwork& operator=(NeuralNetwork&& other) noexcept;
        bool operator==(const NeuralNetwork& other) const;

        std::vector<double> Forward(const std::vector<double>& input_data);

/*
        void Train(const std::vector<std::vector<double>>& training_data, 
                const std::vector<std::vector<double>>& expected_output, 
                double learning_rate, int epochs);
*/
    };
}