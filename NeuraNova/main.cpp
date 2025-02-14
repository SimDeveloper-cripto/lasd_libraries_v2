#include <iostream>

#include "setup.hpp"
#include "config.hpp"

int main() {
    try {
        run_ff_model();
    } catch (const std::exception& e) {
        std::cerr << "[ERRORE] " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
