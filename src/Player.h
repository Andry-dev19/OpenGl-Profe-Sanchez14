#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "Texture.h"
#include "SpriteRenderer.h"

class Player {
public:
    Player();
    explicit Player(glm::vec2 position);

    void move(float dx);
    void updateAnimation(float deltaTime);
    void render();

    glm::vec2 getPosition() const { return position; }
    glm::vec2 getSize() const { return size; }

private:
    glm::vec2 position;
    glm::vec2 size;
    Texture sprite;
    SpriteRenderer renderer;
    int currentFrame = 0;
    int totalFrames = 4;       // 4 frames en el spritesheet
    float frameTime = 0.0f;
    const float frameDuration = 0.15f; // 150ms por frame
};

#endif