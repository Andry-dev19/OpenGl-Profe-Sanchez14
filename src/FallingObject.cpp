#include "FallingObject.h"
#include "Player.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

FallingObject::FallingObject(glm::vec2 startPosition, const Shader& shader)
    : position(startPosition), 
      size(glm::vec2(0.15f, 0.15f)),
      speed(0.3f + (rand() % 100) / 100.0f * 0.5f),
      renderer(shader) {
    if (!texture.LoadFromFile("assets/greenfly_spritesheet.png")) {
        std::cerr << "ERROR: No se pudo cargar greenfly_spritesheet.png\n";
    }
}

void FallingObject::update(float deltaTime) {
    position.y -= speed * deltaTime;
    if (position.y + size.y < -1.0f) {
        reset();
    }
}

void FallingObject::render() {
    float frameWidth = 1.0f / 3.0f; // 3 frames de ancho
    renderer.draw(texture, position, size, 
        glm::vec4(0.0f, 0.0f, frameWidth, 1.0f));
}

void FallingObject::reset() {
    position.x = -0.9f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.8f));
    position.y = 1.2f;
    speed = 0.2f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.4f));
}

bool FallingObject::collidesWith(const Player& player) const {
    glm::vec2 playerPos = player.getPosition();
    glm::vec2 playerSize = player.getSize();

    bool collisionX = position.x < playerPos.x + playerSize.x &&
                      position.x + size.x > playerPos.x;

    bool collisionY = position.y < playerPos.y + playerSize.y &&
                      position.y + size.y > playerPos.y;

    return collisionX && collisionY;
}
