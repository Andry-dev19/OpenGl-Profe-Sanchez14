#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
int currentScene = 0;

float triangleVertices[] = {
    0.0f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

unsigned int triangleIndices[] = { 0, 1, 2 };

float squareVertices[] = {
   -0.5f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f,  0.5f, 0.0f
};

unsigned int squareIndices[] = { 0, 1, 2, 0, 2, 3 };

float pentagonVertices[15];
unsigned int pentagonIndices[] = { 0, 1, 2, 0, 2, 3, 0, 3, 4 };

unsigned int VAOs[3], VBOs[3], EBOs[3];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_RIGHT) currentScene = (currentScene + 1) % 3;
        if (key == GLFW_KEY_LEFT)  currentScene = (currentScene + 2) % 3;
    }
}

void setupScene(int index, float* vertices, size_t vsize, unsigned int* indices, size_t isize) {
    glGenVertexArrays(1, &VAOs[index]);
    glGenBuffers(1, &VBOs[index]);
    glGenBuffers(1, &EBOs[index]);

    glBindVertexArray(VAOs[index]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[index]);
    glBufferData(GL_ARRAY_BUFFER, vsize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[index]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3 Scenes", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    Shader shader("shaders/vertex_shader.vert", "shaders/fragment_shader.frag");

    for (int i = 0; i < 5; ++i) {
        pentagonVertices[i * 3 + 0] = 0.5f * cos(2 * M_PI * i / 5);
        pentagonVertices[i * 3 + 1] = 0.5f * sin(2 * M_PI * i / 5);
        pentagonVertices[i * 3 + 2] = 0.0f;
    }

    setupScene(0, triangleVertices, sizeof(triangleVertices), triangleIndices, sizeof(triangleIndices));
    setupScene(1, squareVertices, sizeof(squareVertices), squareIndices, sizeof(squareIndices));
    setupScene(2, pentagonVertices, sizeof(pentagonVertices), pentagonIndices, sizeof(pentagonIndices));

    while (!glfwWindowShouldClose(window)) {
        float bgColors[3][3] = {
            {0.2f, 0.2f, 0.2f},
            {0.3f, 0.1f, 0.1f},
            {0.1f, 0.1f, 0.3f},
        };

        glm::vec3 figureColors[3] = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f},
        };

        glClearColor(bgColors[currentScene][0], bgColors[currentScene][1], bgColors[currentScene][2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.setVec3("uColor", 
            figureColors[currentScene].x, 
            figureColors[currentScene].y, 
            figureColors[currentScene].z
        );

        glBindVertexArray(VAOs[currentScene]);
        glDrawElements(GL_TRIANGLES, (currentScene + 1) * 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
