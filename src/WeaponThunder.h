#ifndef WEAPONTHUNDER_H
#define WEAPONTHUNDER_H

#include "Weapon.h"

class HUD_Skill;
class WeaponThunder : public Weapon {
   public:
    virtual void init() override ;
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dT) override;

    static WeaponThunder* addWeaponThunder(Actor* parent, float mana_cost, float cooldown);
    protected:
    HUD_Skill* HUD_skill_ = nullptr;  // skill of the weapon
};

#endif  // WEAPONTHUNDER_H
