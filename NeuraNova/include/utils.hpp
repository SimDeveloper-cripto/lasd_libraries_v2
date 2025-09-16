#ifndef NEURANOVA_UTILS_HPP
#define NEURANOVA_UTILS_HPP

#include <cmath>
#include <vector>
#include <random>
#include <stdexcept>

// (mean = 0, var = 1)
float randn();

// From (rows x cols) to (cols x rows)
std::vector<float> transpose(const std::vector<float>& A, int rows, int cols);

// Returns vector of size [rowsA * colsB]
std::vector<float> matmul(const std::vector<float>& A, int rowsA, int colsA, const std::vector<float>& B, int rowsB, int colsB);

std::vector<float> sum_rows(const std::vector<float>& A, int rows, int cols);
std::vector<float> add_vectors(const std::vector<float>& A, const std::vector<float>& B);
std::vector<float> mul_vectors(const std::vector<float>& A, const std::vector<float>& B);

#endif // NEURANOVA_UTILS_HPP