#include "HUD_Button.h"
#include "Sprite.h"

bool HUD_Button::handleEvents(SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (is_hover_){
                is_press_ = true;
                game_.playSound("../assets/sound/UI_button08.wav");
                return true;
            }
        }
    } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            is_press_ = false;
            if (is_hover_){
                is_trigger_ = true;
                return true;
            }
        }
    }
    return false;
}

HUD_Button* HUD_Button::addHUDButton(Object* parent, glm::vec2 render_pos, const std::string& file_path_normal,
                                     const std::string& file_path_hover, const std::string& file_path_press,
                                     float scale, Anchor anchor) {
    auto HUD_button = new HUD_Button();
    HUD_button->init();
    HUD_button->setRenderPosition(render_pos);
    HUD_button->sprite_nomal_ = Sprite::addSprite(HUD_button, file_path_normal, scale, anchor);
    HUD_button->sprite_hover_ = Sprite::addSprite(HUD_button, file_path_hover, scale, anchor);
    HUD_button->sprite_press_ = Sprite::addSprite(HUD_button, file_path_press, scale, anchor);
    HUD_button->sprite_nomal_->setActive(true);
    HUD_button->sprite_hover_->setActive(false);
    HUD_button->sprite_press_->setActive(false);
    if (parent)
        parent->addObject(HUD_button);
    return HUD_button;
}

void HUD_Button::checkHover() {
    bool new_hover = false;
    auto pos = getRenderPosition() + sprite_nomal_->getOffset();
    auto size = sprite_nomal_->getSize();
    if (game_.isMouseInRect(pos, pos + size)) {
        new_hover = true;
    } else {
        new_hover = false;
    }
    if (new_hover != is_hover_) {
        is_hover_ = new_hover;
        if (is_hover_ && !is_press_)
            game_.playSound("../assets/sound/UI_button12.wav");
    }
}

void HUD_Button::checkState() {
    if (!is_hover_ && !is_hover_) {
        sprite_nomal_->setActive(true);
        sprite_hover_->setActive(false);
        sprite_press_->setActive(false);
    } else if (is_hover_ && !is_press_) {
        sprite_nomal_->setActive(false);
        sprite_hover_->setActive(true);
        sprite_press_->setActive(false);
    } else {
        sprite_nomal_->setActive(false);
        sprite_hover_->setActive(false);
        sprite_press_->setActive(true);
    }
}

bool HUD_Button::getIsTrigger() {
    if (is_trigger_) {
        is_trigger_ = false;
        return true;
    }
    return false;
}
