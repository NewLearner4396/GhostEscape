#ifndef SCENEMAIN_H
#define SCENEMAIN_H

#include "Scene.h"

class Player;
class Enemy;
class Spawner;
class UI_Mouse;
class SceneMain : public Scene {
   public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    void init() override;
    void clean() override;
    void handleEvents(SDL_Event& event) override;
    void update(float dT) override;
    void render() override;

   private:
    Player* player_ = nullptr;
    Enemy* enemy_ = nullptr;
    Spawner* spawner_ = nullptr; 
    UI_Mouse* UI_mouse_ = nullptr;
    void renderBackground();
};

#endif