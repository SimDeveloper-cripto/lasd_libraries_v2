#pragma once

#include <vector>
#include <functional>

namespace NNDL {
    class Neuron {    
        public:
            Neuron(int num_inputs, std::function<double(double)> activation_fn);
            Neuron(const Neuron& neuron);
            Neuron(Neuron&& neuron) noexcept;
            ~Neuron() = default;

            Neuron& operator=(const Neuron& other);
            Neuron& operator=(Neuron&& other) noexcept;
            bool operator==(const Neuron& other) const;
    
            void setValue(double value);
            double getValue() const;

            void setBias(double bias);
            double getBias() const;

            void setWeights(const std::vector<double>& weights);
            std::vector<double>& getWeights();

            void setActivationFunction(std::function<double(double)> activation_fn);
            std::function<double(double)> getActivationFunction() const;

            double Compute(const std::vector<double>& inputs);
        private:
            double bias;                                 // Bias term
            double value;                                // Activation value of the Neuron
            std::vector<double> weights;                 // Weights for the connections
            std::function<double(double)> activation_fn; // Activation Function!
    };
}