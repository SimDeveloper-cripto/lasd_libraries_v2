#include "layer.hpp"

#include <future>
#include <utility>

namespace NNDL {
    std::mutex output_mutex;

    Layer::Layer(const std::vector<Neuron>& custom_neurons) : neurons(custom_neurons) {}

    void Layer::setNeurons(const std::vector<Neuron>& ns) { neurons = ns; }
    const std::vector<Neuron>& Layer::getNeurons() { return neurons; }

    std::vector<std::vector<double>> Layer::computeLayerOutput(const std::vector<std::vector<double>>& inputs) {
        std::vector<std::vector<double>> layer_outputs;
        std::vector<std::future<std::vector<double>>> futures;

        {
            std::lock_guard<std::mutex> lock(output_mutex);
            std::cout << "W MATRIX: " << std::endl;
            for (Neuron& neuron : neurons) {
                std::cout << "[ ";
                const std::vector<double>& n_w = neuron.getWeights();
                for (const double& w : n_w) {
                    std::cout << w << " ";
                }
                std::cout << "]" << std::endl;
            }
            std::cout << std::endl;
        }

        for (Neuron& neuron : neurons) {
            futures.push_back(std::async(std::launch::async, &Neuron::Compute, &neuron, inputs));
        }

        // PARALLEL COMPUTATION OF WX + B OUTPUT MATRIX
        for (auto& future : futures) {
            std::vector<double> neuron_output = future.get();  // Get Thread Result!
            layer_outputs.push_back(neuron_output);
        }
        return layer_outputs;
    }
}