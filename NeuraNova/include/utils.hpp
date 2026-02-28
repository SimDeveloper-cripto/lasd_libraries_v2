#ifndef NEURANOVA_UTILS_HPP
#define NEURANOVA_UTILS_HPP

#include <cmath>
#include <vector>

// (mean = 0, var = 1)
float randn();

// From (rows x cols) to (cols x rows)
void transpose(const std::vector<float> &A, int rows, int cols,
               std::vector<float> &out);

// Returns vector of size [rowsA * colsB]
void matmul(const std::vector<float> &A, int rowsA, int colsA,
            const std::vector<float> &B, int rowsB, int colsB,
            std::vector<float> &out);

void sum_rows(const std::vector<float> &A, int rows, int cols,
              std::vector<float> &out);
void add_vectors(const std::vector<float> &A, const std::vector<float> &B,
                 std::vector<float> &out);
void mul_vectors(const std::vector<float> &A, const std::vector<float> &B,
                 std::vector<float> &out);

#endif // NEURANOVA_UTILS_HPP