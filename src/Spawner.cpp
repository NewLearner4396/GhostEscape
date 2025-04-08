#include "Spawner.h"

#include "Effect.h"
#include "Enemy.h"
#include "Scene.h"

void Spawner::update(float dT) {
    timer_ += dT;
    if (timer_ >= interval_) {
        timer_ = 0.0f;
        if (!target_ || !target_->getActive()) {
#ifdef DEBUG_MODE
            SDL_Log("Error: Target is null or inactive in Spawner::update()");
#endif
            return;  // target is not active, do not spawn enemies
        }
        auto currentScene = game_.getCurrentScene();
        if (!currentScene) {
#ifdef DEBUG_MODE
            SDL_Log("Error: Current scene is null in Spawner::update()");
#endif
            return;  // current scene is not valid, do not spawn enemies
        }
        // Only spawn new enemies if we're below the max
        while (num_objects_ < max_objects_) {
            glm::vec2 pos = game_.randomVec2(currentScene->getCameraPosition(),
                                             currentScene->getCameraPosition() +
                                                 currentScene->getCameraSize());  // Generate random position on screen
            Enemy* enemy = Enemy::addEnemy(nullptr, pos, target_);  // Create enemy with proper error checking

            // Set enemy properties
            enemy->setMaxSpeed(game_.randomFloat(30.0f, 50.0f));

            Effect::addEffect(currentScene, "../assets/effect/184_3.png", pos, 1.0f, enemy);  // Add enemy to scene
            game_.playSound("../assets/sound/silly-ghost-sound-242342.mp3");
            num_objects_++;  // Increment counter
        }
    }
}