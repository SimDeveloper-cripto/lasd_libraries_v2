@echo off

g++ -o3 -o bin/main LinkedList/linked_list.cpp Graph\graph.cpp myTest/test.cpp main.cpp

if %ERRORLEVEL% EQU 0 (
    echo [ OK ] Compilation successful. Executable generated in /bin folder.
) else (
    echo [ ERROR ] Encountered compilation errors. 
)

pause