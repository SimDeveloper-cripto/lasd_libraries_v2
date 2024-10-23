#pragma once

#include "neuron.hpp"

#include <mutex>
#include <iostream>

namespace NNDL {
   class Layer {
    private:
        std::vector<Neuron> neurons; // R^m [m-dimensional Vector Space]

    public:
        Layer(const std::vector<Neuron>& custom_neurons);

        void setNeurons(const std::vector<Neuron>& neurons);
        const std::vector<Neuron>& getNeurons();

        std::vector<std::vector<double>> computeLayerOutput(const std::vector<std::vector<double>>& inputs);
    };
}