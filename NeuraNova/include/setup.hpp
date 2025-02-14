#ifndef NEURANOVA_SETUP_HPP
#define NEURANOVA_SETUP_HPP

#include "../include/data.hpp"
#include "../include/config.hpp"
#include "../include/feedforward.hpp"

struct FFDataSet {
    std::vector<float> X_train;
    std::vector<float> y_train;
    std::vector<float> X_val;
    std::vector<float> y_val;
    std::vector<float> X_test;
    std::vector<float> y_test;
    int train_samples;
    int val_samples;
    int test_samples;
};

std::vector<float> one_hot_encode(const std::vector<uint8_t>& labels, int num_classes);

FFDataSet load_and_preprocess_data_for_ff(int train_limit,
                                          int test_limit,
                                          int validation_limit);

FFResult build_and_train_ff_model_with_config(const FFConfig& config);

void run_ff_model();

#endif // NEURANOVA_SETUP_HPP