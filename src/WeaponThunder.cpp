#include "WeaponThunder.h"

#include "Actor.h"
#include "Scene.h"
#include "Spell.h"

void WeaponThunder::init() {
    object_type_ = ObjectType::NONE;
    // TODO: set the collider of the spell
}

void WeaponThunder::handleEvents(SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (canAttack()) {
                auto pos = game_.getMousePosition() +
                           game_.getCurrentScene()->getCameraPosition();  // get the mouse position in world coordinates
                auto spell = Spell::addSpell(nullptr, "../assets/effect/Thunderstrike w blur.png", pos, 2.0f, 40.0f,
                                             Anchor::CENTER);
                attack(pos, spell);  // attack with the spell
            }
        }
    }
}

WeaponThunder* WeaponThunder::addWeaponThunder(Actor* parent, float mana_cost, float cooldown) {
    auto weapon = new WeaponThunder();  // create a new weapon object
    weapon->init();                     // initialize the weapon object
    weapon->setParent(parent);          // set the parent actor of the weapon
    weapon->mana_cost_ = mana_cost;     // set the mana cost of the weapon
    weapon->cooldown_ = cooldown;       // set the cooldown of the weapon
    parent->safeAddObject(weapon);      // add the weapon to the parent actor
    return weapon;                      // return the weapon object
}
