#pragma once

#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <exception>
#include <stdbool.h>
#include <functional>
#include <unordered_set>

// GRAPH: IMPLEMENTATION BY ADJACENCY LISTS

namespace lasd {
    enum class Color { White, Gray, Black };

    template <typename Data>
    class Node {
    private:
        unsigned long distance;
        Node* predecessor;

    public:
        Data key;
        Color color;

        Node() = default;
        virtual ~Node() = default;

        bool operator==(const Node&) const noexcept = delete;
        bool operator!=(const Node&) const noexcept = delete;

        Node(const Data& value) : key(value), color(Color::White) {}

        inline void setDistance(unsigned long distance) {
            this->distance = distance;
        }

        inline unsigned long getDistance() {
            return this->distance;
        }

        inline void setPredecessor(Node* predecessor) {
            this->predecessor = predecessor;
        }
        
        inline Node* getPredecessor() const {
            return this->predecessor;
        }

        // NOTE: A function to change node's color is not provided because Node<Data> is public.
    };

    template <typename Data>
    class Graph {
    private:
        std::map<Data, Node<Data>> Nodes;
        std::map<Data, std::vector<Data>> Adj;

        /* NOTE: DEFAULT IMPLEMENTATION OF DfsVisit
            The function pointer is provided just in case there is something you want to try and apply to each graph's node.
        */

        // Map()
        void DfsVisit(const Data& u, std::function<void(const Data&, void* other)> visit, void* other) {
            Nodes[u].color = Color::Gray;
            visit(u, other);

            for (const Data& v : Adj[u]) {
                if (Nodes[v].color == Color::White) {
                    DfsVisit(v, visit, other);
                }
            }
            Nodes[u].color = Color::Black;
        }

        // Fold()
        void DfsVisit(const Data& u, std::function<void(const Data&, const void*, void*)> visit, const void* par, void* acc) {
            Nodes[u].color = Color::Gray;
            visit(u, par, acc);

            for (const Data& v : Adj[u]) {
                if (Nodes[v].color == Color::White) {
                    DfsVisit(v, visit, par, acc);
                }
            }
            Nodes[u].color = Color::Black;
        }

        void DfsVisitTopological(const Data& u, std::stack<Data>& topologicalOrder) {
            Nodes[u].color = Color::Gray;

            for (const Data& v : Adj[u]) {
                if (Nodes[v].color == Color::White) {
                    DfsVisitTopological(v, topologicalOrder);
                }
            }

            Nodes[u].color = Color::Black;
            topologicalOrder.push(u);
        }

        /* [YOUR CODE STARTS HERE] HERE INSERT YOUR CUSTOM DfsVisit or everything else */

            // THIS DfsVisit allows us to detect a cycle inside the Graph: it returns true if cycle is detected.
            bool DfsVisitAcyclic(const Data& u) {
                Nodes[u].color = Color::Gray;

                for (const Data& v : Adj[u]) {
                    if (Nodes[v].color == Color::White) {
                        bool ret = DfsVisitAcyclic(v);
                        if (ret) return true;
                    } else if (Nodes[v].color == Color::Gray) {
                        return true;
                    }
                }
                Nodes[u].color = Color::Black;
                return false;
            }

        /* [YOUR CODE ENDS HERE] */

    public:
        Graph() = default;
        Graph(const Graph&);           // Copy Constructor
        Graph(Graph&& other) noexcept; // Move Constructor

        virtual ~Graph() = default;

        Graph& operator=(const Graph& other);     // Copy Assignment
        Graph& operator=(Graph&& other) noexcept; // Move Assignment

        bool operator==(const Graph&) const noexcept = delete;
        bool operator!=(const Graph&) const noexcept = delete;

        /* ************************************************************************ */

        // INITIALIZE NODE'S COLORS (AT LEAST FOR NOW)
        void Init();

        // CLEAR THE STRUCTURE
        void Clear();

        // ADD A NODE TO THE GRAPH
        void addNode(const Node<Data>& node) noexcept; // Since Node<Data> is public ...
        void addNode(const Data& key) noexcept;

        // ADD EDGE BETWEEN TO NODES
        void addEdge(const Node<Data>& node_from, const Node<Data>& node_to); // Since Node<Data> is public ...
        void addEdge(const Data& from, const Data& to);

        // SIMPLE FUNCTION TO PRINT GRAPH'S STRUCTURE
        void showGraph() const noexcept {
            if (Nodes.empty()) {
                std::cout << "  Graph is empty." << std::endl;
            } else {
                for (const auto& node_pair : Nodes) {
                    const Data& curr_key = node_pair.first;
                    std::cout << "  Node " << curr_key << " -> ";

                    if (Adj.find(curr_key) != Adj.end()) {
                        const std::vector<Data>& adjs = Adj.at(curr_key);
                        for (const Data& to : adjs) std::cout << to << " ";
                    }
                    std::cout << std::endl;
                }
            }
        }

        /* ************************************************************************ */

        /* Bfs, Dfs section ( Map() in PreOrder implementation ) */
        
        void Dfs(std::function<void(const Data&, void*)> visit, void* other) noexcept;              // Default implementation of Dfs
        void Dfs(const Data&, std::function<void(const Data&, void*)> visit, void* other) noexcept; // Dfs starting from specific vertex
        void Bfs(const Data&, std::function<void(const Data&, void*)> visit, void* other) noexcept; // Default implementation of Bfs
        
        /* Bfs, Dfs section ( Fold() in PreOrder implementation is provided ) */
        typedef std::function<void(const Data&, const void*, void*)> FoldFunctor;
        
        void Dfs(FoldFunctor, const void*, void*) noexcept;              // Default implementation of Fold() using Dfs
        void Dfs(const Data&, FoldFunctor, const void*, void*) noexcept; // Fold() using Dfs starting from specific vertex
        void Bfs(const Data&, FoldFunctor, const void*, void*) noexcept; // Default implementation of Fold() using Bfs

        /* ************************************************************************ */

        /* Bfs, Dfs section ( Map() in PostOrder implementation ) */

        // ...

        /* Bfs, Dfs section ( Fold() in PostOrder implementation ) */

        // ...

        /* ************************************************************************ */

        // GET THE TRANSPOSED GRAPH: returns a new instance of the Graph but Transposed
        void Transpose();

        // GET MINIMUM PATH BETWEEN TWO NODES
        std::vector<Data> GetMinimumPath(const Data& source, const Data& destination) noexcept;

        // GET TOPOLOGICAL ORDER/SORT OF THE GRAPH: in italian we call it topological-order
        std::stack<Data> getTopologicalOrder(bool print_message);
        std::vector<Data> getTopologicalOrderUsingIncomingGrade();

        /* ************************************************************************ */

        std::vector<std::vector<Data>> CalculateStronglyConnectedComponents() noexcept;

        /* ************************************************************************ */

        /* [YOUR CODE STARTS HERE] HERE INSERT YOUR CUSTOM Dfs */
        // NOTE: Every function declared inside here must be defined in "graph.cpp" (in the correct section).

            bool isGraphAcyclicDfs() noexcept;
            void printForEachNodeItsPredecessor() noexcept;
            // ...

        /* [YOUR CODE ENDS HERE] */
    };
}