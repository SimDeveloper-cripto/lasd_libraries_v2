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

// List's Map function to apply
void Square (int& value, void* other) { value = value * value; };

// List's Fold function to apply
void SumEvenNumbers(const int& value, const void* limit, void* accumulator) {
    if(value % *((int*) limit) == 0) {
        *((int*) accumulator) = *((int*) accumulator) + value;
        std::cout << "  Accumulated value: " << *((int*) accumulator) << std::endl;
    } else {
        *((int*) accumulator) = *((int*) accumulator) + 0;
    }
}

namespace lasdtest {
    void run_personal_linked_list_test() {
        std::cout << std::endl << "[ OK ] LINKED_LIST TEST STARTED." << std::endl;

        List<int>* list = new List<int>();
        list->InsertAtFront(generate_random_number());
        list->InsertAtFront(generate_random_number());
        list->InsertAtBack(generate_random_number());
        list->InsertAtBack(generate_random_number());
        list->InsertAtFront(generate_random_number());

        int val = generate_random_number();
        list->InsertAtBack(val);

        int new_val = generate_random_number();

        std::cout << "Generated List with Size: " << list->Size() << std::endl;
        
        if (list->Empty()) {
            std::cout << "The list is empty!" << std::endl;
        } else {
            list->PrintList();

            std::cout << "List's head element value: " << list->Front() << std::endl;
            std::cout << "List's tail element value: " << list->Back() << std::endl;

            unsigned long index = generate_random_index(list->Size());
            std::cout << "List's element at index " << index << ": " << list->operator[](index) << std::endl;

            std::cout << "List's Exists(" << val << ") test: ";
            (list->Exists(val)) ? std::cout << "    Yes, element is present." << std::endl : std::cout << "   No, element is not present." << std::endl;

            std::cout << "List's Exists(" << new_val << ") test: ";
            (list->Exists(new_val)) ? std::cout << "    Yes, element is present." << std::endl : std::cout << "   No, element is not present." << std::endl;

            unsigned long change_index = 3; // List's test has only 5 or 6 elements, it could be worse than that.
            int subtitute = 1;
            std::cout << "List's ChangeValueGivenIndex( index: " << change_index << ", new_value: " << subtitute << ") test: " << std::endl;
            list->ChangeValueGivenIndex(change_index, subtitute); // Remember: the function returns a boolean.
            std::cout << "  "; list->PrintList();

            std::cout << "The List has been Reversed:" << std::endl;
            list->Reverse();
            std::cout << "  "; list->PrintList();
            
            std::cout << "List's new head element value: " << list->Front() << std::endl;
            std::cout << "List's new tail element value: " << list->Back() << std::endl;

            std::cout << "List's values afer Map(): " << std::endl;
            list->MapPreOrder(Square, nullptr);
            std::cout << "  "; list->PrintList();

            const int divide_by = 2; 
            int start = 0;
            std::cout << "List's Fold() application (SumEvenNumbers): " << std::endl;
            list->FoldPreOrder(SumEvenNumbers, &divide_by, &start);
        }

        std::cout << std::endl;
        delete list;
    }

