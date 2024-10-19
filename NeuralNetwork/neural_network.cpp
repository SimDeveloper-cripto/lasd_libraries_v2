#include "neural_network.hpp"
#include <utility>

namespace NNDL {
    NeuralNetwork::NeuralNetwork(const std::vector<std::vector<Neuron>>& neurons_per_layer) {
        for (const auto& neurons : neurons_per_layer) {
            layers.emplace_back(Layer(neurons));
        }
    }

    std::vector<std::vector<double>> NeuralNetwork::Forward(const std::vector<std::vector<double>>& input_data) {
        int index = 1;

        std::vector<std::vector<double>> layer_output = input_data;
        for (Layer& layer : layers) {
            std::cout << "\nLayer " << index++ << " Inputs: " << std::endl;
            for (const auto& input_vector : layer_output) {
                for (const auto& input : input_vector) {
                    std::cout << input << " ";
                }
                std::cout << std::endl;
            }

            std::cout << "\nOutputs:" << std::endl;
            layer_output = layer.computeLayerOutput(layer_output);
        }

        // TODO: PROBABILMENTE QUI BISOGNA OTTENERE UN UNICO VALORE BASATO SULL'ULTIMO VETTORE DI OUTPUT
        return layer_output;
    }
}