#!/bin/sh
g++ -o3 -o build/linux/lasd -Wall LinkedList/linked_list.cpp DirectedGraph/graph.cpp test/test.cpp main.cpp
echo "[ OK ] Compilation successful. Executable generated in /build/linux folder."