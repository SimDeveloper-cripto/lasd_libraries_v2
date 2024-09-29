#include "neural_network.hpp"
#include <utility>

namespace NNDL {
/*
    NeuralNetwork::NeuralNetwork(const std::vector<int>& topology) {
        for (size_t i = 1; i < topology.size(); ++i) {
            layers.emplace_back(Layer(topology[i], topology[i-1]));
            // topology[i]:      # of inputs for that neuron
            // topology[i - 1]:  # of neurons
        }
    }
*/
    NeuralNetwork::NeuralNetwork(const std::vector<std::vector<Neuron>>& neurons_per_layer) {
        for (const auto& neurons : neurons_per_layer) {
            layers.emplace_back(Layer(neurons));
        }
    }

    NeuralNetwork::NeuralNetwork(const NeuralNetwork& other) : layers(other.layers) {}
    NeuralNetwork::NeuralNetwork(NeuralNetwork&& other) noexcept : layers(std::move(other.layers)) {}

    NeuralNetwork& NeuralNetwork::operator=(const NeuralNetwork& nn) {
        if (this != &nn) {
            layers = nn.layers;
        }
        return *this;
    }

    NeuralNetwork& NeuralNetwork::operator=(NeuralNetwork&& nn) noexcept {
        if (this != &nn) {
            layers = std::move(nn.layers);
        }
        return *this;
    }

    bool NeuralNetwork::operator==(const NeuralNetwork& nn) const {
        return layers == nn.layers;
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