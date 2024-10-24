#!/bin/sh
g++ -o3 -o bin/lasd -Wall LinkedList/linked_list.cpp Graph/graph.cpp NeuralNetwork/neuron.cpp \
    NeuralNetwork/layer.cpp NeuralNetwork/neural_network.cpp NeuralNetwork/activation_functions.cpp myTest/test.cpp main.cpp