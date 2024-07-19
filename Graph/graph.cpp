#include "graph.hpp"
#include <assert.h>

namespace lasd {
    template <typename Data>
    Graph<Data>::Graph(const Graph& other) {
        Adj   = other.Adj;
        Nodes = other.Nodes;
    }

    template <typename Data>
    Graph<Data>::Graph(Graph&& other) noexcept {
        std::swap(Adj, other.Adj);
        std::swap(Nodes, other.Nodes);
    }

    template <typename Data>
    Graph<Data>& Graph<Data>::operator=(const Graph& other) {
        if (this != &other) {
            Adj   = other.Adj;
            Nodes = other.Nodes;
        }
        return *this;
    }

    template <typename Data>
    Graph<Data>& Graph<Data>::operator=(Graph&& other) noexcept {
        if (this != &other) {
            std::swap(Adj, other.Adj);
            std::swap(Nodes, other.Nodes);
        }
        return *this;
    }

    template <typename Data>
    void Graph<Data>::Init() {
        for (auto& my_pair : Nodes) {
            my_pair.second.color = Color::White;
            my_pair.second.setDistance(std::numeric_limits<unsigned long>::max());
            my_pair.second.getPredecessors().clear();
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
    void Graph<Data>::addEdge(const Node<Data>& node_from, const Node<Data>& node_to, double weight) {
        if (Nodes.find(node_from.key) != Nodes.end() && Nodes.find(node_to.key) != Nodes.end()) {
            Adj[node_from.key].emplace_back(node_to.key, weight);
        } else {
            throw std::runtime_error("ERROR: addEdge() -> At least one of the nodes provided does not exist.");
        }
    }

    template <typename Data>
    void Graph<Data>::addEdge(const Data& from, const Data& to, double weight) {
        if (Nodes.find(from) != Nodes.end() && Nodes.find(to) != Nodes.end()) {
            Adj[from].emplace_back(to, weight);
        } else {
            throw std::runtime_error("ERROR: addEdge() -> At least one of the nodes provided does not exist.");
        }
    }

    template <typename Data>
    void Graph<Data>::showGraph() const noexcept {
        for (const auto& node : Nodes) {
            std::cout << "Node: " << node.first << " -> ";
            auto adjIt = Adj.find(node.first);
            if (adjIt != Adj.end()) {
                for (const auto& edge : Adj.at(node.first)) {
                    std::cout << edge.to << " (Weight: " << edge.weight << ") ";
                }
            }
            std::cout << std::endl;
        }
    }

    template <typename Data>
    void Graph<Data>::Dfs(std::function<void(const Data&, void*)> visit, void* other) noexcept {
        Init();
        for (auto& my_pair : Nodes) {
            if (my_pair.second.color == Color::White) {
                DfsVisit(my_pair.first, visit, other);
            }
        }
    }

    template <typename Data>
    void Graph<Data>::Dfs(const Data& u, std::function<void(const Data&, void*)> visit, void* other) noexcept {
        Init();
        DfsVisit(u, visit, other);
    }

    template <typename Data>
    void Graph<Data>::Bfs(const Data& u, std::function<void(const Data&, void*)> visit, void* other) noexcept {
        Init();
        Nodes[u].setDistance(0);
        std::queue<Data> queue;
        queue.push(u);

        while (!queue.empty()) {
            Data current = queue.front();
            queue.pop();
            visit(current, other);

            for (const Edge<Data>& edge : Adj[current]) {
                const Data& v = edge.to;
                if (Nodes[v].color == Color::White) {
                    Nodes[v].color = Color::Gray;
                    Nodes[v].setDistance(Nodes[current].getDistance() + 1);
                    Nodes[v].addPredecessor(&Nodes[current]);
                    queue.push(v);
                } else if (Nodes[v].getDistance() == Nodes[current].getDistance() + 1) {
                    Nodes[v].addPredecessor(&Nodes[current]);
                }
            }
            Nodes[current].color = Color::Black;
        }
    }

    template <typename Data>
    void Graph<Data>::Dfs(FoldFunctor visit, const void* par, void* acc) noexcept {
        Init();
        for (auto& my_pair : Nodes) {
            if (my_pair.second.color == Color::White) {
                DfsVisit(my_pair.first, visit, par, acc);
            }
        }
    }

    template <typename Data>
    void Graph<Data>::Dfs(const Data& u, FoldFunctor visit, const void* par, void* acc) noexcept {
        Init();
        DfsVisit(u, visit, par, acc);
    }

    template <typename Data>
    void Graph<Data>::Bfs(const Data& u, FoldFunctor visit, const void* par, void* acc) noexcept {
        Init();
        Nodes[u].setDistance(0);
        std::queue<Data> queue;
        queue.push(u);

        while (!queue.empty()) {
            Data current = queue.front();
            queue.pop();
            visit(current, par, acc);

            for (const Edge<Data>& edge : Adj[current]) {
                const Data& v = edge.to;
                if (Nodes[v].color == Color::White) {
                    Nodes[v].color = Color::Gray;
                    Nodes[v].setDistance(Nodes[current].getDistance() + 1);
                    Nodes[v].addPredecessor(&Nodes[current]);
                    queue.push(v);
                } else if (Nodes[v].getDistance() == Nodes[current].getDistance() + 1) {
                    Nodes[v].addPredecessor(&Nodes[current]);
                }
            }
            Nodes[current].color = Color::Black;
        }
    }

    template <typename Data>
    void Graph<Data>::Transpose() {
        std::map<Data, std::vector<Edge<Data>>> newAdj;
        for (const auto& [from, edges] : Adj) {
            for (const auto& edge : edges) {
                newAdj[edge.to].emplace_back(from, edge.weight);
            }
        }
        Adj = newAdj;
    }

// [OLD IMPLEMENTATION]
/* // THIS IS BEFORE USING WEIGHTS
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
*/

    template <typename Data>
    std::vector<Data> Graph<Data>::GetMinimumPath(const Data& source, const Data& destination) noexcept {
        // Dijkstra's Algorithm Implementation for Weighted Graphs
        return Dijkstra(source, destination);
    }

    template <typename Data>
    std::stack<Data> Graph<Data>::getTopologicalOrder(bool print_message) {
        std::stack<Data> topologicalOrder;
        Init();
        for (auto& my_pair : Nodes) {
            if (my_pair.second.color == Color::White) {
                DfsVisitTopological(my_pair.first, topologicalOrder);
            }
        }

        if (print_message) {
            std::cout << "Topological order: ";
            std::stack<Data> temp = topologicalOrder;
            while (!temp.empty()) {
                std::cout << temp.top() << " ";
                temp.pop();
            }
            std::cout << std::endl;
        }

        return topologicalOrder;
    }

    template <typename Data>
    std::vector<Data> Graph<Data>::getTopologicalOrderUsingIncomingGrade() {
        // This function calculates the topological order using the Incoming Grade (Kahn's Algorithm)
        std::map<Data, int> inDegree;
        for (const auto& node : Nodes) {
            inDegree[node.first] = 0;
        }

        for (const auto& [from, edges] : Adj) {
            for (const auto& edge : edges) {
                inDegree[edge.to]++;
            }
        }

        std::queue<Data> zeroInDegreeQueue;
        for (const auto& [node, degree] : inDegree) {
            if (degree == 0) {
                zeroInDegreeQueue.push(node);
            }
        }

        std::vector<Data> topologicalOrder;
        while (!zeroInDegreeQueue.empty()) {
            Data current = zeroInDegreeQueue.front();
            zeroInDegreeQueue.pop();
            topologicalOrder.push_back(current);

            for (const Edge<Data>& edge : Adj[current]) {
                inDegree[edge.to]--;
                if (inDegree[edge.to] == 0) {
                    zeroInDegreeQueue.push(edge.to);
                }
            }
        }

        if (topologicalOrder.size() != Nodes.size()) {
            throw std::runtime_error("ERROR: The graph is not a DAG, it has at least one cycle.");
        }

        return topologicalOrder;
    }

    // O((log V * (V + E)))
    template <typename Data>
    std::vector<Data> Graph<Data>::Dijkstra(const Data& source, const Data& destination) {
        std::priority_queue<std::pair<double, Data>, std::vector<std::pair<double, Data>>, std::greater<>> pq; // MIN-HEAP
        std::unordered_map<Data, double> distances;
        std::unordered_map<Data, Data> predecessors;

        for (const auto& node : Nodes) {
            distances[node.first] = std::numeric_limits<double>::max();
        }
        distances[source] = 0;
        pq.emplace(0, source);

        while (!pq.empty()) {
            Data current = pq.top().second;
            pq.pop();

            if (current == destination) {
                break;
            }

            for (const Edge<Data>& edge : Adj[current]) {
                double newDist = distances[current] + edge.weight;
                if (newDist < distances[edge.to]) {
                    distances[edge.to] = newDist;
                    predecessors[edge.to] = current;
                    pq.emplace(newDist, edge.to);
                }
            }
        }

        std::vector<Data> path;
        for (Data at = destination; at != source; at = predecessors[at]) {
            path.push_back(at);
        }
        path.push_back(source);
        std::reverse(path.begin(), path.end());
        return path;
    }

    // A* Search
    template <typename Data>
    std::vector<std::pair<Data, double>> Graph<Data>::AStar(const Data& source, const Data& destination, std::function<double(const Data&, const Data&)> Heuristic) {
        // TODO: SHOULD I IMPLEMENT INIT() HERE?
        std::map<Data, double> gScore, fScore;
        std::unordered_map<Data, Data> cameFrom;
        std::priority_queue<std::pair<double, Data>, std::vector<std::pair<double, Data>>, std::greater<std::pair<double, Data>>> pq; // MIN-HEAP

        /*
            - gScore: The cost of the shortest path from the source node to the current node as calculated so far by the algorithm.
            - fScore: The estimated total cost from the source node to the destination node if the path goes through the current node.
                -- The fScore is used as priority criteria (Queue).
                -- The priority queue always extracts the node with the lowest fScore, i.e. the node that appears to be closest to the destination in terms of estimated total cost.
        */

        for (const auto& node : Nodes) {
            gScore[node.first] = std::numeric_limits<double>::max();
            fScore[node.first] = std::numeric_limits<double>::max();
        }

        gScore[source] = 0;
        fScore[source] = Heuristic(source, destination);
        pq.emplace(fScore[source], source);

        while (!pq.empty()) {
            Data current = pq.top().second;
            pq.pop();

            if (current == destination) {
                std::vector<std::pair<Data, double>> path;
                for (Data at = destination; at != source; at = cameFrom[at]) {
                    path.emplace_back(at, fScore[at]);
                }
                path.emplace_back(source, fScore[source]);
                std::reverse(path.begin(), path.end());
                return path;
            }

            for (const auto& edge : Adj[current]) {
                Data neighbor = edge.to;
                double temp_gScore = gScore[current] + edge.weight;

                // For each neighbor, calculate the tentative gScore.
                // If it is lower than the current gScore for the neighbor, update the neighbor's gScore, fScore, and record the path in cameFrom MAP.
                if (temp_gScore < gScore[neighbor]) {
                    cameFrom[neighbor] = current;
                    gScore[neighbor] = temp_gScore;
                    fScore[neighbor] = gScore[neighbor] + Heuristic(neighbor, destination);
                    pq.emplace(fScore[neighbor], neighbor);
                }
            }
        }

        return {}; // If no path is found, return an empty vector.
    }
    
    template <typename Data>
    std::vector<std::vector<Data>> Graph<Data>::CalculateStronglyConnectedComponents() noexcept {
        std::stack<Data> stack;
        Init();

        for (const auto& node : Nodes) {
            if (node.second.color == Color::White) {
                DfsVisitTopological(node.first, stack);
            }
        }

        Graph<Data> transposedGraph = *this;
        transposedGraph.Transpose();
        transposedGraph.Init();

        std::vector<std::vector<Data>> sccs;
        while (!stack.empty()) {
            Data current = stack.top();
            stack.pop();

            if (transposedGraph.Nodes[current].color == Color::White) {
                std::vector<Data> scc;
                transposedGraph.Dfs(current, [&scc](const Data& node, void*) {
                    scc.push_back(node);
                }, nullptr);
                sccs.push_back(scc);
            }
        }
        return sccs;
    }

    template <typename Data>
    bool Graph<Data>::isGraphAcyclicDfs() noexcept {
        Init();
        for (auto& my_pair : Nodes) {
            if (my_pair.second.color == Color::White) {
                if (DfsVisitAcyclic(my_pair.first)) {
                    return false;
                }
            }
        }
        return true;
    }

    template <typename Data>
    void Graph<Data>::printForEachNodeItsPredecessor() noexcept {
        for (const auto& node : Nodes) {
            std::cout << "Node " << node.first << " predecessor: ";
            const auto& predecessors = node.second.getPredecessors();
            if (!predecessors.empty()) {
                for (const auto& pred : predecessors) {
                    std::cout << pred->key << " ";
                }
            } else {
                std::cout << "None";
            }
            std::cout << std::endl;
        }
    }

    template class Graph<int>;
    template class Graph<char>;
    template class Graph<std::string>;
}
