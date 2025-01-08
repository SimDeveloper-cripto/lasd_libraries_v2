#include "dijkstra.hpp"

#include <GLFW/glfw3.h>
#include <GL/freeglut.h>

#include <map>
#include <cmath>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <unordered_map>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define RADIUS 22.0f

// NOTE: The function to call is 'lasd_glfw::show()'

using namespace lasd;

namespace lasd_glfw {
    const int WIDTH  = 1024;
    const int HEIGHT = 768;

    struct Node {
        int id;
        float x, y;
    };

    void setup(GLFWwindow* window) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    #define __FREEGLUT_INSTALLED__
    #ifdef __FREEGLUT_INSTALLED__
    void drawText(const char* text, float x, float y) {
        glRasterPos2f(x, y);
        while (*text) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
            ++text;
        }
    }
    #endif

    void drawCircle(float cx, float cy, float r, const float color[3]) {
        glColor3f(color[0], color[1], color[2]);
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 128; i++) {
            float theta = 2.0f * M_PI * float(i) / 128.0f;
            float x     = r * cosf(theta);
            float y     = r * sinf(theta);
            glVertex2f(cx + x, cy + y);
        }
        glEnd();
    }

    void drawArrow(float x1, float y1, float x2, float y2, const float color[3], float arrowSize = 10.0f) {
        glLineWidth(2.0f);
        glColor3f(color[0], color[1], color[2]);

        // Arrow direction
        float dx = x2 - x1;
        float dy = y2 - y1;
        float length = sqrtf(dx*dx + dy*dy);
        if (length < 1e-6f) return;

        // Normalize to get a vector (nx, ny)
        float nx = dx / length;
        float ny = dy / length;

        float start_x = x1 + nx * RADIUS;
        float start_y = y1 + ny * RADIUS;
        float end_x   = x2 - nx * RADIUS;
        float end_y   = y2 - ny * RADIUS;

        glBegin(GL_LINES);
        glVertex2f(start_x, start_y);
        glVertex2f(end_x, end_y);
        glEnd();

        // Get the orthogonal vector to (nx, ny). If (nx, ny) is (0,1), It is (1,0) or (-1,0)
        float px = -ny;
        float py = nx;

        // Circle coordinates of intersection
        float tip_x = end_x;
        float tip_y = end_y;

        float shaft_end_x = tip_x - nx * arrowSize;
        float shaft_end_y = tip_y - ny * arrowSize;

        float half   = arrowSize * 0.5f;
        float leftx  = shaft_end_x + px * half;
        float lefty  = shaft_end_y + py * half;
        float rightx = shaft_end_x - px * half;
        float righty = shaft_end_y - py * half;

        glBegin(GL_TRIANGLES);
        glVertex2f(tip_x, tip_y);
        glVertex2f(leftx, lefty);
        glVertex2f(rightx, righty);
        glEnd();
    }

    bool isEdgeInPath(const std::vector<int>& path, int from, int to) {
        for (size_t i = 0; i < path.size() - 1; ++i)
            if (path[i] == from && path[i + 1] == to) return true;
        return false;
    }

    int show() {
        if (!glfwInit()) {
            std::cerr << "Could not initialize GLFW.\n";
            return -1;
        }

        GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Dijkstra Example", NULL, NULL);
        if (!window) {
            std::cerr << "Could not create GLFW Window object.\n";
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        srand(static_cast<unsigned int>(time(NULL)));

        int dummy_argc = 1;
        char* dummy_argv[] = { (char*)"dijkstra_example", nullptr };
        glutInit(&dummy_argc, dummy_argv);

        std::vector<Node> nodes;
        std::vector<std::tuple<int, int, double>> edges;

        DirectedGraph<int> graph;
        for (int i = 0; i < 7; ++i) {
            graph.addNode(i);
            nodes.push_back({i, float(rand() % (WIDTH - 100) + 50), float(rand() % (HEIGHT - 100) + 50)});
        }

        auto c_addEdge = [&](int from, int to, double weight) {
            graph.addEdge(from, to, weight);
            edges.emplace_back(from, to, weight);
        };

        c_addEdge(3, 1, 1.0);
        c_addEdge(1, 2, 1.0);
        c_addEdge(2, 3, 2.0);
        c_addEdge(1, 4, 3.0);
        c_addEdge(4, 5, 3.0);
        c_addEdge(5, 6, 4.0);
        c_addEdge(6, 4, 1.0);

        std::vector<int> path = graph.GetMinimumPath(3, 6);

        const float nodeColor[]          = {0.2f, 0.6f, 0.8f};
        const float nodeHighlightColor[] = {0.9f, 0.3f, 0.3f};
        const float edgeColor[]          = {0.6f, 0.6f, 0.6f};
        const float edgeHighlightColor[] = {0.1f, 0.7f, 0.1f};

        while (!glfwWindowShouldClose(window)) {
            setup(window);
            glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (const auto& edge : edges) {
                int from = std::get<0>(edge);
                int to   = std::get<1>(edge);
                double w = std::get<2>(edge);

                const Node& n1 = nodes[from];
                const Node& n2 = nodes[to];

                bool isInPath = isEdgeInPath(path, from, to);
                drawArrow(n1.x, n1.y, n2.x, n2.y, isInPath ? edgeHighlightColor : edgeColor);

                char weightText[16];
                snprintf(weightText, sizeof(weightText), "%.1f", w);
                float midX = (n1.x + n2.x) / 2.0f;
                float midY = (n1.y + n2.y) / 2.0f;
                glColor3f(0.0f, 0.0f, 0.0f);
                drawText(weightText, midX, midY);
            }

            for (const auto& node : nodes) {
                bool isStartOrEnd = node.id == 3 || node.id == 6;
                drawCircle(node.x, node.y, RADIUS, isStartOrEnd ? nodeHighlightColor : nodeColor);
            
                char idText[8];
                snprintf(idText, sizeof(idText), "%d", node.id);
                glColor3f(1.0f, 1.0f, 1.0f);
                drawText(idText, node.x - 5, node.y + 5);
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }
}