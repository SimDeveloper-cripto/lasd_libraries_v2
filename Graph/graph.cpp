#include "graph.hpp"
#include <assert.h>

namespace lasd {
    template <typename Data>
    Graph<Data>::Graph(const Graph& other) {
        Adj = other.Adj;
        Nodes = other.Nodes;
    }

    template <typename Data>
    Graph<Data>::Graph(Graph&& other) noexcept {
        std::swap(Adj, other.Adj);
        std::swap(Nodes, other.Nodes);

        // Adj = std::move(other.Adj);
        // Nodes = std::move(other.Nodes);
    }

    template <typename Data>
    Graph<Data>& Graph<Data>::operator=(const Graph& other) {
        if (this != &other) {
            Adj = other.Adj;
            Nodes = other.Nodes;
        }
        return *this;
    }

    template <typename Data>
    Graph<Data>& Graph<Data>::operator=(Graph&& other) noexcept {
        if (this != &other) {
            std::swap(Adj, other.Adj);
            std::swap(Nodes, other.Nodes);
            
            // Adj = std::move(other.Adj);
            // Nodes = std::move(other.Nodes);
        }
        return *this;
    }

    template <typename Data>
    void Graph<Data>::Init() {
        for (auto& my_pair : Nodes) {
            my_pair.second.color = Color::White;
            my_pair.second.setDistance(0);
            my_pair.second.setPredecessor(nullptr);
        }
    }

    template <typename Data>
    void Graph<Data>::Clear() {
        Nodes.clear();
        Adj.clear();
        Init();
    }

