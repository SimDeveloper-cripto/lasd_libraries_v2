#include "dijkstra/dijkstra.hpp"

#include <exception>

int main(void) {
    if (lasd_glfw::show() != 0) throw std::runtime_error("[Dijkstra example] ERROR: lasd_glfw::show() has produced an exception!");
    return 0;
}