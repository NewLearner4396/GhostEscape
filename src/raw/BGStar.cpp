#include "BGStar.h"
#include "Scene.h"

void BGStar::update(float dT) {
    timer_ += dT;
    color_far_ = {0.5f + 0.5f * sinf(timer_ * 0.9f), 0.5f + 0.5f * sinf(timer_ * 0.8f),
                  0.5f + 0.5f * sinf(timer_ * 0.7f), 1};
    color_mid_ = {0.5f + 0.5f * sinf(timer_ * 0.6f), 0.5f + 0.5f * sinf(timer_ * 0.5f),
                  0.5f + 0.5f * sinf(timer_ * 0.4f), 1};
    color_near_ = {0.5f + 0.5f * sinf(timer_ * 0.3f), 0.5f + 0.5f * sinf(timer_ * 0.2f),
                   0.5f + 0.5f * sinf(timer_ * 0.1f), 1};
}

void BGStar::render() {
    auto render_pos = -game_.getCurrentScene()->getCameraPosition();
    game_.drawPoints(stars_far_, render_pos * scale_far_, color_far_);
    game_.drawPoints(stars_mid_, render_pos * scale_mid_, color_mid_);
    game_.drawPoints(stars_near_, render_pos * scale_near_, color_near_);
}

BGStar* BGStar::addBGStar(Object* parent, float num, float scale_far, float scale_mid, float scale_near) {
    auto bg_star = new BGStar();
    bg_star->init();
    bg_star->num_ = num;
    bg_star->scale_far_ = scale_far;
    bg_star->scale_mid_ = scale_mid;
    bg_star->scale_near_ = scale_near;
    bg_star->stars_far_.reserve(static_cast<int>(num));  //* reserve memory for stars
    bg_star->stars_mid_.reserve(static_cast<int>(num));
    bg_star->stars_near_.reserve(static_cast<int>(num));
    auto minus =
        Game::getInstance().getCurrentScene()->getWorldSize() - Game::getInstance().getCurrentScene()->getCameraSize();
    for (int i = 0; i < num; i++) {
        bg_star->stars_far_.emplace_back(Game::getInstance().randomVec2(
            glm::vec2(0), Game::getInstance().getCurrentScene()->getCameraSize() + minus * scale_far));
        bg_star->stars_mid_.emplace_back(Game::getInstance().randomVec2(
            glm::vec2(0), Game::getInstance().getCurrentScene()->getCameraSize() + minus * scale_mid));
        bg_star->stars_near_.emplace_back(Game::getInstance().randomVec2(
            glm::vec2(0), Game::getInstance().getCurrentScene()->getCameraSize() + minus * scale_near));
    }
    if (parent)
        parent->safeAddObject(bg_star);
    return bg_star;
}
