#ifndef PLAYER_H
#define PLAYER_H
#include "Actor.h"
#include "Effect.h"
#include "SpriteAnim.h"
#include "Status.h"
#include "WeaponThunder.h"

class Player : public Actor {
   public:
    Player() = default;
    ~Player() = default;

    void init() override;
    void clean() override;
    void handleEvents(SDL_Event& event) override;
    void update(float dT) override;
    void render() override;

    void playerMove(float dT);
    void syncCamera();
    void checkState();
    void changeState(bool is_moving);
    void checkIsAlive();

   private:
    float speed_ = 50.0f;
    float acceleration_ = 1.0f;
    float deceleration_ = 0.9f;
    bool is_moving_ = false;
    SpriteAnim* sprite_idle_ = nullptr;
    SpriteAnim* sprite_move_ = nullptr;
    Effect* deadEffect_ = nullptr;
    WeaponThunder* weapon_thunder_ = nullptr;
};

#endif  // PLAYER_H
