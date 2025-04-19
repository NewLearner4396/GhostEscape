#include "Effect.h"

#include "Scene.h"

Effect* Effect::addEffect(Object* parent, const std::string& file_path, glm::vec2 pos, float scale,
                          ObjectWorld* next_object) {
    auto effect = new Effect();
    effect->init();
    effect->sprite_ = SpriteAnim::addSpriteAnim(effect, file_path, scale);
    effect->sprite_->setIsLoop(false);
    effect->setPosition(pos);
    effect->next_object_ = next_object;
    if (parent)
        parent->safeAddObject(effect);
    return effect;
}

void Effect::update(float dT) {
    ObjectWorld::update(dT);
    checkFinish();
}

void Effect::clean(){
    if (next_object_){
        next_object_->clean();
        delete next_object_;
        next_object_ = nullptr;
    }
    ObjectWorld::clean();
}

void Effect::checkFinish(void) {
    if (sprite_ && sprite_->getIsFinished()) {
        need_remove_ = true;
        if (next_object_) {
            game_.getCurrentScene()->safeAddObject(next_object_);
            next_object_ = nullptr;
        }
    }
}