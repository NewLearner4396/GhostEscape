#include "Weapon.h"

#include "Actor.h"
#include "Scene.h"
#include "Spell.h"
#include "Status.h"

void Weapon::update(float dT) {
    Object::update(dT);
    cooldown_timer_ += dT;  // increase the cooldown timer
}

bool Weapon::canAttack() {
    if (cooldown_timer_ < cooldown_)
        return false;  // check if the cooldown is over
    if (!parent_->getStatus()->canUseMana(mana_cost_))
        return false;  // check if the actor has enough mana
    return true;
}

/**
 * @brief attack the target with the spell 
 * ! before using this function, make sure canAttack() is true
 *
 */
void Weapon::attack(glm::vec2 position, Spell* spell) {
    if (spell == nullptr) {  // check if the spell is valid
#ifdef DEBUG_MODE
        SDL_Log("Weapon::attack: spell is nullptr\n");
#endif
        return;
    }
    parent_->getStatus()->useMana(mana_cost_);      // use mana
    spell->setPosition(position);                   // set the position of the spell
    game_.getCurrentScene()->safeAddObject(spell);  // add the spell to the scene
}
