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
class Timer;
class SceneMain : public Scene {
   public:
    SceneMain() = default;
    virtual ~SceneMain() = default;

    void init() override;
    void clean() override;
    bool handleEvents(SDL_Event& event) override;
    void update(float dT) override;
    void render() override;

    void saveData(const std::string& file_path) override;

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
    Timer* end_timer_ = nullptr;

    void renderBackground();
    void updateScore();
    void checkButtonState();
    void checkEndTimer();
    void checkSlowDown(float& dT);
};

#endif