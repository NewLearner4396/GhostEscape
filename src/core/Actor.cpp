#include "Actor.h"

#include "Status.h"

void Actor::takeDamage(float damage) {
    if (!status_) {
        return;
    }
    status_->takeDamage(damage);
}

bool Actor::isAlive() const { return status_ ? status_->getIsAlive() : false; }
