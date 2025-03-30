#include "Status.h"

void Status::update(float dT) {
    Object::update(dT);
    regenMana(dT);
    if (is_invincible_) {
        invincible_timer_ += dT;
        if (invincible_timer_ >= invincible_duration_) {
            is_invincible_ = false;
            invincible_timer_ = 0.0f;  // reset the invincible timer
        }
    }
}

void Status::regenMana(float dT) {
    mana_ += mana_regen_ * dT;
    if (mana_ > max_mana_) {
        mana_ = max_mana_;
    }
}

bool Status::canUseMana(float manaCost) { return mana_ >= manaCost; }

void Status::useMana(float manaCost) {
    if (canUseMana(manaCost)) {
        mana_ -= manaCost;
        if (mana_ < 0) {
            mana_ = 0;
        }
    }
}

void Status::takeDamage(float damage) {
    if (is_invincible_) {
        return;
    }
    health_ -= damage;
    if (health_ <= 0) {
        health_ = 0;
        is_alive_ = false;
    }
#ifdef DEBUG_MODE
    SDL_Log("Status::takeDamage: health = %f", health_);
#endif
    is_invincible_ = true;
    invincible_timer_ = 0.0f;  // reset the invincible timer
}

Status* Status::addStatus(Actor* parent, float health, float max_health, float mana, float max_mana, float mana_regen,
                          float stamina, float max_stamina, float damage) {
    Status* status = new Status();
    status->init();
    status->setParent(parent);
    status->setHealth(health);
    status->setMaxHealth(max_health);
    status->setMana(mana);
    status->setMaxMana(max_mana);
    status->setManaRegen(mana_regen);
    status->setStamina(stamina);
    status->setMaxStamina(max_stamina);
    status->setDamage(damage);
    parent->addObject(status);
    return status;
}
