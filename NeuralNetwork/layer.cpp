#include "layer.hpp"
#include <utility>

namespace NNDL {
/*
    Layer::Layer(int num_neurons, int num_inputs_per_neuron) {
        for (int i = 0; i < num_neurons; ++i) {
            neurons.emplace_back(Neuron(num_inputs_per_neuron));
        }
    }
*/
    Layer::Layer(const std::vector<Neuron>& custom_neurons) : neurons(custom_neurons) {}
    Layer::Layer(const Layer& layer) : neurons(layer.neurons) {}
    Layer::Layer(Layer&& layer) noexcept : neurons(std::move(layer.neurons)) {}

    Layer& Layer::operator=(const Layer& layer) {
        if (this != &layer) {
            neurons = layer.neurons;
        }
        return *this;
    }

    Layer& Layer::operator=(Layer&& layer) noexcept {
        if (this != &layer) {
            neurons = std::move(layer.neurons);
        }
        return *this;
    }

    bool Layer::operator==(const Layer& layer) const {
        return neurons == layer.neurons;
    }

    void Layer::setNeurons(const std::vector<Neuron>& ns) { neurons = ns; }
    std::vector<Neuron>& Layer::getNeurons() { return neurons; }

    std::vector<double> Layer::computeLayerOutput(const std::vector<double>& inputs) {
        int index = 1;

        std::vector<double> output;
        for (Neuron& neuron : neurons) {
            double ret_val = neuron.Compute(inputs);
            output.push_back(ret_val);

            std::cout << "Neuron " << index++ << " Weights: ";
            for (const auto& weight : neuron.getWeights()) { std::cout << weight << " "; }
            std::cout << " , Bias: " << neuron.getBias() << " , Output: " << ret_val << std::endl;
        }
        return output;
    }
}