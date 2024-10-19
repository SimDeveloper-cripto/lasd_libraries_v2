#include "neuron.hpp"

#include <numeric>
#include <utility>
#include <assert.h>

namespace NNDL {
    Neuron::Neuron(int num_inputs, std::function<double(double)> fn) : bias(0.0), weights(num_inputs), activation_fn(fn) {}

    void Neuron::setBias(double b) { bias = b; }
    double Neuron::getBias() const { return bias; }

    void Neuron::setWeights(const std::vector<double>& w) { weights = w; }
    const std::vector<double>& Neuron::getWeights() { return weights; }

    void Neuron::setActivationFunction(std::function<double(double)> fn) { activation_fn = fn; }
    std::function<double(double)> Neuron::getActivationFunction() const { return activation_fn; }

    double Neuron::Compute(const std::vector<double>& inputs) {
        // Weights's vector dimension must be equal to the input dimension!
        assert(weights.size() == inputs.size());

        double sum = bias;
        for (size_t i = 0; i < weights.size(); ++i) { // (# of weights) == (# of inputs)
            sum += weights[i] * inputs[i];
        }
        return activation_fn(sum);
    }
}