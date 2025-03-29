#ifndef SPAWNER_H
#define SPAWNER_H

#include "Object.h"

class Spawner : public Object {
    protected:
    int num_objects_ = 0;
    int max_objects_ = 0;
    float spawn_time_ = 0.0f;
    float interval_ = 0.0f;

    public:
    virtual void update(float dT) override;

    // getters and setters
    int getNumObjects() const { return num_objects_; }
    void setNumObjects(int num_objects) { num_objects_ = num_objects; }
    int getMaxObjects() const { return max_objects_; }
    void setMaxObjects(int max_objects) { max_objects_ = max_objects; }
    float getSpawnTime() const { return spawn_time_; }
    void setSpawnTime(float spawn_time) { spawn_time_ = spawn_time; }
    float getInterval() const { return interval_; }
    void setInterval(float interval) { interval_ = interval; }
    
};

#endif // SPAWNER_H