    template <typename Data>
    void Graph<Data>::addNode(const Node<Data>& node) noexcept {
        Data key = node.key;
        if (Nodes.find(key) == Nodes.end()) {
            Node<Data> new_node(key);
            Nodes[key] = new_node;
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
    void Graph<Data>::addEdge(const Node<Data>& node_from, const Node<Data>& node_to) {
        if (Nodes.find(node_from.key) != Nodes.end() && Nodes.find(node_to.key) != Nodes.end()) {
            Adj[node_from.key].push_back(node_to.key);
        } else {
            throw std::runtime_error("ERROR: addEdge() -> at least one of the nodes provided do not exist.");
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

    /* ************************************************************************ */

    // Default implementation of Map() using Bfs
    template <typename Data>
    void Graph<Data>::Bfs(const Data& source, std::function<void(const Data&, void*)> visit, void* other) noexcept {
        Init();

        std::queue<Data> my_queue;
        my_queue.push(source);
        Nodes[source].color = Color::Gray;

        while (!my_queue.empty()) {
            Data head = my_queue.front();
            my_queue.pop();
            visit(head, other);

            for (const Data& v : Adj[head]) {
                if (Nodes[v].color == Color::White) {
                    Nodes[v].color = Color::Gray;
                    Nodes[v].setDistance(Nodes[head].getDistance()+ 1);
                    Nodes[v].setPredecessor(&Nodes[head]);
                    my_queue.push(v);
                }
            }
            Nodes[head].color = Color::Black;
        }
    }

    // Default implementation of Map() using Dfs
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

    // Default implementation of Map() using Dfs, starting from a specific vertex
    template <typename Data>
    void Graph<Data>::Dfs(const Data& source, std::function<void(const Data&, void*)> visit, void* other) noexcept {
        Init();
        DfsVisit(source, visit, other);
    }

    /* ************************************************************************ */

    // Default implementation of Fold() using Bfs
    template <typename Data>
    void Graph<Data>::Bfs(const Data& source, FoldFunctor func, const void* par, void* acc) noexcept {
        Init();

        std::queue<Data> my_queue;
        my_queue.push(source);
        Nodes[source].color = Color::Gray;

        while (!my_queue.empty()) {
            Data head = my_queue.front();
            my_queue.pop();
            func(head, par, acc);

            for (const Data& v : Adj[head]) {
                if (Nodes[v].color == Color::White) {
                    Nodes[v].color = Color::Gray;
                    Nodes[v].setDistance(Nodes[head].getDistance()+ 1);
                    Nodes[v].setPredecessor(&Nodes[head]);
                    my_queue.push(v);
                }
            }
            Nodes[head].color = Color::Black;
        }
    }

    // Default implementation of Fold() using Dfs
    template <typename Data>
    void Graph<Data>::Dfs(FoldFunctor func, const void* par, void* acc) noexcept {
        Init();

        for (typename std::map<Data, Node<Data>>::const_iterator it = Nodes.begin(); it != Nodes.end(); it++) {
            const Node<Data>& currNode = it->second; // Contains Node<Data> field
            if (currNode.color == Color::White) {
                DfsVisit(currNode.key, func, par, acc);
            }
        }
    }

    // Default implementation of Fold() using Dfs, starting from a specific vertex
    template <typename Data>
    void Graph<Data>::Dfs(const Data& source, FoldFunctor func, const void* par, void* acc) noexcept {
        Init();
        DfsVisit(source, func, par, acc);
    }

    /* ************************************************************************ */

    template <typename Data>
    std::vector<Data> Graph<Data>::GetMinimumPath(const Data& source, const Data& destination) noexcept {
        std::vector<Data> path;
        if (Nodes.find(source) == Nodes.end() || Nodes.find(destination) == Nodes.end()) return path;

        Node<Data>* current = &Nodes[destination];
        while (current && current->key != source) {
            path.push_back(current->key);
            current = current->getPredecessor();
        }

        if (current && current->key == source)
            path.push_back(current->key);

        std::reverse(path.begin(), path.end());
        return path;
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
    std::stack<Data> Graph<Data>::getTopologicalOrder(bool print_message) {
        /* If Graph is cyclic, Topological-Order is a partial order. */
        if (print_message)
            if (!isGraphAcyclicDfs()) std::cout << "\n  The Graph is cyclic! The calculated order is partial: ";

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

    template <typename Data>
    std::vector<Data> Graph<Data>::getTopologicalOrderUsingIncomingGrade() {
        assert(isGraphAcyclicDfs() == true && "The Graph is cyclic! You can't calculate Topological Order!");

        std::map<Data, int> incomingGrades;
        
        /* [START] CALCULATE INCOMING GRADE FOR EACH NODE */

        for (const auto& node : Nodes) {
            const Data& key = node.first;
            incomingGrades[key] = 0;
        }

        for (const auto& node : Nodes) {
            const Data& key = node.first;
            for (const Data& neighbor : Adj[key]) {
                incomingGrades[neighbor]++;
            }
        }

        /* [END] */

        std::queue<Data> order_queue;
        std::vector<Data> result; // This is what gets returned

        for (const auto& node : Nodes) {
            const Data& key = node.first;
            if (incomingGrades[key] == 0) { order_queue.push(key); }
        }    

        // Perform sorting
        while (!order_queue.empty()) {
            Data current_node = order_queue.front();

            order_queue.pop();
            result.insert(result.begin(), current_node);

            for (const Data& neighbor : Adj[current_node]) {
                incomingGrades[neighbor]--;
                if (incomingGrades[neighbor] == 0) { order_queue.push(neighbor); }
            }
        }

        return result;
    }

    // KOSARAJU'S ALGORITHM
    template <typename Data>
    std::vector<std::vector<Data>> Graph<Data>::CalculateStronglyConnectedComponents() noexcept {
        std::stack<Data> topologicalOrder = getTopologicalOrder(false);
        std::vector<std::vector<Data>> sccs; // For each SCC, we store the vertices

        Transpose();
        Init();
        while (!topologicalOrder.empty()) {
            Data vertex = topologicalOrder.top();
            topologicalOrder.pop();

            if (Nodes[vertex].color == Color::White) {
                std::vector<Data> component; // Elements inside the SCC

                DfsVisit(vertex, [] (const Data& data, void* other) {
                    std::vector<Data>& comp = *static_cast<std::vector<Data>*>(other);
                    comp.push_back(data);
                }, &component);

                if (!component.empty()) sccs.push_back(component);
            }
        }

        Transpose(); // Back to previous 
        Init();
        return sccs;
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

        template <typename Data>
        void Graph<Data>::printForEachNodeItsPredecessor() noexcept {
            for (const auto& node : Nodes) {
                const Data& key = node.first;
                const Node<Data>& curr = node.second;
                const Node<Data>* pred = curr.getPredecessor();
                std::cout << "  Node: " << key;
                if (pred) 
                    std::cout << ", Predecessor: " << pred->key << std::endl;
                else
                    std::cout << ", Predecessor: nullptr" << std::endl;                    
            }
        }

    /* [YOUR CODE ENDS HERE] */

    template class Graph<int>;
}