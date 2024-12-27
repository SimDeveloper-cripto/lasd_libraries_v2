#include "dijkstra.hpp"

#include <GLFW/glfw3.h>
#include <GL/freeglut.h>

#include <map>
#include <cmath>
#include <vector>
#include <iostream>
#include <unordered_map>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define RADIUS 22.0f

using namespace lasd;

// TODO: IL METODO `drawArrow(...)` NON FUNZIONA
// TODO: IL RENDER VA SISTEMATO
// TODO: NEL FILE DI COMPILAZIONE, su windows funziona a tutti come includi le librerie? (prese da msys64/mingw64 ecc.)
// TODO: SISTEMA ANCHE TUTTI GLI ALTRI FILE DI COMPILAZIONE (G++ E LINUX)
// TODO: IL PROCESSO DELLA FINESTRA DI OPENGL è BLOCCANTE, PERCHè?

namespace lasd_glfw {
    const int WIDTH  = 800;
    const int HEIGHT = 600;

    void drawCircle(float cx, float cy, float r, int segments = 72) {
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * M_PI * float(i) / float(segments);
            float x     = r * cosf(theta);
            float y     = r * sinf(theta);
            glVertex2f(cx + x, cy + y);
        }
        glEnd();
    }

    void drawArrow(float x1, float y1, float x2, float y2, float arrowSize = 8.0f) {
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();

        // Arrow direction
        float dx = x2 - x1;
        float dy = y2 - y1;
        float length = sqrtf(dx*dx + dy*dy);
        if (length < 1e-6) return;

        // Normalize to get a vector (nx, ny)
        float nx = dx / length;
        float ny = dy / length;

        float bx = x2 - nx * arrowSize;
        float by = y2 - ny * arrowSize;

        // Get the orthogonal vector to (nx, ny). If (nx, ny) è (0,1), It is (1,0) o (-1,0)
        float px = -ny;
        float py = nx;

        float half = arrowSize * 0.5f;
        px *= half;
        py *= half;

        float leftx  = bx + px;
        float lefty  = by + py;
        float rightx = bx - px;
        float righty = by - py;

        glBegin(GL_TRIANGLES);
        glVertex2f(x2, y2);
        glVertex2f(leftx, lefty);
        glVertex2f(rightx, righty);
        glEnd();
    }

    #define __FREEGLUT_INSTALLED__
    #ifdef __FREEGLUT_INSTALLED__
    void drawText(const char* text, float x, float y) {
        glRasterPos2f(x, y);
        while(*text) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
            ++text;
        }
    }
    #endif

    bool isEdgeInPath(const std::vector<int>& path, int from, int to) {
        for (size_t i = 0; i < path.size(); i++) {
            if (path[i] == from && path[i + 1] == to) return true;
        }
        return false;
    }

    int show() {
        if (!glfwInit()) {
            std::cerr << "Could not initialize GLFW.\n";
            return -1;
        }

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Dijkstra Example", NULL, NULL);
        if (!window) {
            std::cerr << "Could not create GLFW Window object.\n";
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

        // TODO: WTF
        int dummy_argc = 1;
        char* dummy_argv[] = { (char*)"dummy", nullptr };
        glutInit(&dummy_argc, dummy_argv);

        DirectedGraph<int> graph;
        std::vector<std::tuple<int, int, double>> all_edges;

        for (int i = 0; i < 7; ++i) graph.addNode(i);

        auto c_addEdge = [&](int f, int t, int w) {
            graph.addEdge(f, t, w);
            all_edges.emplace_back(f, t, w);
        };

        c_addEdge(3, 1, 1.0);
        c_addEdge(1, 2, 1.0);
        c_addEdge(2, 3, 2.0);
        c_addEdge(1, 4, 3.0);
        c_addEdge(4, 5, 3.0);
        c_addEdge(5, 6, 4.0);
        c_addEdge(6, 4, 1.0);

        std::unordered_map<int, std::pair<float, float>> node_positions = {
            {0, {100, 500}}, {1, {200, 400}}, {2, {300, 500}},
            {3, {400, 400}}, {4, {500, 500}}, {5, {600, 400}},
            {6, {700, 500}}
        };

        int start = 3, end = 6;
        std::vector<int> path = graph.GetMinimumPath(start, end);

        while (!glfwWindowShouldClose(window)) {
            glViewport(0, 0, WIDTH, HEIGHT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, WIDTH, HEIGHT, 0, -1, 1); // Y flipped
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (auto& triple : all_edges) {
                int from = std::get<0>(triple);
                int to   = std::get<1>(triple);
                float w  = static_cast<float>(std::get<2>(triple));

                float x1 = node_positions[from].first;
                float y1 = node_positions[from].second;
                float x2 = node_positions[to].first;
                float y2 = node_positions[to].second;

                if (isEdgeInPath(path, from, to)) {
                    glColor3f(0.0f, 0.0f, 1.0f);
                } else {
                    glColor3f(0.5f, 0.5f, 0.5f);
                }

                drawArrow(x1, y1, x2, y2);

                #define __FREEGLUT_INSTALLED__
                #ifdef __FREEGLUT_INSTALLED__
                float midx = (x1 + x2) * 0.5f;
                float midy = (y1 + y2) * 0.5f;

                glColor3f(0.0f, 0.0f, 0.0f);
                char buffer[16];
                snprintf(buffer, sizeof(buffer), "%.1f", w);
                drawText(buffer, midx, midy);
                #endif
            }

            auto nodes = graph.GetAllNodes();
            for (auto& n : nodes) {
                int nodeId = n.key;
                float cx   = node_positions[nodeId].first;
                float cy   = node_positions[nodeId].second;
                char buf[8];

                if (nodeId == start || nodeId == end) {
                    glColor3f(1.0f, 0.0f, 0.0f); // RED
                    drawCircle(cx, cy, RADIUS);

                    #define __FREEGLUT_INSTALLED__ 
                    #ifdef __FREEGLUT_INSTALLED__
                        glColor3f(0.0f, 0.0f, 0.0f);
                        snprintf(buf, sizeof(buf), "%d", nodeId);
                        drawText(buf, cx - 5, cy + 5);
                    #endif
                    glColor3f(0.0f, 0.0f, 0.0f);
                } else {
                    glColor3f(0.0f, 0.0f, 0.0f);
                    drawCircle(cx, cy, RADIUS);

                    #define __FREEGLUT_INSTALLED__ 
                    #ifdef __FREEGLUT_INSTALLED__
                        glColor3f(1.0f, 1.0f, 1.0f);
                        snprintf(buf, sizeof(buf), "%d", nodeId);
                        drawText(buf, cx - 5, cy + 5);
                    #endif
                }
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }
}
