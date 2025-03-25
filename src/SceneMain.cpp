#include "SceneMain.h"

void SceneMain::init() {
    world_size_ = game_.getWindowSize() * 3.0f;
    camera_size_ = game_.getWindowSize();
    camera_position_ = world_size_ / 2.0f - camera_size_ / 2.0f;
    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f);
    addObject(player_);
    enemy_ = new Enemy();
    enemy_->init();
    enemy_->setPosition(world_size_ / 2.0f + glm::vec2(100.0f, 100.0f));
    enemy_->setMaxSpeed(50.0f);
    enemy_->setTarget(player_);
    addObject(enemy_);
}

void SceneMain::clean() { Scene::clean(); }

void SceneMain::handleEvents(SDL_Event& event) { Scene::handleEvents(event); }

void SceneMain::update(float dT) {
    // camera_position_ += glm::vec2(10.0f, 10.0f) * dT;
    Scene::update(dT);
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
