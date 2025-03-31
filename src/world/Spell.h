#ifndef SPELL_H
#define SPELL_H
// a class about the spell of player
#include "ObjectWorld.h"

class SpriteAnim;
class Spell : public ObjectWorld {
   public:
    virtual void update(float dT) override;

    static Spell* addSpell(Object* parent, const std::string& file_path, glm::vec2 pos, float scale = 1.0f,
                           float damage = 30.0f, Anchor anchor = Anchor::CENTER);

    // getters and setters
    float getDamage() const { return damage_; }
    void setDamage(float damage) { damage_ = damage; }

   protected:
    SpriteAnim* sprite_ = nullptr;  // sprite of the spell
    float damage_ = 30.0f;          // damage of the spell
   private:
    void attack();  // attack with the spell
};

#endif  // SPELL_H
