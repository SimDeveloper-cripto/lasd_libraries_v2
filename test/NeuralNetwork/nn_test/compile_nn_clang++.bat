@echo off

clang++ -std=c++17 -o3 -o nn_lasd -Wall ../neuron.cpp ../layer.cpp ../neural_network.cpp ../activation_functions.cpp nn_test.cpp

if %ERRORLEVEL% EQU 0 (
    echo [ OK ] Compilation successful. Executable 'nn_lasd' generated.
) else (
    echo [ ERROR ] Encountered compilation errors.
)

pause