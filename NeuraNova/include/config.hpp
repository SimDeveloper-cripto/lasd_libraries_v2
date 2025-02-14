#ifndef NEURANOVA_CONFIG_HPP
#define NEURANOVA_CONFIG_HPP

#include <string>
#include <vector>

struct LayerConfig {
    int neurons;
    std::string activation;
};

struct FFConfig {
    std::vector<LayerConfig> layers;
    int train_dimension;
    int test_dimension;
    int validation_dimension;
    int epochs;
    int batch_size;
    float learning_rate;
    float beta1;
    float beta2;
    float epsilon;
};

struct FFResult {
    std::vector<LayerConfig> layers;
    int train_dimension;
    int test_dimension;
    int epochs;
    int batch_size;
    std::string test_accuracy;
};

std::vector<FFConfig> load_ff_config(const std::string& file_path);

void update_config_results(const std::vector<FFResult>& results,
                           const std::string& filename);

#endif // NEURANOVA_CONFIG_HPP