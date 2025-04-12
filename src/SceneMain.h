#ifndef SCENEMAIN_H
#define SCENEMAIN_H

#include "Scene.h"

class Player;
class Enemy;
class Spawner;
class UI_Mouse;
class HUD_Status;
class HUD_Text;
class HUD_Button;
class SceneMain : public Scene {
   public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    void init() override;
    void clean() override;
    bool handleEvents(SDL_Event& event) override;
    void update(float dT) override;
    void render() override;

    Spawner* getSpawner() const { return spawner_; }

   private:
    Player* player_ = nullptr;
    Enemy* enemy_ = nullptr;
    Spawner* spawner_ = nullptr;
    UI_Mouse* UI_mouse_ = nullptr;
    HUD_Status* HUD_status_ = nullptr;
    HUD_Text* HUD_text_score_ = nullptr;
    HUD_Button* HUD_button_pause_ = nullptr;
    HUD_Button* HUD_button_restart_ = nullptr;
    HUD_Button* HUD_button_back_ = nullptr;

    float timer_ = 0.0f;

    void renderBackground();
    void updateScore();
    void checkButtonState();
    void checkPlayerAlive(float dT);
};

#endif