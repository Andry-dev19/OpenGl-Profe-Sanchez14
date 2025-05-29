#ifndef GAME_H
#define GAME_H

#include "StartScene.h"
#include <memory>
#include "Scene.h"
#include <GLFW/glfw3.h>

class StartScene;  // Declaración anticipada

class Game {
public:
    static Game& getInstance() {
        static Game instance;
        return instance;
    }

    void initialize(GLFWwindow* win) {
        window = win;
        currentScene = std::make_shared<StartScene>(this);
    }

    void updateScene(float deltaTime) {
        if (currentScene) currentScene->update(deltaTime);
    }

    void renderScene() {
        if (currentScene) currentScene->render();
    }

    void changeScene(std::shared_ptr<Scene> newScene) {
        currentScene = newScene;
    }

    void handleInput(int key, int action) {
        if (currentScene) currentScene->handleInput(key, action);
    }

    GLFWwindow* getWindow() const { return window; }

private:
    Game() = default;
    GLFWwindow* window;
    std::shared_ptr<Scene> currentScene;
};

#endif // GAME_H