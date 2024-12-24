# Documentation

## Enumerations

`enum class Color`

Represents the state of a node during graph traversal.

| __Value__ | __Description__                 |
|-----------|---------------------------------|
| `White`   | Node has not been visited       |
| `Gray`    | Node is currently being visited |
| `Black`   | Node has been fully processed   |

## Node Class

Represents a node in the graph.

| __Public Member__      | __Type__                                | __Description__                                        |
|------------------      |-----------------------------------------|------------------------------------------------------  |
| `key`                  | `Data`                                  | The data associated with the node                      |
| `color`                | `Color`                                 | The color state of the node (`White`, `Gray`, `Black`) |

| __Private Member__      | __Type__                         | __Description__                                     |
|------------------|-----------------------------------------|-----------------------------------------------------|
| `distance`       | `unsigned long`                          | Distance metric used in pathfinding algorithms     |
| `predecessors`   | `std::vector<Node*>`                     | List of predecessor nodes                          |

| __Method__                                | __Description__                                                                |
|-------------------------------------------|--------------------------------------------------------------------------------|
| `Node()`                                                  | Default constructor                                            |
| `Node(const Data& value)`                                 | Constructs a node with a specified `key` value                 |
| `void setDistance(unsigned long distance)`                | Sets the distance value for the node                           |
| `unsigned long getDistance() const`                       | Retrieves the current distance value                           |
| `void addPredecessor(Node* predecessor)`                  | Adds a predecessor to the node                                 |
| `std::vector<Node<Data>*>& getPredecessors()`             | Returns a modifiable reference to the predecessors vector      |
| `const std::vector<Node<Data>*>& getPredecessors() const` | Returns a const reference to the predecessors vector           |

---

## Edge Class

Represents an edge in the graph.

| __Member__       | __Type__        | __Description__                         |
|------------------|-----------------|-----------------------------------------|
| `to`             | `Data`          | The target node of the edge             |
| `weight`         | `double`        | The weight of the edge                  |

| __Method__                              | __Description__                                                            |
|-----------------------------------------|-----------------------------------------------------------------           |
| `Edge(const Data& to, double weight)`   | Constructs an edge pointing to the specified `to` node with a given weight |

---

## DirectedGraph Class

Represents the directed graph and provides all operations and algorithms.

| __Private Member__  | __Type__                                  | __Description__                 |
|------------------   |-----------------------------------------  |-------------------------------- |
| `Nodes`             | `std::map<Data, Node<Data>>`              | A map of all nodes in the graph |
| `Adj`               | `std::map<Data, std::vector<Edge<Data>>>` | Adjacency list for the graph    |

| __Method__                                   | __Description__                                                                                   |
|----------------------------------------------|---------------------------------------------------------------------------------                  |
| `DirectedGraph()`                                                                     | Default constructor                                      |
| `DirectedGraph(const DirectedGraph&)`                                                 | Copy constructor                                         |
| `DirectedGraph(DirectedGraph&& other) noexcept`                                       | Move constructor                                         |
| `DirectedGraph& operator=(const DirectedGraph&)`                                      | Copy assignment operator                                 |
| `DirectedGraph& operator=(DirectedGraph&& other) noexcept`                            | Move assignment operator                                 |
| `void Init() noexcept`                                                                | Initializes the graph                                    |
| `size_t Size() const noexcept`                                                        | Returns the total size of the graph                      |
| `bool isEmpty() const noexcept`                                                       | Checks whether the graph is empty                        |
| `void Clear() noexcept`                                                               | Clears all nodes and edges from the graph                |
| `void addNode(const Node<Data>& node)`                                                | Adds a node to the graph using an existing `Node` object |
| `void addNode(const Data& key)`                                                       | Adds a node to the graph using a `Data` key              |
| `void addEdge(const Node<Data>& node_from, const Node<Data>& node_to, double weight)` | Adds an edge between two nodes                           |
| `void addEdge(const Data& from, const Data& to, double weight)`                       | Adds an edge between two nodes identified by their keys  |
| `void removeNode(const Node<Data>& node)`                                             | Removes a node and its associated edges from the graph   |
| `void removeNode(Data& key)`                                                          | Removes a node (identified by its key) from the graph    |
| `std::vector<Node<Data>> GetAllNodes() const`                                         | Retrieves all nodes in the graph                         |
| `std::unordered_map<Data, Color> GetCurrentColors() const`                            | Gets the color state of all nodes in the graph           |
| `void show() const noexcept`                                                          | Prints the graph's adjacency structure to the console    |

### Traversals

`typedef std::function<void(const Data&, const void*, void*)> FoldFunctor`

