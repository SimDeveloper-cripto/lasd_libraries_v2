#include "layer.hpp"
#include <utility>

namespace NNDL {
    Layer::Layer(const std::vector<Neuron>& custom_neurons) : neurons(custom_neurons) {}

    void Layer::setNeurons(const std::vector<Neuron>& ns) { neurons = ns; }
    const std::vector<Neuron>& Layer::getNeurons() { return neurons; }

    std::vector<std::vector<double>> Layer::computeLayerOutput(const std::vector<std::vector<double>>& inputs) {
        std::vector<std::vector<double>> layer_outputs;

        std::cout << "W MATRIX: " << std::endl;
        for (Neuron& neuron : neurons) {
            std::cout << "[ ";
            const std::vector<double>& n_w = neuron.getWeights();
            for (const double& w : n_w) {
                std::cout << w << " ";
            }
            std::cout << "]" << std::endl;
        }
        std::cout << std::endl;

        int index = 1;
        for (Neuron& neuron : neurons) {
            layer_outputs.push_back(neuron.Compute(inputs)); // Compute for all inputs!

            std::cout << "Neuron " << index++ << ", Output_Vector { ";
            for (const auto& output : layer_outputs.back()) { std::cout << output << " "; }
            std::cout << "}" << std::endl << std::endl;
        }
        return layer_outputs;
    }
}