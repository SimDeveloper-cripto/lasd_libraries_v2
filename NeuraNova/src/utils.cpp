#include "../include/utils.hpp"
#include <omp.h>
#include <random>
#include <stdexcept>

static std::mt19937 &global_rng() {
  static thread_local std::random_device rd;
  static thread_local std::mt19937 gen(rd());
  return gen;
}

float randn() {
  static thread_local std::normal_distribution<float> dist(0.f, 1.f);
  return dist(global_rng());
}

void matmul(const std::vector<float> &A, int rowsA, int colsA,
            const std::vector<float> &B, int rowsB, int colsB,
            std::vector<float> &out) {
  if (colsA != rowsB) {
    throw std::runtime_error("[ERROR] matmul(): mismatch of dimensions.");
  }

  std::fill(out.begin(), out.begin() + rowsA * colsB, 0.0f);

#pragma omp parallel for
  for (int i = 0; i < rowsA; i++) {
    for (int k = 0; k < colsA; k++) {
      float a = A[i * colsA + k];
      for (int j = 0; j < colsB; j++) {
        out[i * colsB + j] += a * B[k * colsB + j];
      }
    }
  }
}

void add_vectors(const std::vector<float> &A, const std::vector<float> &B,
                 std::vector<float> &out) {
  if (A.size() != B.size()) {
    throw std::runtime_error("[ERROR] add_vectors(): mismatch of dimensions.");
  }

#pragma omp parallel for
  for (size_t i = 0; i < A.size(); i++) {
    out[i] = A[i] + B[i];
  }
}

void mul_vectors(const std::vector<float> &A, const std::vector<float> &B,
                 std::vector<float> &out) {
  if (A.size() != B.size()) {
    throw std::runtime_error("[ERROR] mul_vectors(): mismatch of dimensions.");
  }

#pragma omp parallel for
  for (size_t i = 0; i < A.size(); i++) {
    out[i] = A[i] * B[i];
  }
}

void transpose(const std::vector<float> &A, int rows, int cols,
               std::vector<float> &out) {
#pragma omp parallel for collapse(2)
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      out[c * rows + r] = A[r * cols + c];
    }
  }
}

void sum_rows(const std::vector<float> &A, int rows, int cols,
              std::vector<float> &out) {
#pragma omp parallel for
  for (int r = 0; r < rows; r++) {
    float accum = 0.f;
    for (int c = 0; c < cols; c++) {
      accum += A[r * cols + c];
    }
    out[r] = accum;
  }
}