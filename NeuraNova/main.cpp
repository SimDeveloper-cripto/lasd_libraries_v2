#include <iostream>

#include "setup.hpp"
#include "config.hpp"

int main() {
    try {
        launch();
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Could not run 'launch()' function!\n" << e.what() << std::endl;
        return 1;
    }
    return 0;
}