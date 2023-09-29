#include "test.hpp"
// #include <assert.h>

using namespace lasd;

int generate_random_index(unsigned long size) {
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, size-1);
    return dist(generator);
}

int generate_random_number() {
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> dist(-200, 200);
    return dist(generator);
}

void Square (int& value, void* other) { value = value * value; };

void SumEvenNumbers(const int& value, const void* limit, void* accumulator) {
    if(value % *((int*) limit) == 0) {
        *((int*) accumulator) = *((int*) accumulator) + value; 
        std::cout << "      Accum. value: " << *((int*) accumulator) << std::endl; 
    } else {
        *((int*) accumulator) = *((int*) accumulator) + 0;
    }
}

namespace lasdtest {
    void run_test() {
        std::cout << "[ OK ] LINKED_LIST TEST STARTED." << std::endl;

        List<int>* list = new List<int>();
        list->InsertAtBack(generate_random_number());
        list->InsertAtFront(generate_random_number());
        list->InsertAtBack(generate_random_number());
        list->InsertAtBack(generate_random_number());
        list->InsertAtFront(generate_random_number());

        std::cout << "  Size: " << list->Size() << std::endl;
        
        if (list->Empty()) {
            std::cout << "  The list is empty!" << std::endl;
        } else {
            list->PrintList();

            std::cout << "  List's head element value: " << list->Front() << std::endl;
            std::cout << "  List's tail element value: " << list->Back() << std::endl;

            unsigned long index = generate_random_index(list->Size());
            std::cout << "  List's element at index " << index << ": " << list->operator[](index) << std::endl;

            list->Reverse();
            list->PrintList();
            std::cout << "  List's new head element value: " << list->Front() << std::endl;
            std::cout << "  List's new tail element value: " << list->Back() << std::endl;

            std::cout << "  List's values afer Map(): " << std::endl;
            list->MapPreOrder(Square, nullptr);
            std::cout << "  "; list->PrintList();

            const int divide_by = 2; 
            int start = 0;
            std::cout << "  List's Fold() application: " << std::endl;
            list->FoldPreOrder(SumEvenNumbers, &divide_by, &start);
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
        graph->addNode(6);

        graph->addEdge(1, 2);
        graph->addEdge(1, 3);
        // graph->addEdge(3, 1); // You can comment this if you want
        graph->addEdge(2, 3);
        graph->addEdge(3, 4);
        // graph->addEdge(5, 6);
        // graph->addEdge(5, 3);
        // graph->addEdge(4, 5);

        // DEFAULT BFS    
        graph->Bfs(1); // 1 2 3 4 [OK]

        // DEFAULT DFS
        std::cout << "  Dfs's result: ";
        auto applyToNode = [](const int& node, void* other) {
            std::cout << node << " ";
        };
        graph->Dfs(applyToNode, nullptr);

        // Try Dfs but starting from a specific index
        std::cout << std::endl << "  Dfs's result (starting from node 5): ";
        graph->Dfs(5, applyToNode, nullptr);

        // CUSTOM MADE DFS TO CHECK IF GRAPH IS CYCLIC
        if (graph->isGraphAcyclicDfs()) {
            std::cout << std::endl << "  Acyclic test: the Graph is acyclic." << std::endl;
        } else {
            std::cout << std::endl << "  Acyclic test: the Graph is cyclic." << std::endl;
        }

        std::cout << "[ OK ] GRAPH TEST ENDED." << std::endl;
        delete graph;
        std::cout << "-------------------------------------------------------" << std::endl;

        // ...
    }
}