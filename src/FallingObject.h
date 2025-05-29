#ifndef FALLING_OBJECT_H
#define FALLING_OBJECT_H

#include <glm/glm.hpp>
#include "Texture.h"
#include "SpriteRenderer.h"


class Player;

class FallingObject {
public:
    FallingObject(glm::vec2 startPosition, const Shader& shader);

    void update(float deltaTime);
    void render();
    void reset();
    bool collidesWith(const Player& player) const;  // Usa la declaración anticipada

    glm::vec2 getPosition() const { return position; }
    glm::vec2 getSize() const { return size; }

private:
    glm::vec2 position;
    glm::vec2 size;
    float speed;
    Texture texture;
    SpriteRenderer renderer;
};

#endif