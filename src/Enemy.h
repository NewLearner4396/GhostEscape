#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "SpriteAnim.h"

class Enemy : public Actor {
   public:
    enum class EnemyState { NORMAL, HURT, DEAD };
    virtual void init() override;
    virtual void update(float dT) override;

    void aim_target(Player* target);
    EnemyState checkState();
    void changeState(EnemyState new_state);
    void attack();

    Player* getTarget() const { return target_; }
    void setTarget(Player* target) { target_ = target; }

   protected:
    Player* target_ = nullptr;

    EnemyState current_state_ = EnemyState::NORMAL;
    SpriteAnim* sprite_normal_ = nullptr;
    SpriteAnim* sprite_hurt_ = nullptr;
    SpriteAnim* sprite_dead_ = nullptr;
    SpriteAnim* current_anim_ = nullptr;
    float timer_ = 0.0f;
};

#endif  // ENEMY_H
