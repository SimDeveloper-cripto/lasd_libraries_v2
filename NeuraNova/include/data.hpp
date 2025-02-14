#ifndef NEURANOVA_DATA_HPP
#define NEURANOVA_DATA_HPP

#include <vector>
#include <string>
#include <utility>

/**
 * Carica MNIST
 *  - X_train: shape (train_limit, 28, 28)
 *  - y_train: shape (train_limit)
 *  - X_test : shape (test_limit, 28, 28)
 *  - y_test : shape (test_limit)
*/
std::pair<std::pair<std::vector<uint8_t>, std::vector<uint8_t>>,
          std::pair<std::vector<uint8_t>, std::vector<uint8_t>>>
load_mnist(int train_limit, int test_limit, const std::string& path = "data/MNIST/raw");

#endif // NEURANOVA_DATA_HPP