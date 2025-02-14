#include "../include/config.hpp"

#include <cmath>
#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

std::vector<FFConfig> load_ff_config(const std::string& file_path) {
    std::ifstream in(file_path);
    if(!in) {
        throw std::runtime_error("Cannot open config file: " + file_path);
    }
    json j;
    in >> j;

    std::vector<FFConfig> configs;
    for (auto& item : j) {
        FFConfig cfg;
        for (auto& l : item["layers"]) {
            LayerConfig lc;
            lc.neurons = l["neurons"].get<int>();
            lc.activation = l["activation"].get<std::string>();
            cfg.layers.push_back(lc);
        }
        cfg.train_dimension      = item["train_dimension"].get<int>();
        cfg.test_dimension       = item["test_dimension"].get<int>();
        cfg.validation_dimension = item["validation_dimension"].get<int>();
        cfg.epochs               = item["epochs"].get<int>();
        cfg.batch_size           = item["batch_size"].get<int>();
        cfg.learning_rate        = item["learning_rate"].get<float>();
        cfg.beta1                = item["beta1"].get<float>();
        cfg.beta2                = item["beta2"].get<float>();
        cfg.epsilon              = item["epsilon"].get<float>();
        configs.push_back(cfg);
    }
    return configs;
}

void update_config_results(const std::vector<FFResult>& results,
                           const std::string& filename) {
    json rootArray;
    for (auto& r : results) {
        json jr;
        json jLayers = json::array();
        for (auto& l : r.layers) {
            jLayers.push_back({
                {"neurons", l.neurons},
                {"activation", l.activation}
            });
        }
        jr["layers"]          = jLayers;
        jr["train_dimension"] = r.train_dimension;
        jr["test_dimension"]  = r.test_dimension;
        jr["epochs"]          = r.epochs;
        jr["batch_size"]      = r.batch_size;
        jr["test_accuracy"]   = r.test_accuracy;

        rootArray.push_back(jr);
    }

    std::vector<float> accuracies;
    for (auto& r : results) {
        try {
            float acc = std::stof(r.test_accuracy);
            accuracies.push_back(acc);
        } catch(...) {}
    }

    if (!accuracies.empty()) {
        float sumAcc = 0.f;
        for (auto a : accuracies) sumAcc += a;
        float meanAcc = sumAcc / float(accuracies.size());

        float sumVar = 0.f;
        for (auto a : accuracies) {
            float diff = a - meanAcc;
            sumVar += diff * diff;
        }
        float stdAcc = 0.f;
        if (accuracies.size() > 1) {
            stdAcc = std::sqrt(sumVar / float(accuracies.size()));
        }

        json finalObj;
        finalObj["ar_mean"]       = std::to_string(meanAcc);
        finalObj["std_deviation"] = std::to_string(stdAcc);
        rootArray.push_back(finalObj);
    }

    json finalJson = json::array();
    finalJson.push_back(rootArray);

    std::ofstream out(filename);
    if(!out) {
        throw std::runtime_error("Cannot write results file: " + filename);
    }
    out << finalJson.dump(4) << std::endl;
}