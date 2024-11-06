# Overview

This is a continuation and completion of lasd_libraries: <https://github.com/SimDeveloper-cripto/lasd_libraries> <br />
What I have focused my work on the most is the Weigthed and Oriented Graph data structure, which is implemented by adjacency lists. <br />
I used this library for the examination of algorithms and data structures. <br />
This is my first ever try in implementing something like this so any help is well accepted! <br />

Things I want to add in the future for the Graph:

- A* Search Algorithm for std::pair<>
- PostOrder Map() and Fold() (both Bfs and Dfs)
- Bfs starting from a std::set<> (both Map and Fold)

New Data Structures I want to add:

- Doubly Linked List
- Priority Queue
- Min Heap

Todo:

- For now, the library does not Init() the Graph before applying the A* Search.

## Requirements

- gcc/g++ __v13.2.0__ or higher
- clang/clang++ __v17.0.4__ or higher

## Upcoming Development (new update)

I am developing a __Full-Connected Multi-Layer Neural Network__! <br />
That's a work in progress so, at the moment, It is not usable and I recommend not to do It. <br />
I'll start working on it once finished the examination of NeuralNetworks (__DeepLearning Module__).  <br />
You can find the description in __test/NeuralNetwork/neural_network.hpp__. <br />

```bat
cd test/NeuralNetwork/nn_test/
.\compile_nn_clang++.bat
.\nn_lasd
```

## Tutorial: Code your personal test

By default, I provided for you a section dedicated to your personal test. <br />
In __test/test.hpp__ there is everything you'll need, including all the libraries and a personal namespace called "__usertest__". <br />
Your code has to be written inside the namespace at __test/test.cpp__ <br />
I don't forbid you from doing otherwise, but if you want to quickly test things you can do it this way. Have fun! <br />

### Compile and Execute the project in Windows with G++ or CLANG++ (PowerShell)

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

## LICENSE

[MIT](https://choosealicense.com/licenses/mit/)
