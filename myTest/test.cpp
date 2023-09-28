#include "test.hpp"
#include <assert.h>

using namespace lasd;

int generate_random_number() {
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> dist(-200, 200);
    return dist(generator);
}

namespace lasdtest {
    void run_test() {
        std::cout << "[ OK ] LINKED_LIST TEST STARTED." << std::endl;

        List<int>* list = new List<int>();
        list->InsertAtBack(generate_random_number());
        list->InsertAtFront(generate_random_number());
        list->InsertAtBack(generate_random_number());

        std::cout << "Size: " << list->Size() << std::endl;
        
        if (list->Empty()) {
            std::cout << "The list is empty!" << std::endl;
        } else {
            std::cout << "List's head element value: " << list->Front() << std::endl;
            std::cout << "List's tail element value: " << list->Back() << std::endl;

            unsigned long index = 0;
            assert((index >= 0) && (index <= (list->Size() - 1)));
            std::cout << "List's element at index " << index << ": " << list->operator[](index) << std::endl;
        }

        std::cout << "[ OK ] LINKED_LIST TEST ENDED." << std::endl;
        delete list;
        std::cout << "-------------------------------------------------------" << std::endl;

        std::cout << "[ OK ] GRAPH TEST STARTED." << std::endl;
        Graph<int>* graph = new lasd::Graph<int>();

        graph->addNode(1);
        graph->addNode(2);
        graph->addNode(3);
        graph->addNode(4);
        graph->addNode(5);

        graph->addEdge(1, 2);
        graph->addEdge(1, 3);
        graph->addEdge(3, 1); // you can comment this if you want
        graph->addEdge(2, 3);
        graph->addEdge(3, 4);

        // DEFAULT BFS    
        graph->Bfs(1);

        // DEFAULT DFS
        auto applyToNode = [](const int& node, void* other) {
            std::cout << node << " ";
        };
        graph->Dfs(1, applyToNode, nullptr);

        // CUSTOM MADE DFS TO CHECK IF GRAPH IS CYCLIC
        if (graph->isGraphCyclicDfs(1)) {
            std::cout << "\nThe Graph is cyclic." << std::endl;
        } else {
            std::cout << "\nThe Graph is acyclic." << std::endl;
        }

        std::cout << "[ OK ] GRAPH TEST ENDED." << std::endl;
        delete graph;
        std::cout << "-------------------------------------------------------" << std::endl;

        // ...
    }
}