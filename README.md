# Overview

This is a continuation and completion of lasd_libraries: <https://github.com/SimDeveloper-cripto/lasd_libraries> <br />
What I am focusing my work on the most is the __Weigthed and Oriented Graph data structure, which is implemented by adjacency lists__. <br />
Also, I used this library for the examination of algorithms and data structures. <br />
__Disclaimer:__ The usage of __non-primitive data types__ need more testing.

Things I want to add in the future for the Graph:

- A* Search Algorithm for std::pair<>
- PostOrder Map() and Fold() (both Bfs and Dfs)
- Bfs starting from a std::set<> (both Map and Fold)
- Visualization of State

New Data Structures I want to add:

- Doubly Linked List
- Priority Queue
- Min Heap

Todo:

- For now, the library does not Init() the Graph before applying the A* Search.
- Prepare a code example of usage.
- Work on a more organized test suite.

## Requirements

- gcc/g++ __v13.2.0__ or higher
- clang/clang++ __v17.0.4__ or higher

## Upcoming Development (new update)

I am developing a __Fully-Connected Multi-Layer Neural Network__! <br />
That's a work in progress so, at the moment, It is not usable and I recommend not to do It. <br />
I'll start working on it once finished the examination of NeuralNetworks (__DeepLearning Module__).  <br />
You can find the description in __test/NeuralNetwork/neural_network.hpp__. <br />

```bat
cd test/NeuralNetwork/nn_test/
.\compile_nn_clang++.bat
.\nn_lasd
```

## Code your personal TEST

By default, I provided for you a section dedicated to your personal test. <br />
In __test/test.hpp__ there is everything you'll need, including all the libraries and a personal namespace called "__usertest__". <br />
Your code has to be written inside the namespace at __test/test.cpp__ <br />
You can use the test code as a way to learn how to use the library. <br />
I don't forbid you from doing otherwise, but if you want to quickly test things you can do it this way. Have fun! <br />

### Compile and Execute the project in Windows with g++ or clang++ (PowerShell)

```bat
mkdir bin
.\compile_clang++.bat
cd bin
.\lasd
```

```bat
mkdir bin
.\compile_g++.bat
cd bin
.\lasd
```

### Compile and Execute the project in Linux

```bash
mkdir bin
chmod +x build.sh
./build.sh
cd bin
.\lasd
```

## Graph API



### Quick Start

Create a folder inside the root directory of the project:

```bash
mkdir user_test
cd user_test
```

Then, write your own main.cpp file:

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
