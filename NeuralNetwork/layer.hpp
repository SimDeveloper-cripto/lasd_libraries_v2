#pragma once

#include "neuron.hpp"

namespace NNDL {
   class Layer {
    private:
        std::vector<Neuron> neurons;

    public:
        Layer(int num_neurons, int num_inputs_per_neuron);
        Layer(const Layer& other);
        Layer(Layer&& other) noexcept;
        ~Layer() = default;

        Layer& operator=(const Layer& other);
        Layer& operator=(Layer&& other) noexcept;
        bool operator==(const Layer& other) const;

        std::vector<Neuron>& getNeurons();
        std::vector<double> computeLayerOutput(const std::vector<double>& inputs);
    };
}