#ifndef STATUS_H
#define STATUS_H

#include "Actor.h"

class Status : public Object{
    public:
        virtual void init() override { object_type_ = ObjectType::NONE; }
        virtual void update(float dT) override;

        void regenMana(float dT);
        bool canUseMana(float manaCost);
        void useMana(float manaCost);
        void takeDamage(float damage);

        // getters and setters
        Actor* getParent() const { return parent_; }
        void setParent(Actor* parent) { parent_ = parent; }
        float getHealth() const { return health_; }
        void setHealth(float health) { health_ = health; }
        float getMaxHealth() const { return max_health_; }
        void setMaxHealth(float max_health) { max_health_ = max_health; }
        float getMana() const { return mana_; }
        void setMana(float mana) { mana_ = mana; }
        float getMaxMana() const { return max_mana_; }
        void setMaxMana(float max_mana) { max_mana_ = max_mana; }
        float getManaRegen() const { return mana_regen_; }
        void setManaRegen(float mana_regen) { mana_regen_ = mana_regen; }
        float getStamina() const { return stamina_; }
        void setStamina(float stamina) { stamina_ = stamina; }
        float getMaxStamina() const { return max_stamina_; }
        void setMaxStamina(float max_stamina) { max_stamina_ = max_stamina; }
        float getDamage() const { return damage_; }
        void setDamage(float damage) { damage_ = damage; }
        bool getIsAlive() const { return is_alive_; }
        void setIsAlive(bool is_alive) { is_alive_ = is_alive; }
        float getInvincibleDuration() const { return invincible_duration_; }
        void setInvincibleDuration(float time_s) { invincible_duration_ = time_s; }
        bool isInvincible() const { return is_invincible_; }
        void setInvincible(bool is_invincible) { is_invincible_ = is_invincible; }
        
        static Status* addStatus(Actor* parent, float health = 100.0f, float max_health = 100.0f,
                         float mana = 100.0f, float max_mana = 150.0f, float mana_regen = 1.0f,
                         float stamina = 50.0f, float max_stamina = 50.0f, float damage = 10.0f);
    protected:
        Actor* parent_ = nullptr;

        float health_ = 100.0f;
        float max_health_ = 100.0f;
        float mana_ = 100.0f;
        float max_mana_ = 150.0f;
        float mana_regen_ = 1.0f;
        float stamina_ = 50.0f;
        float max_stamina_ = 50.0f;
        float damage_ = 20.0f;

        bool is_alive_ = true;
        float invincible_duration_ = 1.5f; // time to be invincible after taking damage
        float invincible_timer_ = 0.0f; // timer for invincibility
        bool is_invincible_ = false;
};

#endif