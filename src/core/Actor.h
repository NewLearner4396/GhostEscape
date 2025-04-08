#ifndef ACTOR_H
#define ACTOR_H
#include "ObjectWorld.h"

class Status;
class AffiliateBar;
class Actor : public ObjectWorld {
   public:
    virtual void update(float dT) override {
        ObjectWorld::update(dT);
        updateHealthBar();  // update the health bar
        position_ += velocity_ * dT;
    }

    void takeDamage(float damage) override;

    bool isAlive() const;

    // getters and setters
    Status* getStatus() const { return status_; }
    void setStatus(Status* status) { status_ = status; }
    AffiliateBar* getHealthBar() const { return health_bar_; }
    void setHealthBar(AffiliateBar* health_bar) { health_bar_ = health_bar; }
    glm::vec2 getVelocity() const { return velocity_; }
    void setVelocity(const glm::vec2& velocity) { velocity_ = velocity; }
    float getMaxSpeed() const { return max_speed_; }
    void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }
    float getAngle() const { return angle_; }
    void setAngle(float angle) { angle_ = angle; }

   protected:
    Status* status_ = nullptr;            // status of the actor
    AffiliateBar* health_bar_ = nullptr;  // health bar of the actor
    glm::vec2 velocity_;
    float max_speed_ = 50.0f;
    float angle_ = 0.0f;

   private:
    void updateHealthBar();
};

#endif  // ACTOR_H
