#include "layer.hpp"
#include <utility>

namespace NNDL {
    Layer::Layer(int num_neurons, int num_inputs_per_neuron) {
        for (int i = 0; i < num_neurons; ++i) {
            neurons.emplace_back(Neuron(num_inputs_per_neuron));
        }
    }

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

    std::vector<Neuron>& Layer::getNeurons() { return neurons; }

    std::vector<double> Layer::computeLayerOutput(const std::vector<double>& inputs) {
        std::vector<double> output;
        for (Neuron& neuron : neurons) {
            output.push_back(neuron.Compute(inputs));
        }
        return output;
    }
}