#include "neural_network.hpp"
#include <utility>

namespace NNDL {
    NeuralNetwork::NeuralNetwork(const std::vector<int>& topology) {
        for (size_t i = 1; i < topology.size(); ++i) {
            layers.emplace_back(Layer(topology[i], topology[i-1]));
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
        std::vector<double> layer_output = input_data;
        for (Layer& layer : layers) {
            layer_output = layer.computeLayerOutput(layer_output);
        }
        return layer_output;
    }
}