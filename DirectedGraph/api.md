# Documentation

## Enumerations

`enum class Color`

Represents the state of a node during graph traversal.

| __Value__ | __Description__                  |
|-----------|----------------------------------|
| `White`   | Node has not been visited.       |
| `Gray`    | Node is currently being visited. |
| `Black`   | Node has been fully processed.   |

## Node Class

Represents a node in the graph.

| __Public Member__      | __Type__                                | __Description__                                         |
|------------------      |-----------------------------------------|------------------------------------------------------   |
| `key`                  | `Data`                                  | The data associated with the node.                      |
| `color`                | `Color`                                 | The color state of the node (`White`, `Gray`, `Black`). |

| __Private Member__      | __Type__                         | __Description__                                      |
|------------------|-----------------------------------------|------------------------------------------------------|
| `distance`       | `unsigned long`                          | Distance metric used in pathfinding algorithms.     |
| `predecessors`   | `std::vector<Node*>`                     | List of predecessor nodes.                          |

| __Method__                                | __Description__                                                                 |
|-------------------------------------------|---------------------------------------------------------------------------------|
| `Node()`                                                  | Default constructor.                                            |
| `Node(const Data& value)`                                 | Constructs a node with a specified `key` value.                 |
| `void setDistance(unsigned long distance)`                | Sets the distance value for the node.                           |
| `unsigned long getDistance() const`                       | Retrieves the current distance value.                           |
| `void addPredecessor(Node* predecessor)`                  | Adds a predecessor to the node.                                 |
| `std::vector<Node<Data>*>& getPredecessors()`             | Returns a modifiable reference to the predecessors vector.      |
| `const std::vector<Node<Data>*>& getPredecessors() const` | Returns a const reference to the predecessors vector.           |

---

## Edge Class

Represents an edge in the graph.

| __Member__       | __Type__        | __Description__                          |
|------------------|-----------------|------------------------------------------|
| `to`             | `Data`          | The target node of the edge.             |
| `weight`         | `double`        | The weight of the edge.                  |

| __Method__                              | __Description__                                                             |
|-----------------------------------------|-----------------------------------------------------------------            |
| `Edge(const Data& to, double weight)`   | Constructs an edge pointing to the specified `to` node with a given weight. |

---

## DirectedGraph Class

Represents the directed graph and provides all operations and algorithms.

| __Private Member__  | __Type__                                  | __Description__                  |
|------------------   |-----------------------------------------  |--------------------------------  |
| `Nodes`             | `std::map<Data, Node<Data>>`              | A map of all nodes in the graph. |
| `Adj`               | `std::map<Data, std::vector<Edge<Data>>>` | Adjacency list for the graph.    |

| __Method__                                   | __Description__                                                                                    |
|----------------------------------------------|---------------------------------------------------------------------------------                   |
| `DirectedGraph()`                                                                     | Default constructor.                                      |
| `DirectedGraph(const DirectedGraph&)`                                                 | Copy constructor.                                         |
| `DirectedGraph(DirectedGraph&& other) noexcept`                                       | Move constructor.                                         |
| `DirectedGraph& operator=(const DirectedGraph&)`                                      | Copy assignment operator.                                 |
| `DirectedGraph& operator=(DirectedGraph&& other) noexcept`                            | Move assignment operator.                                 |
| `void Init() noexcept`                                                                | Initializes the graph.                                    |
| `size_t Size() const noexcept`                                                        | Returns the total size of the graph.                      |
| `bool isEmpty() const noexcept`                                                       | Checks whether the graph is empty.                        |
| `void Clear() noexcept`                                                               | Clears all nodes and edges from the graph.                |
| `void addNode(const Node<Data>& node)`                                                | Adds a node to the graph using an existing `Node` object. |
| `void addNode(const Data& key)`                                                       | Adds a node to the graph using a `Data` key.              |
| `void addEdge(const Node<Data>& node_from, const Node<Data>& node_to, double weight)` | Adds an edge between two nodes.                           |
| `void addEdge(const Data& from, const Data& to, double weight)`                       | Adds an edge between two nodes identified by their keys.  |
| `void removeNode(const Node<Data>& node)`                                             | Removes a node and its associated edges from the graph.   |
| `void removeNode(Data& key)`                                                          | Removes a node (identified by its key) from the graph.    |
| `std::vector<Node<Data>> GetAllNodes() const`                                         | Retrieves all nodes in the graph.                         |
| `std::unordered_map<Data, Color> GetCurrentColors() const`                            | Gets the color state of all nodes in the graph.           |
| `void show() const noexcept`                                                          | Prints the graph's adjacency structure to the console.    |

