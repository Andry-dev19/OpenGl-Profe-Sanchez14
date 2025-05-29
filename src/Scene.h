
#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void handleInput(int key, int action) = 0;
    virtual ~Scene() = default;
};

#endif // SCENE_H
