#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "SpriteAnim.h"

class Enemy : public Actor {
   public:
    enum class EnemyState { NORMAL, HURT, DEAD };
    virtual void init() override;
    virtual void update(float dT) override;

    static Enemy* addEnemy(Object* parent, glm::vec2 pos, Player* target = nullptr);

    Player* getTarget() const { return target_; }
    void setTarget(Player* target) { target_ = target; }
    EnemyState getState() const { return current_state_; }
    void setState(EnemyState state) { current_state_ = state; }

   protected:
    Player* target_ = nullptr;

    EnemyState current_state_ = EnemyState::NORMAL;
    SpriteAnim* sprite_normal_ = nullptr;
    SpriteAnim* sprite_hurt_ = nullptr;
    SpriteAnim* sprite_dead_ = nullptr;
    SpriteAnim* current_anim_ = nullptr;
    float timer_ = 0.0f;
    float score_ = 10.0f; // score when killed
   private:
    void aim_target(Player* target);
    void move(float dT);
    void checkState();
    void changeState(EnemyState new_state);
    void remove();
    void attack();
};

#endif  // ENEMY_H
