#include "test.hpp"

#include <cmath>
#include <assert.h>

using namespace lasd; // List and Graph namespace

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

// Heuristic Example (A* Search)
double Heuristic (const int& source, const int& dest) {
    return std::abs(source - dest);
};

namespace lasdtest {
    void run_personal_linked_list_test() {
        std::cout << std::endl << "[ OK ] LINKED_LIST<int> TEST STARTED" << std::endl;

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
            (list->Exists(val)) ? std::cout << "Yes, element is present." << std::endl : std::cout << "No, element is not present." << std::endl;

            std::cout << "List's Exists(" << new_val << ") test: ";
            (list->Exists(new_val)) ? std::cout << "Yes, element is present." << std::endl : std::cout << "No, element is not present." << std::endl;

            unsigned long change_index = 2; // List's test has only 5 or 6 elements, it could be worse than that.
            int subtitute = 1;
            std::cout << "List's ChangeValueGivenIndex(index: " << change_index << ", new_value: " << subtitute << ") test: " << std::endl;
            list->ChangeValueGivenIndex(change_index, subtitute); // Remember: the function returns a boolean.
            std::cout << "  "; list->PrintList();

            std::cout << std::endl << "The List has been Reversed:" << std::endl;
            list->Reverse();
            std::cout << "  "; list->PrintList();
            
            std::cout << std::endl;
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

        delete list;
    }

