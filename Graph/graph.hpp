#pragma once

#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <exception>
#include <stdbool.h>
#include <functional>

// GRAPH: IMPLEMENTATION BY ADJACENCY LISTS

namespace lasd {
    enum class Color { White, Gray, Black };

    template <typename Data>
    class Node {
    public:
        Data key;
        Color color;

        Node() = default;
        virtual ~Node() = default;

        bool operator==(const Node&) const noexcept = delete;
        bool operator!=(const Node&) const noexcept = delete;

        Node(const Data& value) : key(value), color(Color::White) {}

        // NOTE: A function to change node's color is not provided because only Graph (in theory) has to change colors.
    };

    template <typename Data>
    class Graph {
    private:
        std::map<Data, Node<Data>> Nodes;
        std::map<Data, std::vector<Data>> Adj;

        /* NOTE: DEFAULT IMPLEMENTATION OF DfsVisit
            The function pointer is provided just in case there is something you want to try and apply to each graph's node.
        */
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

        /* [YOUR CODE STARTS HERE] HERE INSERT YOUR CUSTOM DfsVisit */

            // THIS DfsVisit allows us to detect a cycle inside the Graph: it returns true if cycle is detected.
            bool DfsVisitAcyclic(const Data& u) {
                Nodes[u].color = Color::Gray;

                for (const Data& v : Adj[u]) {
                    if (Nodes[v].color == Color::White) {
                        DfsVisitAcyclic(v);
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

        // There is nothing special that led me to this conclusion: I just decided to do it like this
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
            if (Nodes.empty() && Adj.empty()) {
                std::cout << " Graph is empty." << std::endl;
            } else if (Adj.empty()) {
                std::cout << " Graph is free." << std::endl;
            } else {
                for (const auto& couple : Adj) {
                    const Data& from = couple.first;
                    const std::vector<Data>& adjs = couple.second;
                
                    std::cout << "      Node " << from << " -> ";
                
                    for (const Data& to : adjs) { std::cout << to << " "; }
                    std::cout << std::endl;
                }
            }
        }

        // DEFAULT IMPLEMENTATION OF Bfs
        void Bfs(const Data& source) noexcept;

        // DEFAULT IMPLEMENTATION OF Dfs, this could also be considered as Map()
        void Dfs(std::function<void(const Data&, void*)> visit, void* other) noexcept;

        // DEFAULT IMPLEMENTATION OF Dfs BUT STARTING FROM A SPECIFIC VERTEX, this could also be considered as Map()
        void Dfs(const Data& source, std::function<void(const Data&, void*)> visit, void* other) noexcept;

        // GET THE TRANSPOSED GRAPH (modifies it in-place)
        void Transpose(); // Returns a new instance of the Graph but Transposed.

        // GET TOPOLOGICAL ORDER OF THE GRAPH
        std::stack<Data> getTopologicalOrder();

        /* ************************************************************************ */

        /* [YOUR CODE STARTS HERE] HERE INSERT YOUR CUSTOM Dfs */
        // NOTE: Every function declared inside here must be defined in "graph.cpp" (in the correct section).

            bool isGraphAcyclicDfs() noexcept;
        /* [YOUR CODE ENDS HERE] */
    };
}