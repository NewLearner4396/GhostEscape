#include "Timer.h"

void Timer::update(float dT) {
    timer_ += dT;
    if (timer_ >= interval_){
        timer_ = 0;
        is_timeOut_ = true;
    }
}

Timer* Timer::addTimer(Object* parent, float interval, bool is_loop) {
    Timer* timer = new Timer();
    timer->setTimer(0);
    timer->setInterval(interval);
    timer->setActive(false);
    timer->setIsLoop(is_loop);
    if (parent)
        parent->safeAddObject(timer);
    return timer;
}

bool Timer::getIsTimeOut() {
    if (is_timeOut_) {
        is_timeOut_ = false;
        if (is_loop_)
            is_active_ = false;
        return true;
    }
    return false;
}
