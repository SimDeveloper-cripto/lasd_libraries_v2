#pragma once

#include <cmath>

double Sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}