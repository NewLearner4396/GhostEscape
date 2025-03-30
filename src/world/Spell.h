#ifndef SPELL_H
#define SPELL_H
// a class about the spell of sprite(player)
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
    float getManaCost() const { return mana_cost_; }
    void setManaCost(float mana_cost) { mana_cost_ = mana_cost; }
    float getCooldown() const { return cooldown_; }
    void setCooldown(float cooldown) { cooldown_ = cooldown; }
    float getDuration() const { return duration_; }
    void setDuration(float duration) { duration_ = duration; }
    bool getIsActive() const { return is_active_; }
    void setIsActive(bool is_active) { is_active_ = is_active; }

   protected:
    SpriteAnim* sprite_ = nullptr;  // sprite of the spell
    float damage_ = 30.0f;          // damage of the spell
    float mana_cost_ = 0.0f;        // mana cost of the spell
    float cooldown_ = 0.0f;         // cooldown of the spell
    float duration_ = 0.0f;         // duration of the spell
    bool is_active_ = false;        // is the spell active
   private:
    void attack();  // attack with the spell
};

#endif  // SPELL_H
