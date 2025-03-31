#include "Player.h"

#include "Collider.h"
#include "Scene.h"
#include "SpriteAnim.h"

void Player::init() {
    Actor::init();
    setMaxSpeed(100.0f);

    sprite_idle_ = SpriteAnim::addSpriteAnim(this, "../assets/sprite/ghost-idle.png", 2.0f);
    sprite_move_ = SpriteAnim::addSpriteAnim(this, "../assets/sprite/ghost-move.png", 2.0f);
    sprite_move_->setActive(false);

    collider_ = Collider::addCollider(this, sprite_idle_->getSize() / 2.0f);
    status_ = Status::addStatus(this);
    deadEffect_ = Effect::addEffect(nullptr, "../assets/effect/1764.png", getPosition(), 2.0f);
    weapon_thunder_ = WeaponThunder::addWeaponThunder(this, 10.0f, 2.0f);
}

void Player::clean() { Actor::clean(); }

void Player::handleEvents(SDL_Event& event) { Actor::handleEvents(event); }

void Player::update(float dT) {
    Actor::update(dT);
    playerMove(dT);
    checkState();
    syncCamera();
    checkIsAlive();
    // TODO: if player is invincible, add transparency effect to the player
}

void Player::render() {
    Actor::render();
    // TODO: render the health bar and mana bar
    // render player
    // glm::vec2 start = getRenderPosition();
    // glm::vec2 end = start + glm::vec2(20.0f, 20.0f);
    // game_.drawBoundary(start, end, 5.0f, {1.0f, 0.0f, 0.0f, 1.0f}, false);
}

void Player::playerMove(float dT) {
    auto currentKeyState = SDL_GetKeyboardState(nullptr);
    if (currentKeyState[SDL_SCANCODE_W]) {
        velocity_.y -= speed_;
    }
    if (currentKeyState[SDL_SCANCODE_S]) {
        velocity_.y += speed_;
    }
    if (currentKeyState[SDL_SCANCODE_A]) {
        velocity_.x -= speed_;
    }
    if (currentKeyState[SDL_SCANCODE_D]) {
        velocity_.x += speed_;
    }
    // key R to reset
    if (currentKeyState[SDL_SCANCODE_R]) {
        velocity_ = glm::vec2(0.0f, 0.0f);
        setRenderPosition(game_.getCurrentScene()->getCameraSize() / 2.0f);
    }
    setPosition(position_ + velocity_ * dT);
    position_ = glm::clamp(position_, glm::vec2(0.0f, 0.0f),
                           game_.getCurrentScene()->getWorldSize());  // prevent player from going out of the world
    velocity_ *= deceleration_;                                       // add inertia
}

void Player::syncCamera() { game_.getCurrentScene()->setCameraPosition(position_ - game_.getWindowSize() / 2.0f); }

void Player::checkState() {
    if (velocity_.x < 0) {
        sprite_move_->setFlip(true);
        sprite_idle_->setFlip(true);
    } else {
        sprite_move_->setFlip(false);
        sprite_idle_->setFlip(false);
    }
    bool new_is_moving = (glm::length(velocity_) > 0.1f);
    if (new_is_moving != is_moving_) {
        is_moving_ = new_is_moving;
        changeState(is_moving_);
    }
}

void Player::changeState(bool is_moving) {
    if (is_moving) {
        sprite_idle_->setActive(false);
        sprite_move_->setActive(true);
        sprite_move_->setCurrentFrame(sprite_idle_->getCurrentFrame());
        sprite_move_->setFrameTimer(sprite_idle_->getFrameTimer());
    } else {
        sprite_idle_->setActive(true);
        sprite_move_->setActive(false);
        sprite_idle_->setCurrentFrame(sprite_move_->getCurrentFrame());
        sprite_idle_->setFrameTimer(sprite_move_->getFrameTimer());
    }
}

void Player::checkIsAlive() {
    if (!status_->getIsAlive()) {
        setActive(false);
        deadEffect_->setPosition(getPosition());
        game_.getCurrentScene()->safeAddObject(deadEffect_);
    }
}
