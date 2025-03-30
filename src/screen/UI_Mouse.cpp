#include "UI_Mouse.h"

#include "Sprite.h"

void UI_Mouse::update(float dT) {
    ObjectScreen::update(dT);
    timer_ += dT;
    if (timer_ < 0.5f) {
        sprite1_->setActive(true);
        sprite2_->setActive(false);
    } else if (timer_ < 1.0f) {
        sprite1_->setActive(false);
        sprite2_->setActive(true);
    } else
        timer_ = 0.0f;
    setRenderPosition(game_.getMousePosition());
}

UI_Mouse* UI_Mouse::addMouse(Object* parent, const std::string& file_path1, const std::string& file_path2, float scale,
                             Anchor anchor) {
    auto mouse = new UI_Mouse();
    mouse->init();
    mouse->sprite1_ = Sprite::addSprite(mouse, file_path1, scale, anchor);
    mouse->sprite2_ = Sprite::addSprite(mouse, file_path2, scale, anchor);
    mouse->sprite1_->setActive(true);
    mouse->sprite2_->setActive(false);
    if (parent)
        parent->safeAddObject(mouse);
    return mouse;
}
