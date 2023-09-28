#include "graph.hpp"

namespace lasd {
    template <typename Data>
    void Graph<Data>::Init() {
        for (auto& my_pair : Nodes) {
            my_pair.second.color = Color::White;
        }
    }

    template <typename Data>
    void Graph<Data>::addNode(const Data& key) noexcept {
        if (Nodes.find(key) == Nodes.end()) {
            Node<Data> node(key);
            Nodes[key] = node;
        }
    }

    template <typename Data>
    void Graph<Data>::addEdge(const Data& from, const Data& to) {
        // Make sure the nodes exists
        if (Nodes.find(from) != Nodes.end() && Nodes.find(to) != Nodes.end()) {
            Adj[from].push_back(to);
        } else {
            throw std::runtime_error("ERROR: addEdge() -> at least one of the nodes provided do not exist.");
        }
    }

    template <typename Data>
    void Graph<Data>::Bfs(const Data& source) noexcept {
        Init();

        std::queue<Data> my_queue;
        my_queue.push(source);
        Nodes[source].color = Color::Gray;

        while (!my_queue.empty()) {
            Data head = my_queue.front();
            my_queue.pop();
            std::cout << "[QUEUE HEAD] Visiting: " << Nodes[head].key << std::endl;

            for (const Data& v : Adj[head]) {
                if (Nodes[v].color == Color::White) {
                    Nodes[v].color = Color::Gray;
                    my_queue.push(v);
                }
            }
            Nodes[head].color = Color::Black;
        }
    }

    template <typename Data>
    void Graph<Data>::Dfs(const Data& source, std::function<void(const Data&, void*)> visit, void* other) noexcept {
        Init();
        DfsVisit(source, visit, other);
    }

    /* [YOUR CODE STARTS HERE] HERE INSERT YOUR CUSTOM Dfs */

        template <typename Data>
        bool Graph<Data>::isGraphCyclicDfs(const Data& source) noexcept {
            Init();
            return DfsVisit(source); // It calls DfsVisit, the one that returns a boolean.

            // NOTE: DfsVisit(const Data& source) is defined inside the private scope of Graph, "graph.hpp".
        }

    /* [YOUR CODE ENDS HERE] */

    template class Graph<int>;
    template class Graph<float>;
    template class Graph<double>;
    template class Graph<std::string>;
}