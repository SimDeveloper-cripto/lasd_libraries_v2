#include "dijkstra.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

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
