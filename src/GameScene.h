#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>
#include "Scene.h"
#include "Game.h"
#include "Player.h"
#include "FallingObject.h"

class GameScene : public Scene {
public:
    GameScene(Game* game);
    void update(float deltaTime) override;
    void render() override;
    void handleInput(int key, int action) override;
    void spawnFlyingObject();

private:
    Game* game;
    Shader shader;
    Player player;
    std::vector<FallingObject> fallingObjects;
    float gameTime;
    float startTimer;
    bool gameStarted;
    int score;
};

#endif // GAMESCENE_H