#ifndef WEAPONTHUNDER_H
#define WEAPONTHUNDER_H

#include "Weapon.h"

class WeaponThunder : public Weapon {
   public:
    virtual void init() override ;  // initialize the weapon
    virtual void handleEvents(SDL_Event& event) override;

    static WeaponThunder* addWeaponThunder(Actor* parent, float mana_cost, float cooldown);
};

#endif  // WEAPONTHUNDER_H
