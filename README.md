# Overview

This is a continuation and completion of lasd_libraries: <https://github.com/SimDeveloper-cripto/lasd_libraries>. <br />
What I am focusing my work on the most is the __Weigthed and Oriented Graph data structure, which is implemented by adjacency lists__. <br />
Also, I used this library for the examination of algorithms and data structures. <br />
__Disclaimer:__ The usage of __non-primitive data types__ need more testing.

Things I want to add in the future for the Graph:

- A* Search Algorithm for std::pair<>
- PostOrder Map() and Fold() (both Bfs and Dfs)
- Visualization of State using OpenGL

New Data Structures I want to add:

- Doubly Linked List
- Priority Queue
- Min Heap
- Fibonacci Heap

Todo:

- Provide documentation also for the `LinkedList` library
- For now, the library does not Init() the Graph before applying the A* Search

## Requirements

- gcc/g++ __v13.2.0__ or higher
- clang/clang++ __v17.0.4__ or higher

## Graph API

Have a look at __DirectedGraph/api.md__ file. <br />
There you'll find a complete description of the library and also:

- A __quick start code__
- __Examples of usage__

## Code your personal TEST

By default, I provided for you a section dedicated to your personal test. <br />
In __test/test.hpp__ there is everything you'll need, including all the libraries and a personal namespace called "__usertest__". <br />
Your code has to be written inside the namespace at __test/test.cpp__. <br />
You can use the test code as a way to learn how to use the library. <br />
I don't forbid you from doing otherwise, but if you want to quickly test things you can do it this way. Have fun! <br />

### Compile and Execute the project in Windows with g++ or clang++ (PowerShell)

```bat
.\compile_clang++.bat
cd build/win
.\lasd
```

```bat
.\compile_g++.bat
cd build/win
.\lasd
```

### Compile and Execute the project in Linux with g++

```bash
chmod +x build.sh
./build.sh
cd build/linux
.\lasd
```

## Upcoming Development

I am developing a __Fully-Connected Multi-Layer Neural Network__! <br />
That's a work in progress so, at the moment, It is not usable and I recommend not to do It. <br />
I'll start working on it once finished the examination of NeuralNetworks (__DeepLearning Module__).  <br />
You can find the description in __test/NeuralNetwork/neural_network.hpp__. <br />

```bat
cd test/NeuralNetwork/nn_test/
.\compile_nn_clang++.bat
.\nn_lasd
```

## LICENSE

[GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/)
