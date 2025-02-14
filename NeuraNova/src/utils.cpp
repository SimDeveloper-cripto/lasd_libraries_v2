#include "../include/utils.hpp"

static std::mt19937& global_rng() {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd());
    return gen;
}

float randn() {
    static thread_local std::normal_distribution<float> dist(0.f, 1.f);
    return dist(global_rng());
}

std::vector<float> matmul(const std::vector<float>& A, int rowsA, int colsA,
                          const std::vector<float>& B, int rowsB, int colsB) {
    if (colsA != rowsB) {
        throw std::runtime_error("Dimensioni non compatibili in matmul");
    }

    std::vector<float> C(rowsA * colsB, 0.0f);
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            float sum = 0.f;
            for (int k = 0; k < colsA; k++) {
                sum += A[i * colsA + k] * B[k * colsB + j];
            }
            C[i * colsB + j] = sum;
        }
    }
    return C;
}

std::vector<float> add_vectors(const std::vector<float>& A,
                               const std::vector<float>& B) {
    if (A.size() != B.size()) {
        throw std::runtime_error("Dimensioni non compatibili in add_vectors");
    }

    std::vector<float> C(A.size());
    for (size_t i = 0; i < A.size(); i++) {
        C[i] = A[i] + B[i];
    }
    return C;
}

std::vector<float> mul_vectors(const std::vector<float>& A,
                               const std::vector<float>& B) {
    if (A.size() != B.size()) {
        throw std::runtime_error("Dimensioni non compatibili in mul_vectors");
    }

    std::vector<float> C(A.size());
    for (size_t i = 0; i < A.size(); i++) {
        C[i] = A[i] * B[i];
    }
    return C;
}

std::vector<float> transpose(const std::vector<float>& A, int rows, int cols) {
    std::vector<float> At(cols * rows);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            At[c * rows + r] = A[r * cols + c];
        }
    }
    return At;
}

std::vector<float> sum_rows(const std::vector<float>& A, int rows, int cols) {
    std::vector<float> sums(rows, 0.0f);

    for (int r = 0; r < rows; r++) {
        float accum = 0.f;
        for (int c = 0; c < cols; c++) {
            accum += A[r * cols + c];
        }
        sums[r] = accum;
    }

    // Risultato: shape (rows, 1)
    return sums;
}
