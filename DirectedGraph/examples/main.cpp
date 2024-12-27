#include <iostream>
#include <exception>

#ifndef NO_GLFW
    #include "dijkstra/dijkstra.hpp"
#endif

int main(void) {
#ifdef NO_GLFW
    std::cout << "\n[INFO] Skipping EXAMPLE #1 'DIJKSTRA VISUALIZATION'. Missing <GLFW/glfw3.h> and <GL/freeglut.h> headers." << std::endl;
#else
    if (lasd_glfw::show() != 0) {
        std::cout << "\n[EXAMPLE #1] DIJKSTRA VISUALIZATION: FAILED" << std::endl;
        throw std::runtime_error("[Dijkstra example] ERROR: lasd_glfw::show() has produced an exception!");        
    } else std::cout << "\n[EXAMPLE #1] DIJKSTRA VISUALIZATION: PASSED" << std::endl;
#endif
    return 0;
}