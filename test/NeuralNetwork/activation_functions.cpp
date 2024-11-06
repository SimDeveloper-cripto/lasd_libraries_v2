#include "activation_functions.hpp"
#include <cmath>

namespace NNDL_COMPUTE {
    double Sigmoid(double x) { return 1.0 / (1.0 + std::exp(-x)); }

    double Swish(double x) { return x / (1.0 + std::exp(-x)); }

    double ReLU(double x) { return std::max(0.0, x); }

    double ELU(double x, double alpha) { return (x >= 0) ? x : alpha * (std::exp(x) - 1); }

    double SELU(double x, double lambda, double alpha) { return (x >= 0) ? lambda * x : lambda * alpha * (std::exp(x) - 1); }

    double SoftPlus(double x) { return std::log(1.0 + std::exp(x)); }

    /* *** DERIVATIVES *** */
    double SwishDerivative(double x) {
        double sigmoid = 1.0 / (1.0 + std::exp(-x));
        return sigmoid + x * sigmoid * (1 - sigmoid);
    }

    double ReLUDerivative(double x) { return x > 0.0 ? 1.0 : 0.0; }

    double ELUDerivative(double x, double alpha) { return (x >= 0) ? 1.0 : ELU(x, alpha) + alpha; }

    double SELUDerivative(double x, double lambda, double alpha) { return (x >= 0) ? lambda : SELU(x, lambda, alpha) + lambda * alpha; }

    double SoftPlusDerivative(double x) { return 1.0 / (1.0 + std::exp(-x)); }

    // Linear Activation Function
    double LINEAR(double x) { return x; }
}