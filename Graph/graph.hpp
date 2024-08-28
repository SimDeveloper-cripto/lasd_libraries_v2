#pragma once

#include <set>
#include <map>
#include <cmath>
#include <stack>
#include <queue>
#include <limits>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <exception>
#include <stdbool.h>
#include <functional>
#include <unordered_set>

// WORK DONE: ORIENTED WEIGHTED GRAPH IMPLEMENTED BY ADJACENCY LISTS

namespace lasd {
    enum class Color { White, Gray, Black };

    template <typename Data>
    class Node {
    private:
        unsigned long distance;
        std::vector<Node*> predecessors;
        // Node* predecessor;

        /* [COMMENT SECTION]
            - Topic: print for each node its predecessors (every node has only one Node*)
            How would you do that? Using BFS.

            Graph<int>* graph = new lasd::Graph<int>();
            graph->addNode(0);
            graph->addNode(1);
            graph->addNode(2);
            graph->addNode(3);
            graph->addNode(4);

            graph->addEdge(0, 1, 1.0);
            graph->addEdge(0, 2, 1.0);
            graph->addEdge(1, 3, 1.0);
            graph->addEdge(2, 3, 1.0);
            graph->addEdge(3, 4, 1.0);
            graph->addEdge(4, 0, 1.0);

            // BFS FROM 0 to update Predecessors
            graph->Bfs(0, [](const int&, void*){}, nullptr);
            graph->printForEachNodeItsPredecessor();

            OUTPUT:
                Node 0 predecessor: None
                Node 1 predecessor: 0
                Node 2 predecessor: 0
                Node 3 predecessor: 1
                Node 4 predecessor: 3

                That is correct because:
                    - From node 2 we try to visit node 3, but since it has already been visited we don't update its predecessor.
                    - Same thing from node 4 to node 0.
            delete graph;

            That doesn't make any sense. Each node can have multiple incoming edges!
        */

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

        inline unsigned long getDistance() const {
            return this->distance;
        }

        // inline void setPredecessor(Node* predecessor) {
        //     this->predecessor = predecessor;
        // }
        
        // inline Node* getPredecessor() const {
        //     return this->predecessor;
        // }

        inline void addPredecessor(Node* predecessor) {
            this->predecessors.push_back(predecessor);
        }

        std::vector<Node<Data>*>& getPredecessors() {
            return predecessors;
        }

        const std::vector<Node<Data>*>& getPredecessors() const {
            return predecessors;
        }

        // NOTE: A function to change Node's Color is not provided because Node<Data> is public.
    };

    template <typename Data>
    class Edge {
    public:
        Data to;
        double weight;

        Edge(const Data& to, double weight) : to(to), weight(weight) {}
    };

    template <typename Data>
    class Graph {
    private:
        std::map<Data, Node<Data>> Nodes;
        std::map<Data, std::vector<Edge<Data>>> Adj;

        Color GetColor(const Data& node) const;
        std::vector<Node<Data>*> GetAdjacentNodes(const Data& node) const;

        // DFS MAP()
        void DfsVisit(const Data& u, std::function<void(const Data&, void* other)> visit, void* other) {
            Nodes[u].color = Color::Gray;
            visit(u, other);

            for (const Edge<Data>& edge : Adj[u]) {
                const Data& v = edge.to;
                if (Nodes[v].color == Color::White) {
                    DfsVisit(v, visit, other);
                }
            }
            Nodes[u].color = Color::Black;
        }

        // DFS FOLD()
        void DfsVisit(const Data& u, std::function<void(const Data&, const void*, void*)> visit, const void* par, void* acc) {
            Nodes[u].color = Color::Gray;
            visit(u, par, acc);

            for (const Edge<Data>& edge : Adj[u]) {
                const Data& v = edge.to;
                if (Nodes[v].color == Color::White) {
                    DfsVisit(v, visit, par, acc);
                }
            }
            Nodes[u].color = Color::Black;
        }

        void DfsVisitTopological(const Data& u, std::stack<Data>& topologicalOrder) {
            Nodes[u].color = Color::Gray;

            for (const Edge<Data>& edge : Adj[u]) {
                const Data& v = edge.to;
                if (Nodes[v].color == Color::White) {
                    DfsVisitTopological(v, topologicalOrder);
                }
            }

            Nodes[u].color = Color::Black;
            topologicalOrder.push(u);
        }

