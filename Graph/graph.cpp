#include "graph.hpp"

namespace lasd {
    template <typename Data>
    void Graph<Data>::Init() {
        for (auto& my_pair : Nodes) {
            my_pair.second.color = Color::White;
        }
    }

    template <typename Data>
    void Graph<Data>::Clear() {
        Nodes.clear();
        Adj.clear();
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

    // DEFAULT Dfs
    template <typename Data>
    void Graph<Data>::Dfs(std::function<void(const Data&, void*)> visit, void* other) noexcept {
        Init();

        for (typename std::map<Data, Node<Data>>::const_iterator it = Nodes.begin(); it != Nodes.end(); it++) {
            const Node<Data>& currNode = it->second; // Contains Node<Data> field
            if (currNode.color == Color::White) {
                DfsVisit(currNode.key, visit, other);
            }
        }
    }

    // DEFAULT Dfs: STARTING FROM A SPECIFIC VERTEX
    template <typename Data>
    void Graph<Data>::Dfs(const Data& source, std::function<void(const Data&, void*)> visit, void* other) noexcept {
        Init();
        DfsVisit(source, visit, other);
    }

    template <typename Data>
    void Graph<Data>::Transpose() {
        std::map<Data, std::vector<Data>> temp = Adj;
        Adj.clear();

        // Add Edges in reverse direction.
        for (const auto& nPair : Nodes) {
            const Data& from = nPair.first;
            for (const Data& to : temp[from]) {
                addEdge(to, from);
            }
        }
    }

    template <typename Data>
    std::stack<Data> Graph<Data>::getTopologicalOrder() {
        Init();
        std::stack<Data> topologicalOrder {};

        for (typename std::map<Data, Node<Data>>::const_iterator it = Nodes.begin(); it != Nodes.end(); it++) {
            const Node<Data>& current = it->second; // Contains Node<Data> field
            if (current.color == Color::White) {
                DfsVisitTopological(current.key, topologicalOrder);
            }
        }
        return topologicalOrder;
    }

    /* [YOUR CODE STARTS HERE] HERE INSERT YOUR CUSTOM Dfs */

        template <typename Data>
        bool Graph<Data>::isGraphAcyclicDfs() noexcept {
            Init();

            for (typename std::map<Data, Node<Data>>::const_iterator it = Nodes.begin(); it != Nodes.end(); it++) {
                const Node<Data>& currNode = it->second; // Contains Node<Data> field
                if (currNode.color == Color::White) {
                    bool ret = DfsVisitAcyclic(currNode.key); // It calls DfsVisit, the one that returns a boolean.
                    if (ret)
                        return false;
                }
            }
            return true;
            // NOTE: DfsVisitAcyclic(const Data& source) is defined inside the private scope of Graph, "graph.hpp".
        }

    /* [YOUR CODE ENDS HERE] */

    template class Graph<int>;
    template class Graph<float>;
    template class Graph<double>;
    template class Graph<std::string>;
}