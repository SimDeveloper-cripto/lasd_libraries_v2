@echo off

set SRC_FILES=main.cpp
set LIBS=
set DEFS=-Wall -std=c++17

if "%1"=="--no-gl" (
  set DEFS=%DEFS% -DNO_GLFW
  echo [INFO] Compiling WITHOUT: glfw, freeglut
) else (
    set SRC_FILES=%SRC_FILES% dijkstra/dijkstra.cpp ..\graph.cpp
    set LIBS=-I/mingw64/include -L/mingw64/lib -lglfw3 -lopengl32 -lgdi32 -lfreeglut -lglu32 -lm
    echo [INFO] Compiling WITH glfw, freeglut
)

g++ %DEFS% %SRC_FILES% -o build\win\example %LIBS%

if %ERRORLEVEL% EQU 0 (
    echo [ OK ] Compilation successful. Executable generated in /build/win folder.
) else (
    echo [ ERROR ] Encountered compilation errors. 
)

pause