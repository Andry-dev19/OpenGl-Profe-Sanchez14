    #include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <iostream>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
int currentScene = 0;

const char* vertexShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(aPos, 1.0);
}
)glsl";

const char* fragmentShaderSources[] = {
    R"glsl(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    })glsl",
    R"glsl(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    })glsl",
    R"glsl(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(0.0, 0.0, 1.0, 1.0);
    })glsl"
};

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

unsigned int VAOs[3], VBOs[3], EBOs[3], shaders[3];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_RIGHT) currentScene = (currentScene + 1) % 3;
        if (key == GLFW_KEY_LEFT)  currentScene = (currentScene + 2) % 3;
    }
}

unsigned int compileShader(unsigned int type, const char* src) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}

unsigned int createShaderProgram(const char* fragSrc) {
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragSrc);
    unsigned int program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
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

    for (int i = 0; i < 5; ++i) {
        pentagonVertices[i * 3 + 0] = 0.5f * cos(2 * M_PI * i / 5);
        pentagonVertices[i * 3 + 1] = 0.5f * sin(2 * M_PI * i / 5);
        pentagonVertices[i * 3 + 2] = 0.0f;
    }

    setupScene(0, triangleVertices, sizeof(triangleVertices), triangleIndices, sizeof(triangleIndices));
    setupScene(1, squareVertices, sizeof(squareVertices), squareIndices, sizeof(squareIndices));
    setupScene(2, pentagonVertices, sizeof(pentagonVertices), pentagonIndices, sizeof(pentagonIndices));

    for (int i = 0; i < 3; ++i)
        shaders[i] = createShaderProgram(fragmentShaderSources[i]);

    while (!glfwWindowShouldClose(window)) {
        float colors[3][3] = {
            {0.2f, 0.2f, 0.2f},
            {0.3f, 0.1f, 0.1f},
            {0.1f, 0.1f, 0.3f},
        };

        glClearColor(colors[currentScene][0], colors[currentScene][1], colors[currentScene][2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaders[currentScene]);
        glBindVertexArray(VAOs[currentScene]);
        glDrawElements(GL_TRIANGLES, (currentScene + 1) * 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
