@echo off

g++ -std=c++17 -o build/win/example dijkstra/dijkstra.cpp ../graph.cpp main.cpp -Wall -I/mingw64/include -L/mingw64/lib -lglfw3 -lopengl32 -lm -lgdi32

if %ERRORLEVEL% EQU 0 (
    echo [ OK ] Compilation successful. Executable generated in /build/win folder.
) else (
    echo [ ERROR ] Encountered compilation errors. 
)

pause