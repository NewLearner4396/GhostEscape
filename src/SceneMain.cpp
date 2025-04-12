#include "SceneMain.h"
#include "SceneTitle.h"

#include "Effect.h"
#include "Enemy.h"
#include "HUD_Button.h"
#include "HUD_Status.h"
#include "HUD_Text.h"
#include "Player.h"
#include "Status.h"
#include "Spawner.h"
#include "Spell.h"
#include "UI_Mouse.h"

void SceneMain::init() {
    SDL_HideCursor();  // Hide the system cursor for a better experience

    world_size_ = game_.getWindowSize() * 3.0f;
    camera_size_ = game_.getWindowSize();
    camera_position_ = world_size_ / 2.0f - camera_size_ / 2.0f;
    game_.playMusic("../assets/bgm/OhMyGhost.ogg");

    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f);
    addObject(player_);

    spawner_ = new Spawner();
    spawner_->init();
    spawner_->setTarget(player_);
    addObject(spawner_);

    HUD_status_ = HUD_Status::addHUDStatus(this, player_, glm::vec2{30.0f});
    HUD_text_score_ =
        HUD_Text::addHUDText(this, "Score: 0", glm::vec2{game_.getWindowSize().x - 120.0f, 30.0f}, glm::vec2{200, 50});

    HUD_button_pause_ =
        HUD_Button::addHUDButton(this, game_.getWindowSize() - glm::vec2{230, 30}, "../assets/UI/A_Pause1.png",
                                 "../assets/UI/A_Pause2.png", "../assets/UI/A_Pause3.png", 1.0f);
    HUD_button_restart_ =
        HUD_Button::addHUDButton(this, game_.getWindowSize() - glm::vec2{140, 30}, "../assets/UI/A_Restart1.png",
                                 "../assets/UI/A_Restart2.png", "../assets/UI/A_Restart3.png", 1.0f);
    HUD_button_back_ =
        HUD_Button::addHUDButton(this, game_.getWindowSize() - glm::vec2{50, 30}, "../assets/UI/A_Back1.png",
                                 "../assets/UI/A_Back2.png", "../assets/UI/A_Back3.png", 1.0f);

    UI_mouse_ = UI_Mouse::addMouse(this, "../assets/UI/29.png", "../assets/UI/30.png", 1.0f, Anchor::CENTER);
}

void SceneMain::clean() { Scene::clean(); }

bool SceneMain::handleEvents(SDL_Event& event) { 
    if(Scene::handleEvents(event))
        return true;
    return false;
}

void SceneMain::update(float dT) {
    Scene::update(dT);
    updateScore();
    checkButtonState();
    checkPlayerAlive(dT);
}

void SceneMain::render() {
    renderBackground();
    Scene::render();
}

void SceneMain::renderBackground() {
    // render Grid
    glm::vec2 leftTop = -camera_position_;
    glm::vec2 rightBottom = world_size_ - camera_position_;
    game_.drawGrid(leftTop, rightBottom, 100, 100, {0.5f, 0.5f, 0.5f, 1.0f});
    // render Boundary
    glm::vec2 boundaryStart = leftTop;
    glm::vec2 boundaryEnd = rightBottom;
    game_.drawBoundary(boundaryStart, boundaryEnd, 10.0f, {1.0f, 1.0f, 1.0f, 1.0f}, true);
}

void SceneMain::updateScore() {
    HUD_text_score_->setText("Score: " + std::to_string(static_cast<int>(game_.getScore())));
}

void SceneMain::checkButtonState() {
    if (HUD_button_pause_->getIsTrigger()) {
        if (is_paused_)
            resume();
        else
            pause();
    }
    if (HUD_button_restart_->getIsTrigger()) {
        game_.safeChangeScene(new SceneMain());
    }
    if (HUD_button_back_->getIsTrigger()) {
        game_.safeChangeScene(new SceneTitle());
    }
}

void SceneMain::checkPlayerAlive(float dT) {
    if(player_->getStatus()->getIsAlive()) 
        return;
    else{
        timer_ += dT;
        if(timer_ > 2.0f){
            game_.safeChangeScene(new SceneTitle());
        }
    }
}
