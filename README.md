# Overview

This is a continuation and completion of lasd_libraries: <https://github.com/SimDeveloper-cripto/lasd_libraries>. <br />
What I have focused my work on the most is the __Weigthed and Oriented Graph data structure, which is implemented by adjacency lists__ and my __Feed-Forward Neural Network__. <br />
Also, I used this library for the examination of `algorithms and data structures`, `machine learning` and many other applications! <br />
__Disclaimer:__ The usage of __non-primitive data types__ need more testing.

New Data Structures I want to add:

- Doubly Linked List
- Priority Queue
- Min Heap
- Fibonacci Heap

Todo:

- Provide documentation also for the `LinkedList` library
- `Create unit tests` for PostOrder Map and Fold (both for Bfs and Dfs)

## Requirements

- make
- cmake
- gcc/g++ __v13.2.0__ or higher
- clang/clang++ __v17.0.4__ or higher

```sh
# on Linux
sudo apt install nlohmann-json3-dev
```

## Graph API

Have a look at __DirectedGraph/README.md__ file. <br />
There you'll find a complete description of the library and also:

- A __quick start code__
- __Examples of usage__

### Code your personal TEST

By default, I provided for you a section dedicated to your personal test. <br />
In __test/test.hpp__ there is everything you'll need, including all the libraries and a personal namespace called "__usertest__". <br />
Your code has to be written inside the namespace at __test/test.cpp__. <br />
You can use the test code as a way to learn how to use the library. <br />
I don't forbid you from doing otherwise, but if you want to quickly test things you can do it this way. Have fun! <br />

### Compile and Execute Graph API

```bat
cd ~/lasd_libraries_v2
make
```

## Feed-Forward API (NeuraNova)

I am re-creating in C++ what I've built before, from scratch, [__NeuraNova__](https://github.com/SimDeveloper-cripto/neura_nova.git) (also from scratch but in python3).  <br />
It is recommended to look up that repository 'cause you'll find also a __Convolutional Neural Network__ implementation. <br>
For more details, have a look at __NeuraNova/README.md__ file. <br />

### Compile and Execute NeuraNova

```bat
cd ~/lasd_libraries_v2/NeuraNova
make all
make run
```

## LICENSE

[GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/)

Copyright © 2024 Simone Catapano "SimDeveloper-cripto".