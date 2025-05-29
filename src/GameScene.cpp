#include "GameScene.h"
#include "Player.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

GameScene::GameScene(Game* game)
    : game(game),
  shader("shaders/sprite.vert", "shaders/sprite.frag"),
  gameTime(0.0f), startTimer(0.0f), gameStarted(false), score(0),
  player(glm::vec2(0.0f, -0.8f))
 {
    
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    
    for (int i = 0; i < 3; ++i) {
        spawnFlyingObject();
    }
}

void GameScene::update(float deltaTime) {
    if (!gameStarted) {
        startTimer += deltaTime;
        if (startTimer > 5.0f) {
            gameStarted = true;
            std::cout << "¡Comienza el juego!" << std::endl;
        }
        return;
    }

    
    player.updateAnimation(deltaTime);

    
    static float spawnTimer = 0.0f;
    spawnTimer += deltaTime;
    if (spawnTimer > 1.5f) { 
        spawnTimer = 0.0f;
        spawnFlyingObject();
    }

    
    for (auto it = fallingObjects.begin(); it != fallingObjects.end(); ) {
        it->update(deltaTime);
        
        if (it->collidesWith(player)) {
            score++;
            std::cout << "¡Atrapada! Puntuación: " << score << std::endl;
            it = fallingObjects.erase(it); // Eliminar mosca capturada
        } 
        else if (it->getPosition().y < -1.5f) {
            it = fallingObjects.erase(it); // Eliminar mosca que salió de pantalla
        } 
        else {
            ++it;
        }
    }

    
    gameTime += deltaTime;
    if (gameTime > 25.0f) {
        gameStarted = false;
        std::cout << "¡Tiempo terminado! Puntuación final: " << score << std::endl;
        // Aquí podrías cambiar a una escena de resultados
    }
}

void GameScene::render() {
   
    glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    
    player.render();

    
    for (auto& obj : fallingObjects) {
        obj.render();
    }
}

void GameScene::handleInput(int key, int action) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        const float moveSpeed = 0.05f;
        if (key == GLFW_KEY_LEFT) {
            player.move(-moveSpeed);
        }
        if (key == GLFW_KEY_RIGHT) {
            player.move(moveSpeed);
        }
    }
}

void GameScene::spawnFlyingObject() {
    float x = -0.9f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 1.8f));
    fallingObjects.emplace_back(glm::vec2(x, 1.2f), shader);
}
