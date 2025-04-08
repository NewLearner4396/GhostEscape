#include "SceneTitle.h"

#include <cmath>
#include "HUD_Text.h"

void SceneTitle::init() {
    Scene::init();
    auto pos = game_.getWindowSize() / 2.0f - glm::vec2(0, 100);
    auto size = glm::vec2(game_.getWindowSize().x / 2.0f, game_.getWindowSize().y / 3.0f);
    HUD_Text::addHUDText(this, " GHOST ESCAPE", pos, size, "../assets/font/VonwaonBitmap-16px.ttf", 64);

    auto score_text = "Max Score: " + std::to_string(static_cast<int>(game_.getHighScore()));
    pos = game_.getWindowSize() / 2.0f + glm::vec2(0, 100);
    size = glm::vec2(275, 50);
    HUD_Text::addHUDText(this, score_text, pos, size, "../assets/font/VonwaonBitmap-16px.ttf", 32);
}

void SceneTitle::clean() { Scene::clean(); }

void SceneTitle::handleEvents(SDL_Event& event) { Scene::handleEvents(event); }

void SceneTitle::update(float dT) {
    Scene::update(dT);
    color_timer += dT;
    updateBoundaryColor(0.3f, 0.4f, 0.1f);
}

void SceneTitle::render() {
    renderBackground();
    Scene::render();
}

void SceneTitle::renderBackground() {
    game_.drawBoundary(glm::vec2(30), game_.getWindowSize() - glm::vec2(30), 10.0f, boundary_color_, true);
}

void SceneTitle::updateBoundaryColor(std::optional<float> a, std::optional<float> b, std::optional<float> c,
                                     std::optional<float> d) {
    //? when all the coffs are the same, it will just change brightness
    if (!a.has_value())
        a = game_.randomFloat(0.5f, 1.5f);
    if (!b.has_value())
        b = a;
    if (!c.has_value())
        c = a;
    if (!d.has_value())
        d = 1.0f;
    boundary_color_.r = 0.5f + 0.5f * std::sinf(color_timer * a.value());
    boundary_color_.g = 0.5f + 0.5f * std::sinf(color_timer * b.value());
    boundary_color_.b = 0.5f + 0.5f * std::sinf(color_timer * c.value());
    boundary_color_.a = 0.5f + 0.5f * std::sinf(color_timer * d.value());
}
