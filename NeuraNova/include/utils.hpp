#ifndef NEURANOVA_UTILS_HPP
#define NEURANOVA_UTILS_HPP

#include <cmath>
#include <vector>
#include <random>
#include <stdexcept>

// (mean=0, var=1)
float randn();

// Esegue la moltiplicazione di matrici (A di shape [rowsA, colsA], B di shape [colsA, colsB])
// Restituisce un vettore di size [rowsA * colsB]
std::vector<float> matmul(const std::vector<float>& A, int rowsA, int colsA,
                          const std::vector<float>& B, int rowsB, int colsB);

// Somma vettori: C[i] = A[i] + B[i]
std::vector<float> add_vectors(const std::vector<float>& A,
                               const std::vector<float>& B);

// Element-wise: C[i] = A[i] * B[i]
std::vector<float> mul_vectors(const std::vector<float>& A,
                               const std::vector<float>& B);

// Trasposta di A (rows x cols) => out (cols x rows)
std::vector<float> transpose(const std::vector<float>& A, int rows, int cols);

// Somma su le colonne di una matrice shape (rows, cols) => restituisce shape (rows, 1).
std::vector<float> sum_rows(const std::vector<float>& A, int rows, int cols);

#endif // NEURANOVA_UTILS_HPP