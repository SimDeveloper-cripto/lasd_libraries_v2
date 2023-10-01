#pragma once

#include <random>
#include <iostream>
#include "../LinkedList/linked_list.hpp"
#include "../Graph/graph.hpp"

namespace lasdtest {
    void run_test();
    void run_personal_linked_list_test();
    void run_personal_graph_test();
}

// USER'S NAMESPACE SO THAT CAN DECLARE PERSONAL TEST
namespace usertest {
    void run_test(); // JUST MODIFY run_test()
}