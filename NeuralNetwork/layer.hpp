#pragma once

#include "neuron.hpp"
#include <iostream>

namespace NNDL {
   class Layer {
    private:
        std::vector<Neuron> neurons;

    public:
        Layer(const std::vector<Neuron>& custom_neurons);
        Layer(int num_neurons, int num_inputs, std::function<double(double)> activation_fn = nullptr);
        Layer(const Layer& other);
        Layer(Layer&& other) noexcept;
        ~Layer() = default;

        Layer& operator=(const Layer& other);
        Layer& operator=(Layer&& other) noexcept;
        bool operator==(const Layer& other) const;

        void setNeurons(const std::vector<Neuron>& neurons);
        std::vector<Neuron>& getNeurons();
        std::vector<double> computeLayerOutput(const std::vector<double>& inputs);
    };
}