### Traversals

`typedef std::function<void(const Data&, const void*, void*)> FoldFunctor`

| __Method__                                   | __Description__                                                                                    |
|----------------------------------------------|---------------------------------------------------------------------------------                   |
| `void Dfs(std::function<void(const Data&, void*)> visit, void* other) noexcept`                               | |
| `void Dfs(const Data&, std::function<void(const Data&, void*)> visit, void* other) noexcept`                  | |
| `void Dfs(FoldFunctor, const void*, void*) noexcept`                                                          | |
| `void Dfs(const Data&, FoldFunctor, const void*, void*) noexcept`                                             | |
| `void DfsFromSet(const std::set<Data>&, std::function<void(const Data&, void*)> visit, void* other) noexcept` | |
| `void DfsFromSet(const std::set<Data>&, FoldFunctor, const void*, void*) noexcept`                            | |
| `void Bfs(const Data&, std::function<void(const Data&, void*)> visit, void* other) noexcept`                  | |
| `void Bfs(const Data&, FoldFunctor, const void*, void*) noexcept`                                             | |

### Algorithms

| __Method__                                   | __Description__                                                                                            |
|----------------------------------------------|---------------------------------------------------------------------------------                           |
| `void Transpose()`                                                                                                                                   | |
| `std::vector<Data> GetMinimumPath(const Data& source, const Data& destination) noexcept`                                                             | |
| `std::stack<Data> getTopologicalSort(bool print_message)`                                                                                            | |
| `std::vector<Data> getTopologicalSortUsingIncomingGrade()`                                                                                           | |
| `std::vector<std::pair<Data, double>> AStar(const Data& source, const Data& destination, std::function<double(const Data&, const Data&)> Heuristic)` | |
| `std::vector<std::vector<Data>> CalculateStronglyConnectedComponents() noexcept`                                                                     | |

---

### Utilities

| __Method__                                   | __Description__              |
|----------------------------------------------|------------------------------|
| `bool isGraphAcyclicDfs() noexcept`                                   | Returns true if the graph does not contain cycles. |
| `void printForEachNodeItsPredecessor() noexcept`                      | Prints the predecessors list of each node.         |

---

## Quick Start Example

Create a folder inside the root directory of the project.

```bash
mkdir user_test
cd user_test
```

Then, write your own main.cpp file.

```cpp
// main.cpp
#include "../DirectedGraph/graph.hpp"

using namespace lasd;

// You can also find this code in test/test.cpp (graph test)
int main(void) {
    DirectedGraph<int> g;
    for (int i = 0; i < 7; i++) g.addNode(i);

    g.addEdge(1, 0, 1.0);
    g.addEdge(0, 6, 1.0);
    g.addEdge(6, 5, 1.0);
    g.addEdge(5, 0, 1.0);
    g.addEdge(0, 1, 1.0);
    g.addEdge(4, 2, 1.0);
    g.addEdge(4, 3, 1.0);
    g.addEdge(2, 0, 1.0);
    g.addEdge(3, 6, 1.0);

    std::set<int> ASet; // Use a Set to get O(log(n)) as search complexity.
    std::vector<int> S;
        
    ASet.insert(0);
    ASet.insert(2);
    ASet.insert(3);
        
    std::cout << "--- #1 DFS SET" << std::endl;
    g.DfsFromSet(ASet, fastMapDfs, nullptr);
    std::unordered_map<int, Color> color_map_v1 = g.GetCurrentColors();
    g.Transpose();
    std::cout << "--- #2 TRANSPOSE DFS SET" << std::endl;
    g.DfsFromSet(ASet, fastMapDfs, nullptr);

    for (auto& node : g.GetAllNodes()) {
        auto value = node.key;
        std::unordered_map<int, Color>::iterator it = color_map_v1.find(value);
        if (it != color_map_v1.end()) {
            // We only check the nodes which aren't inside the Set.
            if (ASet.find(value) == ASet.end() && (it->second == Color::White || node.color == Color::White)) {
                S.push_back(value);
                std::cout << "--- Found: " << value << std::endl; // It will print "Found: 4".
                assert(value == 4);
            }
        }
    }

    // ASSERT CORRECT STACK SIZE
    assert(S.size() == 1);
    return 0;
}
```

## LICENSE

[GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/)
