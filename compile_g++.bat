@echo off

g++ -std=c++17 -o build/win/lasd -Wall LinkedList/linked_list.cpp DirectedGraph/graph.cpp test/test.cpp main.cpp

if %ERRORLEVEL% EQU 0 (
    echo [ OK ] Compilation successful. Executable generated in /build/win folder.
) else (
    echo [ ERROR ] Encountered compilation errors. 
)

pause