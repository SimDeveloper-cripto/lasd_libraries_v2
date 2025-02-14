#include <cmath>
#include <iostream>
#include <algorithm>

#include "../include/loss.hpp"
#include "../include/setup.hpp"

std::vector<float> one_hot_encode(const std::vector<uint8_t>& labels, int num_classes) {
    int n = (int)labels.size();
    std::vector<float> one_hot(num_classes * n, 0.0f);
    for (int i = 0; i < n; i++) {
        int label = labels[i];
        if (label >= 0 && label < num_classes) {
            one_hot[label * n + i] = 1.0f;
        }
    }
    return one_hot;
}

FFDataSet load_and_preprocess_data_for_ff(int train_limit,
                                          int test_limit,
                                          int validation_limit) {
    auto mnist = load_mnist(train_limit, test_limit);

    // mnist.first  => (X_train, y_train)
    // mnist.second => (X_test,  y_test)

    // X_train shape => (train_limit, 28, 28)
    // y_train shape => (train_limit)
    // Idem per test
    auto X_train_3d = mnist.first.first;
    auto y_train_1d = mnist.first.second;
    auto X_test_3d  = mnist.second.first;
    auto y_test_1d  = mnist.second.second;

    int N_train = train_limit;
    int N_test  = test_limit;
    int rows = 28;
    int cols = 28;
    int image_size = rows * cols; // 784

    // Normalizzazione [0..255] => [0..1], flatten (28x28 => 784)
    // X_train_3d ha dimensione (N_train * 784)
    std::vector<float> X_train_f(N_train * image_size);
    for (int i = 0; i < N_train * image_size; i++) {
        X_train_f[i] = float(X_train_3d[i]) / 255.0f;
    }

    std::vector<float> X_test_f(N_test * image_size);
    for (int i = 0; i < N_test * image_size; i++) {
        X_test_f[i] = float(X_test_3d[i]) / 255.0f;
    }

    int num_classes = 10;
    auto y_train_oh = one_hot_encode(y_train_1d, num_classes); // shape (10 * N_train)
    auto y_test_oh  = one_hot_encode(y_test_1d, num_classes);

    if (validation_limit > N_train) {
        validation_limit = N_train;
    }
    int N_val = N_train - validation_limit;

    std::vector<float> X_train_final(784 * validation_limit);
    std::vector<float> y_train_final(10 * validation_limit);
    std::vector<float> X_val(784 * N_val);
    std::vector<float> y_val(10 * N_val);

    for (int i = 0; i < validation_limit; i++) {
        for (int d = 0; d < 784; d++) {
            X_train_final[d * validation_limit + i] = X_train_f[i * 784 + d];
        }
        for (int c = 0; c < 10; c++) {
            y_train_final[c * validation_limit + i] = y_train_oh[c * N_train + i];
        }
    }

    for (int i = 0; i < N_val; i++) {
        int idx = validation_limit + i;
        for (int d = 0; d < 784; d++) {
            X_val[d * N_val + i] = X_train_f[idx * 784 + d];
        }
        for (int c = 0; c < 10; c++) {
            y_val[c * N_val + i] = y_train_oh[c * N_train + idx];
        }
    }

    // Trasponiamo X_test e y_test_oh: (N_test, 784) => (784, N_test)
    std::vector<float> X_test_T(784 * N_test);
    std::vector<float> y_test_T(10  * N_test);
    for (int i = 0; i < N_test; i++) {
        for (int d = 0; d < 784; d++) {
            X_test_T[d * N_test + i] = X_test_f[i * 784 + d];
        }
        for (int c = 0; c < 10; c++) {
            y_test_T[c * N_test + i] = y_test_oh[c * N_test + i];
        }
    }

    FFDataSet ds;
    ds.X_train = X_train_final;
    ds.y_train = y_train_final;
    ds.X_val   = X_val;
    ds.y_val   = y_val;
    ds.X_test  = X_test_T;
    ds.y_test  = y_test_T;
    ds.train_samples = validation_limit;
    ds.val_samples   = N_val;
    ds.test_samples  = N_test;
    return ds;
}

FFResult build_and_train_ff_model_with_config(const FFConfig& config) {
    auto ds = load_and_preprocess_data_for_ff(config.train_dimension,
                                              config.test_dimension,
                                              config.validation_dimension);
    SoftmaxCrossEntropy softmaxCE;
    FeedForward nn(&softmaxCE);

    int input_dim = 784;
    for (size_t i = 0; i < config.layers.size(); i++) {
        int out_dim = config.layers[i].neurons;
        DenseLayer layer(input_dim,
                         out_dim,
                         config.layers[i].activation,
                         config.learning_rate,
                         config.beta1, config.beta2, config.epsilon);
        nn.add_layer(layer);
        input_dim = out_dim;
    }

    nn.train(ds.X_train, ds.y_train,
             784,
             ds.train_samples,
             config.epochs,
             ds.X_val, ds.y_val, ds.val_samples,
             config.batch_size);

    // Test
    float test_acc = nn.getAccuracy(ds.X_test, ds.y_test, 784, ds.test_samples);

    FFResult r;
    r.layers          = config.layers;
    r.train_dimension = config.train_dimension;
    r.test_dimension  = config.test_dimension;
    r.epochs          = config.epochs;
    r.batch_size      = config.batch_size;

    char buf[32];
    snprintf(buf, sizeof(buf), "%.2f", test_acc * 100.0f);
    r.test_accuracy = buf;
    return r;
}

void run_ff_model() {
    auto configs = load_ff_config("config/ffconfig.json");
    std::vector<FFResult> results;

    int index = 1;
    for (auto& cfg : configs) {
        std::cout << "\n[FEED-FORWARD] TRAINING MODEL WITH CONFIG " << index << std::endl;
        auto res = build_and_train_ff_model_with_config(cfg);
        results.push_back(res);
        index++;
    }
    update_config_results(results, "results/ff/results.json");
}