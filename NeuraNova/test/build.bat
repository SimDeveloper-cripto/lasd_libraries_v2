@echo off

clang++ -std=c++17 -o3 -o neura_nova -Wall ../neuron.cpp ../layer.cpp ../neural_network.cpp ../activation_functions.cpp test.cpp

if %ERRORLEVEL% EQU 0 (
    echo [ OK ] Compilation successful. Executable 'neura_nova' generated.
) else (
    echo [ ERROR ] Encountered compilation errors.
)

pause