@echo off

g++ -std=c++17 -o3 -o bin/lasd -Wall LinkedList/linked_list.cpp Graph/graph.cpp test/test.cpp main.cpp

if %ERRORLEVEL% EQU 0 (
    echo [ OK ] Compilation successful. Executable generated in /bin folder.
) else (
    echo [ ERROR ] Encountered compilation errors. 
)

pause