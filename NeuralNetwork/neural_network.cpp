#include "neural_network.hpp"
#include <utility>

namespace NNDL {
    NeuralNetwork::NeuralNetwork(const std::vector<std::vector<Neuron>>& neurons_per_layer) {
        for (const auto& neurons : neurons_per_layer) {
            layers.emplace_back(Layer(neurons));
        }
    }

    std::vector<double> NeuralNetwork::Forward(const std::vector<double>& input_data) {
        int index = 1;

        std::vector<double> layer_output = input_data;
        for (Layer& layer : layers) {
            std::cout << "\nLayer " << index++ << " inputs: ";
            for (const auto& input : layer_output) { std::cout << input << " "; }

            std::cout << "\nOutputs:" << std::endl;
            layer_output = layer.computeLayerOutput(layer_output);
        }
        return layer_output;
    }
}