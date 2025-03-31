#ifndef WEAPON_H
#define WEAPON_H
#include "Object.h"

class Actor;
class Spell;
class Weapon : public Object {
   public:
    virtual void update(float dT) override;

    void attack(glm::vec2 position, Spell* spell);  // attack with the weapon
    bool canAttack();                               // check if the weapon can attack

    Actor* getParent() const { return parent_; }         // get the actor of the weapon
    void setParent(Actor* parent) { parent_ = parent; }  // set the actor of the weapon

   protected:
    Actor* parent_ = nullptr;  // actor of the weapon

    float mana_cost_ = 0.0f;       // mana cost of the weapon
    float cooldown_ = 1.0f;        // cooldown of the weapon
    float cooldown_timer_ = 0.0f;  // cooldown time of the weapon
};

#endif  // WEAPON_H
