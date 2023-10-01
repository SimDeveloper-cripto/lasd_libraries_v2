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
    void run_personal_linked_list_test() {
        std::cout << "[ OK ] LINKED_LIST TEST STARTED." << std::endl;

        List<int>* list = new List<int>();
        list->InsertAtFront(generate_random_number());
        list->InsertAtFront(generate_random_number());
        list->InsertAtBack(generate_random_number());
        list->InsertAtBack(generate_random_number());
        list->InsertAtFront(generate_random_number());

        int val = generate_random_number();
        list->InsertAtBack(val);

        int new_val = generate_random_number();

        std::cout << "  Size: " << list->Size() << std::endl;
        
        if (list->Empty()) {
            std::cout << "  The list is empty!" << std::endl;
        } else {
            list->PrintList();

            std::cout << "  List's head element value: " << list->Front() << std::endl;
            std::cout << "  List's tail element value: " << list->Back() << std::endl;

            unsigned long index = generate_random_index(list->Size());
            std::cout << "  List's element at index " << index << ": " << list->operator[](index) << std::endl;

            std::cout << "  List's Exists(" << val << ") test: " << std::endl;
            (list->Exists(val)) ? std::cout << "      Elemento presente!" << std::endl : std::cout << "       Elemento non presente!" << std::endl;

            std::cout << "  List's Exists(" << new_val << ") test: " << std::endl;
            (list->Exists(new_val)) ? std::cout << "      Elemento presente!" << std::endl : std::cout << "       Elemento non presente!" << std::endl;

            unsigned long change_index = 3; // This is silly but hey, I do what I want. Its the test that has only 5 or 6 elements, it could be worse than that.
            int subtitute = 1;
            std::cout << "  List's ChangeValueGivenIndex(" << change_index << ", "<< subtitute <<") test: " << std::endl;
            list->ChangeValueGivenIndex(change_index, subtitute); // Remember: the function returns a boolean.
            std::cout << "  "; list->PrintList();

            std::cout << "  Reversed List:" << std::endl;
            list->Reverse();
            std::cout << "  "; list->PrintList();
            
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
    }

    void run_personal_graph_test() {
                std::cout << "[ OK ] GRAPH TEST STARTED." << std::endl;
        Graph<int>* graph = new lasd::Graph<int>();

        // graph->addNode(0);
        graph->addNode(1);
        graph->addNode(2);
        graph->addNode(3);
        graph->addNode(4);
        graph->addNode(5);
        graph->addNode(6);

        // graph->addEdge(0, 6);
        graph->addEdge(1, 2);
        graph->addEdge(1, 3);
        graph->addEdge(3, 1); // You can comment this if you want
        graph->addEdge(2, 3);
        graph->addEdge(3, 4);
        // graph->addEdge(5, 6);
        // graph->addEdge(5, 3);
        graph->addEdge(4, 5);

        std::cout << "  Printing the Graph: " << std::endl;
        graph->showGraph();

        // DEFAULT BFS
        graph->Bfs(1); // 1 2 3 4 [OK]

        // DEFAULT DFS
        std::cout << "  Dfs's result: ";

        /* That is basically our way to apply Map() to Graph's nodes */
        auto applyToNode = [](const int& node, void* other) {
            std::cout << node << " "; // const int&, insted of printing we could modify the values. I would be fun.
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
        
        std::cout << "  Topological-Order of the Graph: ";
        std::stack<int> myOrder = graph->getTopologicalOrder();
        
        while(!myOrder.empty()) {
            std::cout << myOrder.top() << " ";
            myOrder.pop();
        }
        std::cout << std::endl;

        graph->Transpose();
        std::cout << "  Printing the Transposed Graph: " << std::endl;
        graph->showGraph();

        /* ************************************************************************ */

        Node<int> node1, node2;
        node1.key = 10, node2.key = 11;
        node1.color = Color::White, node2.color = Color::White;

        std::cout << std::endl << "  Added new Node to Graph, called addNode(const Node<Data>&)" << std::endl;
        graph->addNode(node1);
        graph->addNode(node2);
        graph->addEdge(node1, node2);
        graph->addEdge(node2, node1);
        graph->addEdge(5, node2.key);
        graph->showGraph();

        std::cout << std::endl << "  Dfs's result (starting from new node "<< node1.key << "): ";
        graph->Dfs(node1.key, applyToNode, nullptr); // applyToNode is defined above.

        if (graph->isGraphAcyclicDfs()) {
            std::cout << std::endl << "  Acyclic test: the new Graph is acyclic." << std::endl;
        } else {
            std::cout << std::endl << "  Acyclic test: the new Graph is cyclic." << std::endl;
        }

        /* ************************************************************************ */

        std::cout << "[ OK ] GRAPH TEST ENDED." << std::endl;
        delete graph;
    }

    void run_test() {
        run_personal_linked_list_test();
        std::cout << "-------------------------------------------------------" << std::endl;
        
        run_personal_graph_test();
        std::cout << "-------------------------------------------------------" << std::endl;

        // ...
    }
}

/* [YOUR CODE STARTS HERE] HERE CREATE YOUR PERSONAL TEST */

namespace usertest {
    // MODIFY THIS AS YOU LIKE
    void run_test() {
        std::cout << "[TODO] To be implemented!" << std::endl;
    }
}

/* [YOUR CODE ENDS HERE] */