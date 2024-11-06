#include "test/test.hpp"

int main(int argc, char** argv) {
    short int choice;
    std::cout << "[1 - DEVELOPER] Run default test." << std::endl << "[2 - USER]      Run your personal test." << std::endl;
    std::cout << ">>> "; std::cin >> choice;

    switch(choice) {
        case 1:
            lasdtest::run_test();
            break;
        case 2:
            usertest::run_test(); // READ NOTE BELOW
            break;
        default:
            std::cout << "Sorry, there is no action for your choice!" << std::endl;
    }

    return 0;
}

// NOTE: usertest::run_test() is defined in myTest/test.hpp. That is the place in which you can insert your personal code.
// run_test() is implemented in myTest/test.cpp.
// Please whatever code you write, make sure to do it inside usertest namespace.