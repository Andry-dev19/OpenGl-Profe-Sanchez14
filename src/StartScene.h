#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "Scene.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>

class Game;  

class StartScene : public Scene {
public:
    explicit StartScene(Game* game);
    void update(float deltaTime) override;
    void render() override;
    void handleInput(int key, int action) override;

private:
    Game* game;
    Texture icon;
    Shader shader;
    SpriteRenderer renderer;
    float animTime;
};

#endif // STARTSCENE_H