    void run_personal_graph_test() {
        std::cout << std::endl << "[ OK ] GRAPH<int> {WEIGHTED AND ORIENTED, IMPLEMENTED BY ADJACENCY LIST} TEST STARTED" << std::endl;

        /* TEST SECTION #1 (WITH DYNAMIC ALLOCATION) */

        DirectedGraph<int>* graph = new lasd::DirectedGraph<int>();
        graph->addNode(0);
        graph->addNode(1);
        graph->addNode(2);
        graph->addNode(3);
        graph->addNode(4);
        graph->addNode(5);
        graph->addNode(6);

        graph->addEdge(3, 1, 1.0); // 3rd parameter is edge-weight
        graph->addEdge(1, 2, 1.0);
        graph->addEdge(2, 3, 2.0);
        graph->addEdge(1, 4, 3.0);
        graph->addEdge(4, 5, 3.0);
        graph->addEdge(5, 6, 4.0);
        graph->addEdge(6, 4, 1.0);

        /** Map functions applied to both Bfs and Dfs
            That is basically our way to apply Map() to Graph's nodes
        */
        auto applyToNodeBfs = [](const int& node, void* other) {
            std::cout << "  [QUEUE HEAD] Visiting: " << node << std::endl; // const int&, instead of printing we could modify the values.
        };
        
        auto applyToNodeDfs = [](const int& node, void* other) {
            std::cout << node << " "; // const int&, insted of printing we could modify the values.
        };

        // DO NOT USE THIS ONE! 
        auto fastMapDfs = [] (const int& node, void* other) {};

        std::cout << "Graph's size: " << graph->Size() << std::endl;

        std::cout << "\nPrinting the Graph: " << std::endl;
        graph->show();

        // DEFAULT BFS
        std::cout << "\nBfs's result, starting from 1: " << std::endl;
        graph->Bfs(1, applyToNodeBfs, nullptr);

        { /* [MIN PATH TEST] START */
            int start = 1, end = 4;

            std::cout << std::endl;
            std::cout << "Minimum path between nodes " << start << " and " << end << ":" << std::endl;

            std::cout << "   Starting from " << start << ": ";
            for (const int vertex : graph->GetMinimumPath(start, end))
                std::cout << vertex << " ";
            
            /* OUTPUT: DIRECT PATH FROM 1 TO 4 (WEIGHT 3.0) */

            std::cout << std::endl << std::endl;
        } /* [MIN PATH TEST] END */

        // DEFAULT DFS
        std::cout << "Dfs's result: ";
        graph->Dfs(applyToNodeDfs, nullptr);

        // Try Dfs but starting from a specific index
        std::cout << std::endl << "Dfs's result (starting from node 4): ";
        graph->Dfs(4, applyToNodeDfs, nullptr); // Works even if the node dosen't exists

        // CUSTOM MADE DFS TO CHECK IF GRAPH IS CYCLIC
        bool do_incoming_grade = true;
        if (graph->isGraphAcyclicDfs()) {
            std::cout << std::endl << "\nAcyclic test: the Graph is acyclic." << std::endl;
        } else {
            std::cout << std::endl << "\nAcyclic test: the Graph is cyclic." << std::endl;
            do_incoming_grade = false;
        }
 
        std::cout << "\nTopological-Order of the Graph (Dfs): ";
        std::stack<int> myOrder = graph->getTopologicalSort(false);

        while(!myOrder.empty()) {
            std::cout << myOrder.top() << " ";
            myOrder.pop();
        }
        std::cout << std::endl;

        if (do_incoming_grade) {
            std::cout << "Topological-Order of the Graph using Incoming Grade: ";
            std::vector<int> myOrder2 = graph->getTopologicalSortUsingIncomingGrade();

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
        graph->show();

        /* ************************************************************************ */

        Node<int> node1, node2;
        node1.key = 10, node2.key = 11;
        node1.color = Color::White, node2.color = Color::White;

        std::cout << "\nAdded new Nodes to Graph, addNode(const Node<Data>&) called:" << std::endl;
        graph->addNode(node1);
        graph->addNode(node2);
        graph->addEdge(node1, node2, 7.0);
        graph->addEdge(node2, node1, 2.0);
        graph->addEdge(5, node2.key, 2.0);
        graph->show();

        std::cout << std::endl << "Dfs's result (starting from new node " << node1.key << "): ";
        graph->Dfs(node1.key, applyToNodeDfs, nullptr); // applyToNodeDfs is Defined Above.

        if (graph->isGraphAcyclicDfs()) {
            std::cout << std::endl << "\nAcyclic test: the new Graph is acyclic." << std::endl;
        } else {
            std::cout << std::endl << "\nAcyclic test: the new Graph is cyclic." << std::endl;
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

        std::cout << "\nBfs's Fold application result: " << std::endl;
        graph->Bfs(1, applyFoldToNode, &start, &accum);

        accum = 0;
        std::cout << "\nDfs's Fold application result: " << std::endl;
        graph->Dfs(applyFoldToNode, &start, &accum);

        std::cout << "\nRemoving all the nodes: ";
        std::vector<Node<int>> nodes = graph->GetAllNodes();
        for (const Node<int>& node : nodes) {
            graph->removeNode(node);
        }

        graph->isEmpty() ? std::cout << "Graph is Empty!" : std::cout << "Graph is not Empty!" << std::endl;
        delete graph;

        /* TEST SECTION #2 (WITH DYNAMIC ALLOCATION) */

        std::cout << std::endl << "\nFor each node, every predecessor: " << std::endl;
        DirectedGraph<int>* new_g = new lasd::DirectedGraph<int>();
        new_g->addNode(0);
        new_g->addNode(1);
        new_g->addNode(2);
        new_g->addNode(3);
        new_g->addNode(4);

        new_g->addEdge(0, 1, 1.0);
        new_g->addEdge(0, 2, 1.0);
        new_g->addEdge(1, 3, 1.0);
        new_g->addEdge(2, 3, 1.0);
        new_g->addEdge(3, 4, 1.0);
        new_g->addEdge(4, 0, 1.0);

        // BFS starting from 0 to update the vector of predecessors
        new_g->Bfs(0, [](const int&, void*){}, nullptr);
        new_g->printForEachNodeItsPredecessor();

        std::cout << "\nClearing the Graph: ";
        graph->Clear();
        graph->isEmpty() ? std::cout << "Graph is Empty!" : std::cout << "Graph is not Empty!" << std::endl;
        delete new_g;

        /* TEST SECTION #3 (WITH STACK ALLOCATION) */

        // For now {X, Y} is a single value.
        DirectedGraph<int> new_g2;
        for (int i = 0; i < 6; i++) new_g2.addNode(i);

        new_g2.addEdge(0, 1, 2.5);
        new_g2.addEdge(0, 4, 3.0);
        new_g2.addEdge(1, 2, 1.5);
        new_g2.addEdge(1, 3, 2.0);
        new_g2.addEdge(0, 4, 1.7);
        new_g2.addEdge(2, 3, 5.0);
        new_g2.addEdge(3, 4, 1.5);
        new_g2.addEdge(3, 5, 2.5);
        new_g2.addEdge(4, 5, 3.0);

        std::vector<std::pair<int, double>> path = new_g2.AStar(0, 5, Heuristic);

        std::cout << std::endl << "\nNew graph of coordinates has been created!" << std::endl;
        std::cout << "[A* SEARCH ALGORITHM FROM 0 TO 5] RESULT: ";
        for (const auto& [node, fScore] : path) {
            std::cout << "{ Node: " << node << ", Heuristic: " << fScore << "} ";
        }
        std::cout << std::endl << std::endl;

        // ASSERT CORRECT PATH
        std::vector<std::pair<int, double>> expectedPath = {{0, 5}, {4, 2.7}, {5, 4.7}};
        assert(path == expectedPath);

        /* TEST SECTION #4 (WITH STACK ALLOCATION) */

        /* SOLVED ONE ASD EXAM [SEPTEMBER 2019, LOOK AT YOUR SOLUTION] */
        DirectedGraph<int> new_g3;
        for (int i = 0; i < 7; i++) new_g3.addNode(i);

        new_g3.addEdge(1, 0, 1.0);
        new_g3.addEdge(0, 6, 1.0);
        new_g3.addEdge(6, 5, 1.0);
        new_g3.addEdge(5, 0, 1.0);
        new_g3.addEdge(0, 1, 1.0);
        new_g3.addEdge(4, 2, 1.0);
        new_g3.addEdge(4, 3, 1.0);
        new_g3.addEdge(2, 0, 1.0);
        new_g3.addEdge(3, 6, 1.0);

        std::set<int> ASet; // Use a Set to get O(log(n)) as search complexity.
        std::vector<int> S;
        
        ASet.insert(0);
        ASet.insert(2);
        ASet.insert(3);

        std::cout << "--- #1 DFS SET" << std::endl;
        new_g3.DfsFromSet(ASet, fastMapDfs, nullptr);
        std::unordered_map<int, Color> color_map_v1 = new_g3.GetCurrentColors();
        new_g3.Transpose();
        std::cout << "--- #2 TRANSPOSE DFS SET" << std::endl;
        new_g3.DfsFromSet(ASet, fastMapDfs, nullptr);

        for (auto& node : new_g3.GetAllNodes()) {
            auto value = node.key;
            std::unordered_map<int, Color>::iterator it = color_map_v1.find(value);
            if (it != color_map_v1.end()) {
                // We only check the nodes which aren't inside the Set.
                if (ASet.find(value) == ASet.end() && (it->second == Color::White || node.color == Color::White)) {
                    S.push_back(value);
                    std::cout << "--- Found: " << value << std::endl; // Will print "Found: 4".
                    assert(value == 4);
                }
            }
        }

        // ASSERT CORRECT STACK SIZE
        assert(S.size() == 1);
        std::cout << "--- 'Stack' size = 1, correct! " << std::endl;
    }

    void run_test() {
        short int choice;
        std::cout << "\n[1 - DEV] RUN LINKED_LIST<int> TEST" << std::endl << "[2 - DEV] RUN GRAPH<int> TEST" << std::endl;
        std::cout << ">>> "; std::cin >> choice;

        switch(choice) {
            case 1:
                run_personal_linked_list_test(); // Example with Integers, but It works also with other fund. data types
                break;
            case 2:
                run_personal_graph_test();
                break;
            default:
                std::cout << "Sorry, there is no action for your choice!" << std::endl;
        }
    }
}

/* [YOUR CODE STARTS HERE] HERE CREATE YOUR PERSONAL TEST */

namespace usertest {
    void run_test() {
        std::cout << "[TODO] There is no user's implementation yet." << std::endl;
    }
}

/* [YOUR CODE ENDS HERE] */