    void run_personal_graph_test() {
        std::cout << std::endl << "[ OK ] GRAPH TEST STARTED." << std::endl;
        Graph<int>* graph = new lasd::Graph<int>();

        graph->addNode(0);
        graph->addNode(1);
        graph->addNode(2);
        graph->addNode(3);
        graph->addNode(4);
        graph->addNode(5);
        graph->addNode(6);

        graph->addEdge(0, 1);
        graph->addEdge(1, 0);
        graph->addEdge(3, 1);
        graph->addEdge(1, 2);
        graph->addEdge(2, 3);
        graph->addEdge(1, 4);
        graph->addEdge(4, 5);
        graph->addEdge(5, 6);
        graph->addEdge(6, 4);

        /*
            SCCs MUST BE: 0 1 3 2 | 4 5 6
        */

        /** Map functions applied to both Bfs and Dfs
            That is basically our way to apply Map() to Graph's nodes
        */
        auto applyToNodeBfs = [](const int& node, void* other) {
            std::cout << "  [QUEUE HEAD] Visiting: " << node << std::endl; // const int&, insted of printing we could modify the values.
        };
        
        auto applyToNodeDfs = [](const int& node, void* other) {
            std::cout << node << " "; // const int&, insted of printing we could modify the values.
        };

        std::cout << "Printing the Graph: " << std::endl;
        graph->showGraph();

        // DEFAULT BFS
        std::cout << "Bfs's result: " << std::endl;
        graph->Bfs(1, applyToNodeBfs, nullptr);

        // DEFAULT DFS
        std::cout << "Dfs's result: ";
        graph->Dfs(applyToNodeDfs, nullptr);

        // Try Dfs but starting from a specific index
        std::cout << std::endl << "Dfs's result (starting from node 5): ";
        graph->Dfs(5, applyToNodeDfs, nullptr);

        // CUSTOM MADE DFS TO CHECK IF GRAPH IS CYCLIC
        bool do_incoming_grade = true;
        if (graph->isGraphAcyclicDfs()) {
            std::cout << std::endl << "Acyclic test: the Graph is acyclic." << std::endl;
        } else {
            std::cout << std::endl << "Acyclic test: the Graph is cyclic." << std::endl;
            do_incoming_grade = false;
        }
        
        std::cout << "Topological-Order of the Graph: ";
        std::stack<int> myOrder = graph->getTopologicalOrder(true);
        
        while(!myOrder.empty()) {
            std::cout << myOrder.top() << " ";
            myOrder.pop();
        }
        std::cout << std::endl;

        if (do_incoming_grade) {
            std::cout << "Topological-Order of the Graph using Incoming Grade: ";
            std::vector<int> myOrder2 = graph->getTopologicalOrderUsingIncomingGrade();
            
            for (const int elem : myOrder2) std::cout << elem << " ";
            std::cout << std::endl;
        }

        { /* [SCC TEST] START */
            std::cout << std::endl;
            std::cout << "SCC CALCULATION: " << std::endl;
            std::vector<std::vector<int>> sccs = graph->CalculateStronglyConnectedComponents();

            for (const std::vector<int>& scc : sccs) {
                std::cout << "  Component: ";
                for (const int& elem : scc) {
                    std::cout << elem << " ";
                }
                std::cout << std::endl;
            }
        } /* [SCC TEST] END */

        graph->Transpose();
        std::cout << std::endl << "Printing the Transposed Graph: " << std::endl;
        graph->showGraph();

        /* ************************************************************************ */

        Node<int> node1, node2;
        node1.key = 10, node2.key = 11;
        node1.color = Color::White, node2.color = Color::White;

        std::cout << "Added new Node to Graph, addNode(const Node<Data>&) called:" << std::endl;
        graph->addNode(node1);
        graph->addNode(node2);
        graph->addEdge(node1, node2);
        graph->addEdge(node2, node1);
        graph->addEdge(5, node2.key);
        graph->showGraph();

        std::cout << "Dfs's result (starting from new node " << node1.key << "): ";
        graph->Dfs(node1.key, applyToNodeDfs, nullptr); // applyToNodeDfs is defined above.

        if (graph->isGraphAcyclicDfs()) {
            std::cout << std::endl << "Acyclic test: the new Graph is acyclic." << std::endl;
        } else {
            std::cout << std::endl << "Acyclic test: the new Graph is cyclic." << std::endl;
        }

        /* ************************************************************************ */

        /** Fold function applied to both Bfs and Dfs
            That is basically our way to apply Fold() to Graph's nodes
        */
        auto applyFoldToNode = [](const int& node, const void* limit, void* accumulator) {
            // Sum values >= limit
            if(node >= *((int*) limit)) {
                *((int*) accumulator) = *((int*) accumulator) + node;
                std::cout << "  Accumulated value: " << *((int*) accumulator) << std::endl;
            } else {
                *((int*) accumulator) = *((int*) accumulator) + 0;
            }
       };

        /* Apply Fold() to the Transposed Graph */
        int start = 2, accum = 0;

        std::cout << "Bfs's Fold application result: " << std::endl;
        graph->Bfs(1, applyFoldToNode, &start, &accum);

        accum = 0;
        // std::cout << "Dfs's Fold application result (starting from 1): " << std::endl;
        // graph->Dfs(1, applyFoldToNode, &start, &accum);
        std::cout << "Dfs's Fold application result: " << std::endl;
        graph->Dfs(applyFoldToNode, &start, &accum);

        /* ************************************************************************ */

        // TODO: Solve one of ASD's problems: the ones where a barrier between nodes is formed

        /* ************************************************************************ */

        std::cout << std::endl;
        delete graph;
    }

    void run_test() {
        run_personal_linked_list_test();
        std::cout << "-----------------------------------------------------------------------------------" << std::endl;
        
        run_personal_graph_test();
        std::cout << "-----------------------------------------------------------------------------------" << std::endl;

        // TODO: CREATE A FLOAT TEST FOR GRAPH
    }
}

/* [YOUR CODE STARTS HERE] HERE CREATE YOUR PERSONAL TEST */

namespace usertest {
    void run_test() {
        std::cout << "[TODO] There is no user's implementation yet." << std::endl;
    }
}

/* [YOUR CODE ENDS HERE] */