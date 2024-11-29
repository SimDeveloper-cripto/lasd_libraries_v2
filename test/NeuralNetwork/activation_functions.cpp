#include "activation_functions.hpp"
#include <cmath>

namespace NNDL_COMPUTE {
    double Sigmoid(double x) { return 1.0 / (1.0 + std::exp(-x)); }

    double ReLU(double x) { return std::max(0.0, x); }

    /* *** DERIVATIVES *** */

    double ReLU_D(double x) { return x > 0.0 ? 1.0 : 0.0; }

    // Linear Activation Function
    double LINEAR(double x) { return x; }
}