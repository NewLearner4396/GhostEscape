#include "Actor.h"

#include "Status.h"
#include "AffiliateBar.h"

void Actor::takeDamage(float damage) {
    if (!status_) {
        return;
    }
    status_->takeDamage(damage);
}

bool Actor::isAlive() const { return status_ ? status_->getIsAlive() : false; }

void Actor::updateHealthBar() {
    if(!health_bar_ || !status_) 
        return;
    health_bar_->setBarWidthPercentage(status_->getHealth() / status_->getMaxHealth());    
}
