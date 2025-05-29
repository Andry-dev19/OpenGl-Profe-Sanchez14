
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>

class GameObject {
public:
    glm::vec2 position;
    glm::vec2 size;
    glm::vec2 velocity;

    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual ~GameObject() = default;
};

#endif // GAMEOBJECT_H
