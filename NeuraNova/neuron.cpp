#include "neuron.hpp"

#include <numeric>
#include <utility>
#include <assert.h>

namespace NNDL {
    std::mutex out_mutex;

    Neuron::Neuron(int num_inputs, std::function<double(double)> fn) : bias(0.0), weights(num_inputs), activation_fn(fn) {}

    void Neuron::setBias(double b) { bias = b; }
    double Neuron::getBias() const { return bias; }

    void Neuron::setWeights(const std::vector<double>& w) { weights = w; }
    const std::vector<double>& Neuron::getWeights() { return weights; }

    void Neuron::setActivationFunction(std::function<double(double)> fn) { activation_fn = fn; }
    std::function<double(double)> Neuron::getActivationFunction() const { return activation_fn; }

    std::vector<double> Neuron::Compute(const std::vector<std::vector<double>>& inputs) {
        // [NOTES]
        // - [APPLY CONSTRAINT] WX can evaluated if, and only if, the number of columns of W (vector weights) corresponds to the number of rows of X (inputs matrix)
        assert(weights.size() == inputs.size() && "[ERROR] Weights vector size must match the number of rows in the inputs matrix.");
        std::vector<double> outputs(inputs[0].size(), 0.0); // Init of Output vector

        {
            std::lock_guard<std::mutex> lock(out_mutex);
            std::cout << "  Weights Row Vector: { ";
            for (const auto& w : weights) {
                std::cout << w << " ";
            } std::cout << "}" << std::endl;
        }

        // Compute [WX + B] [XW^T + B]
        // TODO: CHECK #1: Do I need to Transpose W matrix?
        for (size_t j = 0; j < inputs[0].size(); ++j) {
            double sum = bias;
            {
                std::lock_guard<std::mutex> lock(out_mutex);
                std::cout << "      Input Column Vector: { ";
                for (size_t i = 0; i < weights.size(); ++i) {
                    std::cout << inputs[i][j] << " ";
                    sum += weights[i] * inputs[i][j];    
                }
                std::cout << "}" << std::endl;
                std::cout << "      WX (Before Applying Activation Function): " << sum << std::endl << std::endl;
            }
            outputs[j] = activation_fn(sum); // Call the Activation Function!
        }

        {
            std::lock_guard<std::mutex> lock(out_mutex);
            std::cout << "Neuron Output_Vector { ";
            for (const auto& output : outputs) {
                std::cout << output << " ";
            }
            std::cout << "}\n\n";
        }

        return outputs;
    }
}