#ifndef SPAWNER_H
#define SPAWNER_H

#include "Object.h"

class Enemy;
class Player;
class Spawner : public Object {
    protected:
    int num_objects_ = 0;
    int max_objects_ = 20;
    float timer_ = 0.0f;
    float interval_ = 1.0f;
    Player* target_ = nullptr; // target to spawn enemies

    public:
    virtual void init() override { object_type_ = ObjectType::NONE; }
    virtual void update(float dT) override;

    // getters and setters
    int getNumObjects() const { return num_objects_; }
    void setNumObjects(int num_objects) { num_objects_ = num_objects; }
    int getMaxObjects() const { return max_objects_; }
    void setMaxObjects(int max_objects) { max_objects_ = max_objects; }
    float getInterval() const { return interval_; }
    void setInterval(float interval) { interval_ = interval; }
    Player* getTarget() const { return target_; }
    void setTarget(Player* target) { target_ = target; }
    
};

#endif // SPAWNER_H
