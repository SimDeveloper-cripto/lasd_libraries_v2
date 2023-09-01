#include "test.hpp"

using namespace lasd;

int generate_random_number() {
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> dist(-200, 200);
    return dist(generator);
}

namespace lasdtest {
    void run_test() {
        std::cout << "[ OK ] INT VALUES TEST STARTED." << std::endl;

        List<int>* list = new List<int>();

        list->InsertAtBack(generate_random_number());
        list->InsertAtFront(generate_random_number());
        list->InsertAtBack(generate_random_number());

        std::cout << "List's head element value: " << list->Front() << std::endl;
        std::cout << "List's tail element value: " << list->Back() << std::endl;

        // TODO: MUST TEST ACCESS AT RANDOM INDEX (YOU OVERLOADED THE OPERATOR: JUST TRY IT)

        std::cout << "[ OK ] INT VALUES TEST ENDED." << std::endl;
        delete list;
    }
}