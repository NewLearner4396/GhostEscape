#include "HUD_Status.h"

#include "Actor.h"
#include "Sprite.h"
#include "Status.h"

void HUD_Status::init() {
    ObjectScreen::init();  // Call the init function of the parent class
    //* should care the initialization order of the status bar
    //* bg -> bar -> icon
    health_bar_bg_ = Sprite::addSprite(this, "../assets/UI/bar_bg.png", 3.0f, Anchor::CENTER_LEFT);
    health_bar_bg_->setOffset(health_bar_bg_->getOffset() + glm::vec2{30, 0});
    health_bar_ = Sprite::addSprite(this, "../assets/UI/bar_red.png", 3.0f, Anchor::CENTER_LEFT);
    health_bar_->setOffset(health_bar_->getOffset() + glm::vec2{30, 0});
    health_bar_icon_ = Sprite::addSprite(this, "../assets/UI/Red Potion.png", 0.5f, Anchor::CENTER_LEFT);

    mana_bar_bg_ = Sprite::addSprite(this, "../assets/UI/bar_bg.png", 3.0f, Anchor::CENTER_LEFT);
    mana_bar_bg_->setOffset(mana_bar_bg_->getOffset() + glm::vec2{300, 0});
    mana_bar_ = Sprite::addSprite(this, "../assets/UI/bar_blue.png", 3.0f, Anchor::CENTER_LEFT);
    mana_bar_->setOffset(mana_bar_->getOffset() + glm::vec2{300, 0});
    mana_bar_icon_ = Sprite::addSprite(this, "../assets/UI/Blue Potion.png", 0.5f, Anchor::CENTER_LEFT);
    mana_bar_icon_->setOffset(mana_bar_icon_->getOffset() + glm::vec2{270, 0});
}

void HUD_Status::update(float dT) {
    ObjectScreen::update(dT);  // Call the update function of the parent class
    updateHealthBar();         // Update the health bar based on the actor's status
    updateManaBar();           // Update the mana bar based on the actor's status
}

HUD_Status* HUD_Status::addHUDStatus(Object* parent, Actor* target, glm::vec2 render_position) {
    auto HUD_status = new HUD_Status();  // Create a new HUD_Status object
    HUD_status->init();
    HUD_status->setRenderPosition(render_position);
    HUD_status->setTarget(target);  // Set the target actor for the HUD status
    if (parent)
        parent->safeAddObject(HUD_status);  // Add the HUD status to the parent object
    return HUD_status;
}

void HUD_Status::updateHealthBar() {
    if (!target_ || !health_bar_ || !target_->getStatus())
        return;
    health_bar_->setPercentage(
        glm::vec2{target_->getStatus()->getHealth() / target_->getStatus()->getMaxHealth(), 1.0f});
}

void HUD_Status::updateManaBar() {
    if (!target_ || !mana_bar_ || !target_->getStatus())
        return;
    mana_bar_->setPercentage(glm::vec2{target_->getStatus()->getMana() / target_->getStatus()->getMaxMana(), 1.0f});
}