        bool DfsVisitAcyclic(const Data& u) {
            Nodes[u].color = Color::Gray;

            for (const Edge<Data>& edge : Adj[u]) {
                const Data& v = edge.to;
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

    public:
        Graph() = default;
        Graph(const Graph&);           // Copy Constructor
        Graph(Graph&& other) noexcept; // Move Constructor

        virtual ~Graph() = default;

        Graph& operator=(const Graph& other);     // Copy Assignment
        Graph& operator=(Graph&& other) noexcept; // Move Assignment

        bool operator==(const Graph&) const noexcept = delete;
        bool operator!=(const Graph&) const noexcept = delete;

        void Init();

        // CLEAR THE STRUCTURE
        void Clear();

        // ADD A NODE TO THE GRAPH
        void addNode(const Node<Data>& node) noexcept;
        void addNode(const Data& key) noexcept;

        // ADD EDGE BETWEEN TO NODES
        void addEdge(const Node<Data>& node_from, const Node<Data>& node_to, double weight);
        void addEdge(const Data& from, const Data& to, double weight);

        std::vector<Node<Data>> GetAllNodes() const;

	    // GET CURRENT STATE OF THE COLORS OF ALL THE NODES
	    std::unordered_map<Data, Color> GetCurrentColors() const;

        // SIMPLE FUNCTION TO PRINT GRAPH'S STRUCTURE
        void showGraph() const noexcept;

        // Bfs, Dfs section ( Map() in PreOrder implementation )
        void Dfs(std::function<void(const Data&, void*)> visit, void* other) noexcept;
        void Dfs(const Data&, std::function<void(const Data&, void*)> visit, void* other) noexcept;
        void Bfs(const Data&, std::function<void(const Data&, void*)> visit, void* other) noexcept;

        // TODO: IMPLEMENT BFS AND ALSO DFS/BFS FOLD
        void DfsFromSet(const std::set<Data>&, std::function<void(const Data&, void*)> visit, void* other) noexcept;

        // Bfs, Dfs section ( Fold() in PreOrder implementation is provided )
        typedef std::function<void(const Data&, const void*, void*)> FoldFunctor;
        
        void Dfs(FoldFunctor, const void*, void*) noexcept;
        void Dfs(const Data&, FoldFunctor, const void*, void*) noexcept;
        void Bfs(const Data&, FoldFunctor, const void*, void*) noexcept;

        // GET THE TRANSPOSED GRAPH: returns a new instance of the Graph but Transposed
        void Transpose();

        // GET MINIMUM PATH BETWEEN TWO NODES
        std::vector<Data> GetMinimumPath(const Data& source, const Data& destination) noexcept;

        // GET TOPOLOGICAL ORDER/SORT OF THE GRAPH: in italian we call it topological-order
        std::stack<Data> getTopologicalOrder(bool print_message);
        std::vector<Data> getTopologicalOrderUsingIncomingGrade();

        // Dijkstra's algorithm
        std::vector<Data> Dijkstra(const Data& source, const Data& destination);

        /* [ A* Search ] */
        // Data  : Node Value
        // double: Heuristic
        std::vector<std::pair<Data, double>> AStar(const Data& source, const Data& destination, std::function<double(const Data&, const Data&)> Heuristic);

        std::vector<std::vector<Data>> CalculateStronglyConnectedComponents() noexcept;

        /* [YOUR CODE STARTS HERE] HERE INSERT YOUR CUSTOM Dfs */
        // NOTE: Every function declared inside here must be defined in "graph.cpp" (in the correct section).

            bool isGraphAcyclicDfs() noexcept;
            void printForEachNodeItsPredecessor() noexcept;
            // ...

            // Euclidean Distance Heuristic Example
            double EuclideanDistance(const std::pair<int, int>& Node, const std::pair<int, int>& Destination) {
                int dx = Node.first  - Destination.first;
                int dy = Node.second - Destination.second;
                return std::sqrt((dx * dx) + (dy * dy));
            }

        /* [YOUR CODE ENDS HERE] */
    };
}
