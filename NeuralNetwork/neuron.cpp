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

    std::vector<double> Neuron::Compute(const std::vector<std::vector<double>>& inputs) {
        // Weights's vector dimension must be equal to the input dimension!
        assert(weights.size() == inputs.size());

        std::vector<double> outputs(inputs[0].size(), 0.0); // Init of Output vector

        std::cout << "  Weights: { ";
        for (const auto& w : weights) {
            std::cout << w << " ";
        } std::cout << "}" << std::endl << std::endl;

        // Compute [WX + B] for each input vector
        for (size_t j = 0; j < inputs[0].size(); ++j) {
            double sum = bias;
            std::cout << "      Input Vector: { ";
            for (size_t i = 0; i < weights.size(); ++i) {
                std::cout << inputs[i][j] << " ";
                sum += weights[i] * inputs[i][j];    
            }
            std::cout << "}" << std::endl;
            std::cout << "      WX (Before Activation): " << sum << std::endl << std::endl;
            outputs[j] = activation_fn(sum);
        }
        return outputs;
    }
}