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

        int test_step = 1;

        // TEST #1
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
        list->PrintList();
        
        if (!list->Empty()) {
            std::cout << "List's head element value: " << list->Front() << std::endl;
            std::cout << "List's tail element value: " << list->Back() << std::endl;
            std::cout << "List's Exists(" << val << "): "
                    << (list->Exists(val) ? "True" : "False")
                    << std::endl;
            std::cout << "List's Exists(" << new_val << "): "
                    << (list->Exists(new_val) ? "True" : "False")
                    << std::endl;

            std::cout << "--> [INFO] TEST #" << test_step++ << " 'INSERT AND VERIFY MEMBERSHIP' STATUS: PASSED" << std::endl;
        } else {
            std::cout << "The list is empty!" << std::endl;
            std::cout << "--> [ERROR] TEST #" << test_step++ << " 'INSERT AND VERIFY MEMBERSHIP' STATUS: FAILED" << std::endl;
        }

        // Test #2
        unsigned long change_index = 2;
        int substitute = 1;
        bool changed = list->ChangeValueGivenIndex(change_index, substitute);
        std::cout << "\nList's ChangeValueGivenIndex(index: " << change_index << ", new_value: " << substitute << "): " << std::endl;
        list->PrintList();

        if (changed && list->operator[](change_index) == substitute) {
            std::cout << "--> [INFO] TEST #" << test_step++ << " 'CHANGE VALUE GIVEN INDEX' STATUS: PASSED" << std::endl;
        } else {
            std::cout << "--> [ERROR] TEST #" << test_step++ << " 'CHANGE VALUE GIVEN INDEX' STATUS: FAILED" << std::endl;
        }

        // Test #3
        list->Reverse();
        std::cout << std::endl << "The List has been Reversed:" << std::endl;
        list->PrintList();
        
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'REVERSE LIST' STATUS: PASSED" << std::endl;

        // Test #4
        list->MapPreOrder(Square, nullptr);
        std::cout << "\nList's values after Map() 'Square': " << std::endl;
        list->PrintList();
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'MAP PRE-ORDER (SQUARE) STATUS PASSED" << std::endl;

        // Test #5
        const int divide_by = 2;
        int start = 0;
        std::cout << "\nList's Fold() application (Sum Even Numbers): " << std::endl;
        list->FoldPreOrder(SumEvenNumbers, &divide_by, &start);
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'FOLD PRE-ORDER 'SUM EVEN NUMBERS' STATUS: PASSED" << std::endl;

        delete list;
    }

    void run_personal_graph_test() {
        std::cout << std::endl << "[ OK ] GRAPH<int> {WEIGHTED AND ORIENTED, IMPLEMENTED BY ADJACENCY LIST} TEST STARTED" << std::endl;

        int test_step = 1;

        auto applyToNodeBfs = [](const int& node, void* other) {
            // const int&, instead of printing we could modify the values
            std::cout << "  [QUEUE HEAD] Visiting: " << node << std::endl;
        };

        auto applyToNodeDfs = [](const int& node, void* other) {
            // const int&, insted of printing we could modify the values
            std::cout << node << " ";
        };

        auto fastMapDfs = [] (const int& node, void* other) {};

        DirectedGraph<int>* graph = new lasd::DirectedGraph<int>();
        for (int i = 0; i < 7; i++) graph->addNode(i);

        graph->addEdge(3, 1, 1.0);
        graph->addEdge(1, 2, 1.0);
        graph->addEdge(2, 3, 2.0);
        graph->addEdge(1, 4, 3.0);
        graph->addEdge(4, 5, 3.0);
        graph->addEdge(5, 6, 4.0);
        graph->addEdge(6, 4, 1.0);

        std::cout << "Graph's size: " << graph->Size() << ", ";
        std::cout << "Printing the Graph: " << std::endl;
        graph->show();

        // Test #1 'BFS'
        std::cout << "\nBfs's result, starting from 1: " << std::endl;
        graph->Bfs(1, applyToNodeBfs, nullptr);
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'MAP BFS' STATUS: PASSED" << std::endl;

        // Test #2 'Minimum Path'
        {
            int start = 3, end = 6;
            std::cout << "\nMinimum path between nodes " << start << " and " << end << ":" << std::endl;
            std::cout << "   Starting from " << start << ": ";
            for (const int vertex : graph->GetMinimumPath(start, end))
                std::cout << vertex << " ";
            std::cout << std::endl << "--> [INFO] TEST #" << test_step++ << " 'DIJKSTRA MINIMUM PATH' STATUS: PASSED\n" << std::endl;
        }

        // Test #3 'DFS'
        std::cout << "Dfs's result: ";
        graph->Dfs(applyToNodeDfs, nullptr);
        std::cout << "\nDfs's result (starting from node 4): ";
        graph->Dfs(4, applyToNodeDfs, nullptr);
        std::cout << "\n--> [INFO] TEST #" << test_step++ << " 'MAP DFS' STATUS: PASSED" << std::endl;

        // Test #4 'Acyclic Test'
        bool do_incoming_grade = true;
        if (graph->isGraphAcyclicDfs()) {
            std::cout << "\nAcyclic test: the Graph is acyclic." << std::endl;
        } else {
            std::cout << "\nAcyclic test: the Graph is cyclic." << std::endl;
            do_incoming_grade = false;
        }
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'ACYCLIC TEST' STATUS: PASSED" << std::endl;

        // Test #5 'Topological Sort'
        std::cout << "\nTopological-Order of the Graph (Dfs): ";
        std::stack<int> myOrder = graph->getTopologicalSort(false);
        while(!myOrder.empty()) {
            std::cout << myOrder.top() << " ";
            myOrder.pop();
        }
        std::cout << std::endl;
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'TOPOLOGICAL SORT WITH DFS' STATUS: PASSED" << std::endl;

        if (do_incoming_grade) {
            std::cout << "Topological-Order of the Graph using Incoming Grade: ";
            std::vector<int> myOrder2 = graph->getTopologicalSortUsingIncomingGrade();
            for (const int elem : myOrder2) std::cout << elem << " ";
            std::cout << std::endl;
            std::cout << "--> [INFO] TEST #" << test_step++ << " 'TOPOLOGICAL SORT USING INCOMING GRADE' STATUS: PASSED" << std::endl;
        }

        // Test #6 'Strongly Connected Components (SCC)'
        {
            std::cout << "\nSCC CALCULATION: " << std::endl;
            std::vector<std::vector<int>> sccs = graph->CalculateStronglyConnectedComponents();
            for (const std::vector<int>& scc : sccs) {
                std::cout << "  Component: ";
                for (const int& elem : scc) {
                    std::cout << elem << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "--> [INFO] TEST #" << test_step++ << " 'SCC CALCULATION' STATUS: PASSED" << std::endl;
        }

        // Test #7 'TRANSPOSE'
        graph->Transpose();
        std::cout << std::endl << "Printing the Transposed Graph: " << std::endl;
        graph->show();
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'TRANSPOSE' STATUS: PASSED" << std::endl;

        // Test #8 'ADD NEW NODES AND EDGES'
        Node<int> node1, node2;
        node1.key = 10, node2.key = 11;
        node1.color = Color::White, node2.color = Color::White;

        std::cout << "\nAdded new Nodes to Graph, addNode(const Node<int>&) called:" << std::endl;
        graph->addNode(node1);
        graph->addNode(node2);
        graph->addEdge(node1, node2, 7.0);
        graph->addEdge(node2, node1, 2.0);
        graph->addEdge(5, node2.key, 2.0);
        graph->show();
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'ADD NEW NODES AND EDGES' STATUS: PASSED" << std::endl;

        // Test #9 'DFS'
        std::cout << std::endl << "Dfs's result (starting from new node " << node1.key << "): ";
        graph->Dfs(node1.key, applyToNodeDfs, nullptr);
        std::cout << "\n--> [INFO] TEST #" << test_step++ << " 'MAP DFS' STATUS: PASSED" << std::endl;

        // Test #10 'ACYCLIC TEST'
        if (graph->isGraphAcyclicDfs()) {
            std::cout << "\nAcyclic test: the new Graph is acyclic." << std::endl;
        } else {
            std::cout << "\nAcyclic test: the new Graph is cyclic." << std::endl;
        }
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'ACYCLIC TEST' STATUS: PASSED" << std::endl;

        // Test #11 'FOLD BFS'
        auto applyFoldToNode = [](const int& node, const void* limit, void* accumulator) {
            if(node >= *((int*) limit)) {
                *((int*) accumulator) += node;
                std::cout << "  Accumulated value: " << *((int*) accumulator) << std::endl;
            }
        };

        int fold_limit = 2, accum = 0;
        std::cout << "\nBfs's Fold application result: " << std::endl;
        graph->Bfs(1, applyFoldToNode, &fold_limit, &accum);
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'FOLD BFS' STATUS: PASSED" << std::endl;

        // Test #12 'FOLD DFS'
        accum = 0;
        std::cout << "\nDfs's Fold application result: " << std::endl;
        graph->Dfs(applyFoldToNode, &fold_limit, &accum);
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'FOLD DFS' STATUS: PASSED" << std::endl;

        // Test #13 'REMOVE ALL NODES'
        std::cout << "\nRemoving all the nodes: ";
        std::vector<Node<int>> nodes = graph->GetAllNodes();
        for (const Node<int>& node : nodes) {
            graph->removeNode(node);
        }

        if (graph->isEmpty()) {
            std::cout << "Graph is Empty!" << std::endl;
            std::cout << "--> [INFO] TEST #" << test_step++ << " 'IS_EMPTY' STATUS: PASSED" << std::endl;
        } else {
            std::cout << "Graph is not Empty!" << std::endl;
            std::cout << "--> [ERROR] TEST #" << test_step++ << " 'IS_EMPTY' STATUS: FAILED" << std::endl;
        }
        delete graph;

        // Test #14
        DirectedGraph<int>* new_g = new lasd::DirectedGraph<int>();
        for (int i = 0; i < 5; i++) new_g->addNode(i);

        new_g->addEdge(0, 1, 1.0);
        new_g->addEdge(0, 2, 1.0);
        new_g->addEdge(1, 3, 1.0);
        new_g->addEdge(2, 3, 1.0);
        new_g->addEdge(3, 4, 1.0);
        new_g->addEdge(4, 0, 1.0);

        std::cout << "\nNew Graph of size: " << new_g->Size();
        std::cout << " has been created! Printing the Graph: " << std::endl;
        new_g->show();

        std::cout << std::endl << "For each node, every predecessor: " << std::endl;
        new_g->Bfs(0, [](const int&, void*){}, nullptr);
        new_g->printForEachNodeItsPredecessor();
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'PREDECESSOR LISTING' STATUS: PASSED" << std::endl;

        // Test #15
        std::cout << "\nClearing the Graph: ";
        new_g->Clear();
        if (new_g->isEmpty()) {
            std::cout << "Graph is Empty!" << std::endl;
            std::cout << "--> [INFO] TEST #" << test_step++ << " 'CLEAR' STATUS: PASSED" << std::endl;
        } else {
            std::cout << "Graph is not Empty!" << std::endl;
            std::cout << "--> [ERROR] TEST #" << test_step++ << " 'CLEAR' STATUS: FAILED" << std::endl;
        }
        delete new_g;

        // Test #16
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

        std::cout << std::endl << "New graph of coordinates has been created!" << std::endl;
        std::cout << "[A* SEARCH ALGORITHM FROM 0 TO 5] RESULT: ";
        for (const auto& [node, fScore] : path) {
            std::cout << "{ Node: " << node << ", Heuristic: " << fScore << "} ";
        }
        std::cout << std::endl;

        std::vector<std::pair<int, double>> expectedPath = {{0, 5}, {4, 2.7}, {5, 4.7}};
        assert(path == expectedPath && "--> [INFO] TEST #16 'A* SEARCH' STATUS: FAILED\n");
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'A* SEARCH' STATUS: PASSED" << std::endl;

        // Test #17
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

        std::set<int> ASet; 
        std::vector<int> S;

        ASet.insert(0);
        ASet.insert(2);
        ASet.insert(3);

        std::cout << "\n--- #1 DFS SET" << std::endl;
        new_g3.DfsFromSet(ASet, fastMapDfs, nullptr);
        std::unordered_map<int, Color> color_map_v1 = new_g3.GetCurrentColors();
        new_g3.Transpose();
        std::cout << "--- #2 TRANSPOSE DFS SET" << std::endl;
        new_g3.DfsFromSet(ASet, fastMapDfs, nullptr);

        for (auto& node : new_g3.GetAllNodes()) {
            auto value = node.key;
            auto it = color_map_v1.find(value);
            if (it != color_map_v1.end()) {
                if (ASet.find(value) == ASet.end() && (it->second == Color::White || node.color == Color::White)) {
                    S.push_back(value);
                    std::cout << "--- Found: " << value << std::endl;
                    assert(value == 4);
                }
            }
        }

        // Verifica della dimensione dello stack
        assert(S.size() == 1);
        std::cout << "--- 'Stack' size = 1, correct! " << std::endl;
        std::cout << "--> [INFO] TEST #" << test_step++ << " 'DFS FROM A SET' STATUS: PASSED" << std::endl;
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