#include "SpriteAnim.h"

void SpriteAnim::update(float dT) {
    if (isFinished_) {
        return;
    }
    if (totalFrames_ <= 0) {
        return;
    }
    frameTimer_ += dT;
    if (frameTimer_ >= 1.0f / fps_) {
        currentFrame_ = (currentFrame_ + 1);
        if (currentFrame_ >= totalFrames_) {
            currentFrame_ = 0;
            if (!isLoop_)
                isFinished_ = true;
        }
        frameTimer_ = 0;
    }
    texture_.srcRect.x = currentFrame_ * texture_.srcRect.w;
}

/**
 * @brief addSpriteAnim and link it to the object_parent
 *
 * @param object_parent
 * @param filePath
 * @param scale
 * @return SpriteAnim*
 */
SpriteAnim* SpriteAnim::addSpriteAnim(ObjectScreen* object_parent, const std::string filePath, float scale,
                                      Anchor anchor) {
    auto sprite_anim = new SpriteAnim();
    sprite_anim->init();
    sprite_anim->setAnchor(anchor);
    sprite_anim->setTexture(Texture(filePath));
    sprite_anim->setScale(scale);
    sprite_anim->setParent(object_parent);
    object_parent->addObject(sprite_anim);
    return sprite_anim;
}

void SpriteAnim::setTexture(const Texture& texture) {
    texture_ = texture;
    totalFrames_ = static_cast<int>(texture_.srcRect.w / texture_.srcRect.h);
    if (totalFrames_ <= 0) {
        totalFrames_ = 1;
        std::cerr << "Error: totalFrames_ is less than or equal to 0" << std::endl;
    }
    texture_.srcRect.w = texture_.srcRect.h;
    size_ = glm::vec2(texture_.srcRect.w, texture_.srcRect.h);
}
