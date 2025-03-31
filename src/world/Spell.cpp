#include "Spell.h"

#include "Collider.h"
#include "Enemy.h"
#include "Scene.h"
#include "SpriteAnim.h"

void Spell::update(float dT) {
    ObjectWorld::update(dT);  // call the update function of the parent class
    if (sprite_->getIsFinished())
        need_remove_ = true;  // remove the spell when the animation is finished
    attack();                 // call the attack function to deal damage
}

Spell* Spell::addSpell(Object* parent, const std::string& file_path, glm::vec2 pos, float scale, float damage,
                       Anchor anchor) {
    auto spell = new Spell();  // create a new spell object
    spell->init();             // initialize the spell object
    spell->setDamage(damage);  // set the damage of the spell
    spell->sprite_ =
        SpriteAnim::addSpriteAnim(spell, file_path, scale, anchor);  // add the sprite animation to the spell:
    spell->sprite_->setIsLoop(false);                                // set the animation to not loop
    spell->setPosition(pos);                                         // set the position of the spell
    spell->collider_ = Collider::addCollider(spell, spell->sprite_->getSize(), Collider::ColliderType::CIRCLE,
                                             anchor);  // add a collider to the spell
    if (parent)
        parent->safeAddObject(spell);  // add the spell to the parent object
    return spell;                      // return the spell object
}

void Spell::attack() {
    auto objects = game_.getCurrentScene()->getObjectsWorld();  // get all the objects in the world
    for (auto& object : objects) {
        if (object->getObjectType() == ObjectType::ENEMY) {  // check if the object is an enemy
            auto enemy = dynamic_cast<Enemy*>(object);       // cast the object to an enemy
            if (collider_ && enemy->getCollider() &&
                collider_->isColliding(enemy->getCollider())) {  // check if the spell collides with the enemy
                enemy->takeDamage(damage_);                      // deal damage to the enemy
                break;                                           // exit the loop after dealing damage to one enemy
            }
        }
    }
}
