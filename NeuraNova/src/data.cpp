#include "../include/data.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <cstdint>
#include <algorithm>
#include <stdexcept>

static std::vector<uint8_t> load_images(const std::string& filename, int& total, int& rows, int& cols) {
    std::ifstream in(filename, std::ios::binary);
    if(!in) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    int32_t magic = 0;
    in.read(reinterpret_cast<char*>(&magic), 4);
    magic = __builtin_bswap32(magic);

    if(magic != 2051) {
        throw std::runtime_error("Magic number mismatch in " + filename);
    }
    int32_t n_images = 0;
    in.read(reinterpret_cast<char*>(&n_images), 4);
    n_images = __builtin_bswap32(n_images);

    int32_t r = 0;
    in.read(reinterpret_cast<char*>(&r), 4);
    r = __builtin_bswap32(r);

    int32_t c = 0;
    in.read(reinterpret_cast<char*>(&c), 4);
    c = __builtin_bswap32(c);

    total = n_images;
    rows = r;
    cols = c;

    std::vector<uint8_t> images(n_images * r * c);
    in.read(reinterpret_cast<char*>(images.data()), images.size());
    return images;
}

static std::vector<uint8_t> load_labels(const std::string& filename, int& total) {
    std::ifstream in(filename, std::ios::binary);
    if(!in) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    int32_t magic = 0;
    in.read(reinterpret_cast<char*>(&magic), 4);
    magic = __builtin_bswap32(magic);

    if(magic != 2049) {
        throw std::runtime_error("Magic number mismatch in " + filename);
    }
    int32_t n_labels = 0;
    in.read(reinterpret_cast<char*>(&n_labels), 4);
    n_labels = __builtin_bswap32(n_labels);

    std::vector<uint8_t> labels(n_labels);
    in.read(reinterpret_cast<char*>(labels.data()), labels.size());
    total = n_labels;
    return labels;
}

std::pair<std::pair<std::vector<uint8_t>, std::vector<uint8_t>>,
          std::pair<std::vector<uint8_t>, std::vector<uint8_t>>>
load_mnist(int train_limit, int test_limit, const std::string& path) {
    int total_train  = 0, rows_train = 0, cols_train = 0;
    auto X_train_all = load_images(path + "/train-images-idx3-ubyte", total_train, rows_train, cols_train);
    auto y_train_all = load_labels(path + "/train-labels-idx1-ubyte", total_train);

    int total_test = 0, rows_test = 0, cols_test = 0;
    auto X_test_all = load_images(path + "/t10k-images-idx3-ubyte", total_test, rows_test, cols_test);
    auto y_test_all = load_labels(path + "/t10k-labels-idx1-ubyte", total_test);

    train_limit = std::min(train_limit, total_train);
    test_limit  = std::min(test_limit, total_test);

    X_train_all.resize(train_limit * rows_train * cols_train);
    y_train_all.resize(train_limit);

    X_test_all.resize(test_limit * rows_test * cols_test);
    y_test_all.resize(test_limit);

    return { {X_train_all, y_train_all}, {X_test_all, y_test_all} };
}