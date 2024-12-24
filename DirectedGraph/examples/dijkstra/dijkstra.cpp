#include <GLFW/glfw3.h>
#include "dijkstra.hpp"

#include <map>
#include <cmath>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace lasd;

namespace lasd_glfw {
    int show() {
        if (!glfwInit()) {
            std::cerr << "Could not initialize GLFW.\n";
            return -1;
        }

        GLFWwindow* window = glfwCreateWindow(800, 600, "Dijkstra Example", NULL, NULL);
        if (!window) {
            std::cerr << "Could not create GLFW Window object.\n";
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

        DirectedGraph<int> graph;
        for (int i = 0; i < 7; ++i) graph.addNode(i);

        graph.addEdge(3, 1, 1.0);
        graph.addEdge(1, 2, 1.0);
        graph.addEdge(2, 3, 2.0);
        graph.addEdge(1, 4, 3.0);
        graph.addEdge(4, 5, 3.0);
        graph.addEdge(5, 6, 4.0);
        graph.addEdge(6, 4, 1.0);

        std::vector<Node<int>> nodes = graph.GetAllNodes();

        int start = 1, end = 4;
        std::vector<int> path = graph.GetMinimumPath(start, end);

        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }
}
