#include "test.hpp"

using namespace NNDL;

namespace nn_lasdtest {
    void run_personal_neural_network_test() {
        std::cout << std::endl << "[ OK ] SHALLOW NETWORK {FULLY-CONNECTED MULTI-LAYER NEURAL NETWORK} TEST STARTED" << std::endl;

        /* ***** CREATION OF A SHALLOW FULLY-CONNECTED NEURAL NETWORK (JUST ONE INTERNAL LAYER) ***** */

        // Creation of Layer #1
        Neuron neuron1(3, NNDL_COMPUTE::Sigmoid); // Sigmoid is a non-linear function
        Neuron neuron2(3, NNDL_COMPUTE::Sigmoid);

        neuron1.setWeights({0.5, -0.6, 0.1});
        neuron1.setBias(0.1);

        neuron2.setWeights({0.3, 0.8, -0.5});
        neuron2.setBias(0.2);

        // Creation of Layer #2
        Neuron neuron3(2, NNDL_COMPUTE::LINEAR);

        neuron3.setWeights({0.7, -0.2});
        neuron3.setBias(0.3);

        // Creation of the Neural Network
        std::vector<std::vector<Neuron>> layers = {
            {neuron1, neuron2},
            {neuron3}
        };
        NeuralNetwork nn(layers);

        // Inputs for Neural Network (Layer #1)
        // First input vector, X1 = (1.0, 2.0, 3.0), is the first column and so on ...
        std::vector<std::vector<double>> inputs = {
            {1.0, 4.0, 7.0},
            {2.0, 5.0, 8.0},
            {3.0, 6.0, 9.0}
        };

        // Compute
        std::vector<std::vector<double>> output = nn.Forward(inputs);
    }
}

int main(int argc, char** argv) {
    nn_lasdtest::run_personal_neural_network_test();
    return 0;
}