#include "neural_network.hpp"
#include <utility>

// THIS IMPLEMENTATION IS FOR A FEED-FORWARD MODEL

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
            std::cout << "\nLayer #" << index << " Input Matrix: " << std::endl;
            for (const auto& input_vector : layer_output) {
                std::cout << "[ ";
                for (const auto& input : input_vector) {
                    std::cout << input << " ";
                }
                std::cout << "]" << std::endl;
            }

            // [COMPUTE LAYER OUTPUT]
            std::cout << "\n--> Process of Computation:" << std::endl;
            layer_output = layer.computeLayerOutput(layer_output);

            std::cout << "Layer #" << index << " [WX + B] Output Matrix: " << std::endl;
            for (size_t i = 0; i < layer_output.size(); i++) {
                std::cout << "[ ";
                for (const auto& output : layer_output[i]) {
                    std::cout << output << " ";
                }
                std::cout << "]" << std::endl;
            }

            index++;
        }
        return layer_output;
    }
}