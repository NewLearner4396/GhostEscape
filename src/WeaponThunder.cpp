#include "WeaponThunder.h"

#include "Actor.h"
#include "HUD_Skill.h"
#include "Scene.h"
#include "Spell.h"
void WeaponThunder::init() {
    object_type_ = ObjectType::NONE;
    auto scene = game_.getCurrentScene();                     // get the current scene
    auto pos = glm::vec2(game_.getWindowSize().x - 300, 30);  // set the position of the HUD skill
    HUD_skill_ = HUD_Skill::addHUDSkill(scene, "../assets/UI/Electric-Icon.png", pos, 0.14f,
                                        Anchor::CENTER);  // create the HUD skill for the weapon
    // TODO: set the collider of the spell
}

void WeaponThunder::handleEvents(SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (canAttack()) {
                auto pos = game_.getMousePosition() +
                           game_.getCurrentScene()->getCameraPosition();  // get the mouse position in world coordinates
                auto spell = Spell::addSpell(nullptr, "../assets/effect/Thunderstrike w blur.png", pos, 2.0f, 60.0f,
                                             Anchor::CENTER);
                attack(pos, spell);  // attack with the spell
                cooldown_timer_ = 0.0f;  // reset the cooldown timer
            }
        }
    }
}

void WeaponThunder::update(float dT) {
    Weapon::update(dT);  // update the weapon
    if (HUD_skill_) {
        HUD_skill_->setPercentage(
            (cooldown_timer_ / cooldown_));  // update the HUD skill percentage
    }
}

WeaponThunder* WeaponThunder::addWeaponThunder(Actor* parent, float mana_cost, float cooldown) {
    auto weapon = new WeaponThunder();  // create a new weapon object
    weapon->init();                     // initialize the weapon object
    weapon->setParent(parent);          // set the parent actor of the weapon
    weapon->mana_cost_ = mana_cost;     // set the mana cost of the weapon
    weapon->cooldown_ = cooldown;       // set the cooldown of the weapon
    weapon->cooldown_timer_ = cooldown;
    parent->safeAddObject(weapon);      // add the weapon to the parent actor
    return weapon;                      // return the weapon object
}
