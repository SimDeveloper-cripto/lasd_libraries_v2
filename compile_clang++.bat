@echo off

clang++ -std=c++17 -o3 -o bin/main -Wall LinkedList/linked_list.cpp Graph/graph.cpp myTest/test.cpp main.cpp

if %ERRORLEVEL% EQU 0 (
    echo [ OK ] Compilation successful. Executable generated in /bin folder.
) else (
    echo [ ERROR ] Encountered compilation errors. 
)

pause