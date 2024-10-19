#pragma once

#include <vector>
#include <iostream>
#include <functional>

namespace NNDL {
    class Neuron {
        public:
            Neuron(int num_inputs, std::function<double(double)> activation_fn);

            void setBias(double bias);
            double getBias() const;

            void setWeights(const std::vector<double>& weights);
            const std::vector<double>& getWeights();

            void setActivationFunction(std::function<double(double)> activation_fn);
            std::function<double(double)> getActivationFunction() const;

            std::vector<double> Compute(const std::vector<std::vector<double>>& inputs);
        private:
            double bias;                                 // Bias term
            std::vector<double> weights;                 // Weights for the connections
            std::function<double(double)> activation_fn; // Activation Function!
    };
}