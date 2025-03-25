#ifndef SCENEMAIN_H
#define SCENEMAIN_H
#include "Enemy.h"
#include "Player.h"
#include "Scene.h"

class Player;
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
    void renderBackground();
};

#endif