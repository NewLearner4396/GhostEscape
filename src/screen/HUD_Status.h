#ifndef HUD_STATUS_H
#define HUD_STATUS_H

#include "ObjectScreen.h"

class Sprite;
class Actor;
class HUD_Status : public ObjectScreen {
   public:
    virtual void init() override;
    virtual void update(float dT) override;

    static HUD_Status* addHUDStatus(Object* parent, Actor* target, glm::vec2 render_position);

    // getters and setters
    Sprite* getHealthBar() const { return health_bar_; }
    Sprite* getHealthBarBg() const { return health_bar_bg_; }
    Sprite* getHealthBarIcon() const { return health_bar_icon_; }
    Sprite* getManaBar() const { return mana_bar_; }
    Sprite* getManaBarBg() const { return mana_bar_bg_; }
    Sprite* getManaBarIcon() const { return mana_bar_icon_; }

    float getHealthPercentage() const { return health_percentage_; }
    void setHealthPercentage(float percentage) { health_percentage_ = percentage; }
    float getManaPercentage() const { return mana_percentage_; }
    void setManaPercentage(float percentage) { mana_percentage_ = percentage; }
    Actor* getTarget() const { return target_; }
    void setTarget(Actor* target) { target_ = target; }

   protected:
    Sprite* health_bar_ = nullptr;       // Health bar sprite
    Sprite* health_bar_bg_ = nullptr;    // Health bar background sprite
    Sprite* health_bar_icon_ = nullptr;  // Health bar icon sprite
    Sprite* mana_bar_ = nullptr;         // Mana bar sprite
    Sprite* mana_bar_bg_ = nullptr;      // Mana bar background sprite
    Sprite* mana_bar_icon_ = nullptr;    // Mana bar icon sprite

    Actor* target_ = nullptr;  // Actor associated with the HUD status

    float health_percentage_ = 0.5f;  // Health percentage (1.0 = full health)
    float mana_percentage_ = 1.0f;    // Mana percentage (1.0 = full mana)
                                      // TODO: more var about the position or the size of the bar
   private:
    void updateHealthBar();  // Update the health bar based on the actor's status
    void updateManaBar();    // Update the mana bar based on the actor's status
};

#endif  // HUD_STATUS_H
