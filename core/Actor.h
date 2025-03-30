#ifndef ACTOR_H
#define ACTOR_H
#include "ObjectWorld.h"

class Status;

class Actor : public ObjectWorld {
   protected:
    Status* status_ = nullptr;  // status of the actor
    glm::vec2 velocity_;
    float max_speed_ = 50.0f;
    float angle_ = 0.0f;

   public:
    virtual void update(float dT) override {
        position_ += velocity_ * dT;
        ObjectWorld::update(dT);
    }

    void takeDamage(float damage);
    bool isAlive() const;

    // getters and setters
    Status* getStatus() const { return status_; }
    void setStatus(Status* status) { status_ = status; }
    glm::vec2 getVelocity() const { return velocity_; }
    void setVelocity(const glm::vec2& velocity) { velocity_ = velocity; }
    float getMaxSpeed() const { return max_speed_; }
    void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }
    float getAngle() const { return angle_; }
    void setAngle(float angle) { angle_ = angle; }
};

#endif  // ACTOR_H
