#pragma once

namespace NNDL_COMPUTE {
    double Sigmoid(double x);
    double Swish(double x);
    double ReLU(double x);
    double ELU(double x, double alpha = 1.0);
    double SELU(double x, double lambda = 1.0507, double alpha = 1.67326);
    double SoftPlus(double x);

    /* *** DERIVATIVES *** */
    double SwishDerivative(double x);
    double ReLUDerivative(double x);
    double ELUDerivative(double x, double alpha = 1.0);
    double SELUDerivative(double x, double lambda = 1.0507, double alpha = 1.67326);
    double SoftPlusDerivative(double x);
}