| __Method__                                   | __Description__                                                                                    |
|----------------------------------------------|---------------------------------------------------------------------------------                   |
| `void Dfs(std::function<void(const Data&, void*)> visit, void* other) noexcept`                               | Performs a depth-first search (DFS) traversal of the graph, applying a map function to each node  |
| `void Dfs(const Data&, std::function<void(const Data&, void*)> visit, void* other) noexcept`                  | Starts a DFS traversal applying a map, starting from a specified node                             |
| `void Dfs(FoldFunctor, const void*, void*) noexcept`                                                          | Performs a DFS traversal using a fold function for custom aggregation of node data                |
| `void Dfs(const Data&, FoldFunctor, const void*, void*) noexcept`                                             | Starts a DFS traversal from a specified node, using a fold function for aggregation               |
| `void DfsFromSet(const std::set<Data>&, std::function<void(const Data&, void*)> visit, void* other) noexcept` | Performs DFS from a set of starting nodes, applying a map function                                |
| `void DfsFromSet(const std::set<Data>&, FoldFunctor, const void*, void*) noexcept`                            | Performs DFS from a set of starting nodes, using a fold function for aggregation                  |
| `void Bfs(const Data&, std::function<void(const Data&, void*)> visit, void* other) noexcept`                  | Performs a breadth-first search (BFS) traversal from a specified node, applying a map function    |
| `void Bfs(const Data&, FoldFunctor, const void*, void*) noexcept`                                             | Performs BFS from a specified node, using a fold function for aggregation                         |

### Algorithms

| __Method__                                   | __Description__                                                                  |
|----------------------------------------------|--------------------------------------------------------------------------------- |
| `void Transpose()`                                                                                                                                   | Creates the transpose of the graph by reversing the direction of all edges                    |
| `std::vector<Data> GetMinimumPath(const Data& source, const Data& destination) noexcept`                                                             | Finds the shortest path between two nodes using Dijkstra's algorithm                          |
| `std::stack<Data> getTopologicalSort(bool print_message)`                                                                                            | Returns a topological order of the graph's nodes. Prints a message if parameter is true       |
| `std::vector<Data> getTopologicalSortUsingIncomingGrade()`                                                                                           | Computes a topological sort of the graph using node in-degrees                                |
| `std::vector<std::pair<Data, double>> AStar(const Data& source, const Data& destination, std::function<double(const Data&, const Data&)> Heuristic)` | Finds the shortest path between two nodes using the A* algorithm, incorporating a heuristic   |
| `std::vector<std::vector<Data>> CalculateStronglyConnectedComponents() noexcept`                                                                     | Identifies and returns all strongly connected components in the graph                         |

---

### Utilities

| __Method__                                   | __Description__              |
|----------------------------------------------|------------------------------|
| `bool isGraphAcyclicDfs() noexcept`                                   | Returns true if the graph does not contain cycles |
| `void printForEachNodeItsPredecessor() noexcept`                      | Prints the predecessors list of each node         |

---

## Quick Start

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

// Get Minimum Path between two nodes
int main(void) {
    DirectedGraph<int>* graph = new lasd::DirectedGraph<int>();
    for (int i = 0; i < 7; ++i) graph->addNode(i);

    graph->addEdge(3, 1, 1.0);
    graph->addEdge(1, 2, 1.0);
    graph->addEdge(2, 3, 2.0);
    graph->addEdge(1, 4, 3.0);
    graph->addEdge(4, 5, 3.0);
    graph->addEdge(5, 6, 4.0);
    graph->addEdge(6, 4, 1.0);

    { /* [MIN PATH] START */
        int start = 1, end = 4;

        std::cout << std::endl;
        std::cout << "Minimum path between nodes " << start << " and " << end << ":" << std::endl;

        std::cout << "   Starting from " << start << ": ";
        for (const int vertex : graph->GetMinimumPath(start, end))
        std::cout << vertex << " ";

        /* OUTPUT: DIRECT PATH FROM 1 TO 4 (WEIGHT 3.0) */

        std::cout << std::endl << std::endl;
    } /* [MIN PATH] END */

    std::cout << "\nRemoving all the nodes: ";
    std::vector<Node<int>> nodes = graph->GetAllNodes();
    for (const Node<int>& node : nodes) graph->removeNode(node);

    graph->isEmpty() ? std::cout << "Graph is Empty!" : std::cout << "Graph is not Empty!" << std::endl;
    delete graph;
    return 0;
}
```

## Run Examples in Windows with g++ or clang++ (PowerShell)

__Warning__: For some of them, the library __glfw3__ is required. <br />

```bat
cd examples
.\compile_g++.bat
cd build/win
.\example
```

```bat
cd examples
.\compile_clang++.bat
cd build/win
.\example
```

## Run Examples in Linux with g++

```bash
```

## LICENSE

[GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/)
