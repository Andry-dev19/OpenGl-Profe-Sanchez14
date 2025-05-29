#include "StartScene.h"
#include "GameScene.h"  
#include "Game.h"       
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <memory>       

StartScene::StartScene(Game* game)
    : game(game), 
      icon("assets/frog_soldier.png"),
      shader("shaders/sprite.vert", "shaders/sprite.frag"),
      renderer(shader),
      animTime(0.0f) {}

void StartScene::update(float deltaTime) {
    animTime += deltaTime;
}

void StartScene::render() {
    glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float yOffset = std::sin(animTime * 2.0f) * 0.05f;
    glm::vec2 position = glm::vec2(0.35f, 0.25f + yOffset);  // Posición corregida
    glm::vec2 size = glm::vec2(0.3f, 0.3f);                  // Tamaño ajustado

    
    renderer.draw(icon, position, size, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
}

void StartScene::handleInput(int key, int action) {
    if (action == GLFW_PRESS && key == GLFW_KEY_ENTER) {
        
        auto newScene = std::make_shared<GameScene>(game);
        game->changeScene(newScene);
    }
}