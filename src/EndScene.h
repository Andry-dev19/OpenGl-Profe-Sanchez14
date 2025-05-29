
#ifndef ENDSCENE_H
#define ENDSCENE_H

#include "Scene.h"
#include "Game.h"

class EndScene : public Scene {
public:
    EndScene(Game* game, int finalScore);
    void update(float deltaTime) override;
    void render() override;
    void handleInput(int key, int action) override;

private:
    Game* game;
    int finalScore;
};

#endif 
