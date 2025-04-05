#include "Enemy.h"

#include "AffiliateBar.h"
#include "Collider.h"
#include "Scene.h"
#include "SceneMain.h"
#include "Spawner.h"
#include "Status.h"

void Enemy::init() {
    Actor::init();
    setMaxSpeed(50.0f);

    sprite_normal_ = SpriteAnim::addSpriteAnim(this, "../assets/sprite/ghost-Sheet.png", 2.0f);
    sprite_hurt_ = SpriteAnim::addSpriteAnim(this, "../assets/sprite/ghostHurt-Sheet.png", 2.0f);
    sprite_hurt_->setActive(false);
    sprite_dead_ = SpriteAnim::addSpriteAnim(this, "../assets/sprite/ghostDead-Sheet.png", 2.0f);
    sprite_dead_->setActive(false);
    sprite_dead_->setIsLoop(false);

    current_anim_ = sprite_normal_;
    collider_ = Collider::addCollider(this, sprite_normal_->getSize());
    status_ = Status::addStatus(this);
    status_->setDamage(50.0f);
    auto _size = sprite_normal_->getSize();
    health_bar_ = AffiliateBar::addAffiliateBar(this, glm::vec2(_size.x - 10, 10), Anchor::BOTTOM_CENTER);
    health_bar_->setOffset(health_bar_->getOffset() + glm::vec2(0, -_size.y / 2 + 5));
    setObjectType(ObjectType::ENEMY);
}

void Enemy::update(float dT) {
    Actor::update(dT);
    if (target_->getActive()) {
        aim_target(target_);  // get the position and direction of the target
        move(dT);             // move towards the target
        attack();
    }
    checkState();  // check the state of the enemy
    remove();      // check if the enemy is dead
}

Enemy* Enemy::addEnemy(Object* parent, glm::vec2 pos, Player* target) {
    auto enemy = new Enemy();
    enemy->init();
    enemy->setPosition(pos);
    enemy->setMaxSpeed(50.0f);
    enemy->setTarget(target);
    if (parent)
        parent->safeAddObject(enemy);
    return enemy;
}

void Enemy::aim_target(Player* target) {
    if (target == nullptr)
        return;
    auto direction = target->getPosition() - this->getPosition();
    direction = glm::normalize(direction);
}

void Enemy::move(float dT) {
    if (target_ == nullptr)
        return;
    velocity_ = velocity_ * 0.9f + (target_->getPosition() - position_) * max_speed_ * 0.1f * dT;
    position_ += velocity_ * dT;
    position_ = glm::clamp(position_, glm::vec2(0.0f, 0.0f),
                           game_.getCurrentScene()->getWorldSize());  // prevent player from going out of the world
    setPosition(position_);
}

void Enemy::checkState() {
    EnemyState new_state;
    if (status_ && status_->getHealth() <= 0) {
        new_state = EnemyState::DEAD;
    } else if (status_ && status_->getInvincibleDuration() > 0) {
        new_state = EnemyState::HURT;
    } else {
        new_state = EnemyState::NORMAL;
    }
    if (new_state != current_state_) {
        changeState(new_state);
    }
}

void Enemy::changeState(EnemyState new_state) {
    current_anim_->setActive(false);
    switch (new_state) {
    case EnemyState::NORMAL:
        current_anim_ = sprite_normal_;
        current_anim_->setActive(true);
        break;
    case EnemyState::HURT:
        current_anim_ = sprite_hurt_;
        current_anim_->setActive(true);
        break;
    case EnemyState::DEAD:
        current_anim_ = sprite_dead_;
        current_anim_->setActive(true);
        game_.setScore(game_.getScore() + score_);
        break;
    }
    current_state_ = new_state;
}

/**
 * @brief Check if the enemy is dead and remove it from the scene
 *
 */
void Enemy::remove() {
    if (sprite_dead_->getIsFinished()) {
        need_remove_ = true;
        // Remove the enemy from the spawner
        auto scene_main = dynamic_cast<SceneMain*>(game_.getCurrentScene());
        if (scene_main && scene_main->getSpawner()) {
            scene_main->getSpawner()->setNumObjects(scene_main->getSpawner()->getNumObjects() -
                                                    1);  // Decrease the number of enemies
        }
    }
}

void Enemy::attack() {
    if (!collider_ || !target_ || !target_->getCollider())
        return;
    if (collider_->isColliding(target_->getCollider())) {
        if (status_ && target_->getStatus()) {
            target_->takeDamage(status_->getDamage());
        }
    }
}
