#include "Player.h"
#include <iostream>

Player::Player() 
    : position(0.0f, -0.8f), 
      size(0.2f, 0.2f),
      renderer(Shader("shaders/sprite.vert", "shaders/sprite.frag")) {
    
    if (!sprite.LoadFromFile("assets/frog_soldier.png")) {
        std::cerr << "ERROR: No se pudo cargar frog_soldier.png\n";
    }
}

Player::Player(glm::vec2 position)
    : position(position), 
      size(0.2f, 0.2f),
      renderer(Shader("shaders/sprite.vert", "shaders/sprite.frag")) {
    
    if (!sprite.LoadFromFile("assets/frog_soldier.png")) {
        std::cerr << "ERROR: No se pudo cargar frog_soldier.png\n";
    }
}

void Player::move(float dx) {
    position.x += dx;
   
    if (position.x < -1.0f) position.x = -1.0f;
    if (position.x > 1.0f - size.x) position.x = 1.0f - size.x;
}

void Player::updateAnimation(float deltaTime) {
    frameTime += deltaTime;
    if (frameTime >= frameDuration) {
        frameTime = 0.0f;
        currentFrame = (currentFrame + 1) % totalFrames;
    }
}

void Player::render() {
    float frameWidth = 1.0f / totalFrames;
    renderer.draw(sprite, position, size, 
                 glm::vec4(
                     currentFrame * frameWidth, 0.0f,
                     (currentFrame + 1) * frameWidth, 1.0f
                 ));
}