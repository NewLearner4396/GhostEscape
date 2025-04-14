#ifndef TIMER_H
#define TIMER_H

#include "ObjectAffiliate.h"

class Timer : public ObjectAffiliate {
   public:
    void update(float dT) override;

    static Timer* addTimer(Object* parent, float interval = 3.0f,
                           bool is_loop = false);  //* Timer when created will be set to inactive

    void start() { is_active_ = true; }
    void stop() { is_active_ = false; }
    void reset() { timer_ = 0; }
    bool getIsTimeOut();
    float getProgress() const {
        if (interval_ == 0)
            return 0;
        return timer_ / interval_;
    }

    float getTimer() const { return timer_; }
    void setTimer(float timer) { timer_ = timer; }
    float getInterval() const { return interval_; }
    void setInterval(float interval) { interval_ = interval; }
    bool getIsLoop() const { return is_loop_; }
    void setIsLoop(bool is_loop) { is_loop_ = is_loop; }

   protected:
    float timer_ = 0;
    float interval_ = 0;
    bool is_timeOut_ = false;
    bool is_loop_ = false;
};

#endif  // TIMER_H
