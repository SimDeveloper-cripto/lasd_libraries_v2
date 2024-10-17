#include "neuron.hpp"

#include <numeric>
#include <utility>
#include <assert.h>

namespace NNDL {
    Neuron::Neuron(int num_inputs, std::function<double(double)> fn)
        : bias(0.0), value(0.0), weights(num_inputs), activation_fn(fn) {}

    Neuron::Neuron(const Neuron& neuron)
        : bias(neuron.bias), value(neuron.value), weights(neuron.weights), activation_fn(neuron.activation_fn) {}
    Neuron::Neuron(Neuron&& neuron) noexcept : bias(neuron.bias), value(neuron.value), weights(std::move(neuron.weights)) {
        neuron.value  = 0.0;
        neuron.bias   = 0.0;
        activation_fn = neuron.activation_fn;
    }

    Neuron& Neuron::operator=(const Neuron& neuron) {
        if (this != &neuron) {
            value         = neuron.value;
            bias          = neuron.bias;
            weights       = neuron.weights;
            activation_fn = neuron.activation_fn;
        }
        return *this;
    }

    Neuron& Neuron::operator=(Neuron&& neuron) noexcept {
        if (this != &neuron) {
            value         = neuron.value;
            bias          = neuron.bias;
            weights       = std::move(neuron.weights);
            activation_fn = neuron.activation_fn;
            neuron.value  = 0.0;
            neuron.bias   = 0.0;
        }
        return *this;
    }

    bool Neuron::operator==(const Neuron& other) const {
        return value == other.value && bias == other.bias && weights == other.weights
            && (activation_fn.target<double(*)(double)>()) == other.activation_fn.target<double(*)(double)>();
    }

    void Neuron::setBias(double b) { bias = b; }
    double Neuron::getBias() const { return bias; }

    void Neuron::setValue(double v) { value = v; }
    double Neuron::getValue() const { return value; }

    void Neuron::setWeights(const std::vector<double>& w) { weights = w; }
    std::vector<double>& Neuron::getWeights() { return weights; }

    void Neuron::setActivationFunction(std::function<double(double)> fn) { activation_fn = fn; }
    std::function<double(double)> Neuron::getActivationFunction() const { return activation_fn; }

    double Neuron::Compute(const std::vector<double>& inputs) {
        assert(inputs.size() == weights.size());

        double sum = bias;
        for (size_t i = 0; i < weights.size(); ++i) { // (# of weights) == (# of inputs)
            sum += weights[i] * inputs[i];
        }
        
        double ret_val = activation_fn(sum);
        setValue(ret_val);
        return ret_val;
    }
}