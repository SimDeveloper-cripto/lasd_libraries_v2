#pragma once

#include <map>
#include <queue>
#include <vector>
#include <iostream>
#include <exception>
#include <stdbool.h>
#include <functional>

// ORIENTED GRAPH: IMPLEMENTATION BY ADJACENCY LISTS

namespace lasd {
    enum class Color { White, Gray, Black };

    template <typename Data>
    class Node {
    public:
        Data key;
        Color color;

        Node() = default;
        virtual ~Node() = default;

        Node(const Data& value) : key(value), color(Color::White) {}
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
        virtual ~Graph() = default;

        void Init();
        void addNode(const Data& key) noexcept;
        void addEdge(const Data& from, const Data& to);

        void showGraph() const noexcept {
            for (const auto& couple : Adj) {
                const Data& from = couple.first;
                const std::vector<Data>& adjs = couple.second;
                
                std::cout << "Node " << from << " -> ";
                
                for (const Data& to : adjs) { std::cout << to << " "; }
                std::cout << std::endl;
            }
        }

        // DEFAULT IMPLEMENTATION OF Bfs
        void Bfs(const Data& source) noexcept;

        // DEFAULT IMPLEMENTATION OF Dfs
        void Dfs(std::function<void(const Data&, void*)> visit, void* other) noexcept;

        // DEFAULT IMPLEMENTATION OF Dfs BUT STARTING FROM A SPECIFIC VERTEX
        void Dfs(const Data& source, std::function<void(const Data&, void*)> visit, void* other) noexcept;

        /* [YOUR CODE STARTS HERE] HERE INSERT YOUR CUSTOM Dfs */
        // NOTE: Every function declared inside here must be defined in "graph.cpp" (in the correct section).

            bool isGraphAcyclicDfs() noexcept;
        /* [YOUR CODE ENDS HERE] */
    };
}