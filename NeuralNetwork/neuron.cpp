#include "neuron.hpp"
#include "activation_functions.hpp"

#include <numeric>
#include <utility>

namespace NNDL {
    Neuron::Neuron(int num_inputs) : bias(0.0), value(0.0), weights(num_inputs) {}
    Neuron::Neuron(const Neuron& neuron) : bias(neuron.bias), value(neuron.value), weights(neuron.weights) {}
    Neuron::Neuron(Neuron&& neuron) noexcept : bias(neuron.bias), value(neuron.value), weights(std::move(neuron.weights)) {
        neuron.value = 0.0;
        neuron.bias  = 0.0;
    }

    Neuron& Neuron::operator=(const Neuron& neuron) {
        if (this != &neuron) {
            value   = neuron.value;
            bias    = neuron.bias;
            weights = neuron.weights;
        }
        return *this;
    }

    Neuron& Neuron::operator=(Neuron&& neuron) noexcept {
        if (this != &neuron) {
            value        = neuron.value;
            bias         = neuron.bias;
            weights      = std::move(neuron.weights);
            neuron.value = 0.0;
            neuron.bias  = 0.0;
        }
        return *this;
    }

    bool Neuron::operator==(const Neuron& other) const {
        return value == other.value && bias == other.bias && weights == other.weights;
    }

    void Neuron::setBias(double b) { bias = b; }
    double Neuron::getBias() const { return bias; }

    void Neuron::setValue(double v) { value = v; }
    double Neuron::getValue() const { return value; }

    void Neuron::setWeights(const std::vector<double>& w) { weights = w; }
    std::vector<double>& Neuron::getWeights() { return weights; }

    double Neuron::Compute(const std::vector<double>& inputs) {
        double sum = std::inner_product(inputs.begin(), inputs.end(), weights.begin(), 0.0) + bias;
        return Sigmoid(sum);
    }
}