#include "Sprite.h"

Texture::Texture(std::string filePath) {
    texture = Game::getInstance().getAssetStore()->getImage(filePath);
    SDL_GetTextureSize(texture, &srcRect.w, &srcRect.h);
}

void Sprite::setTexture(const Texture& texture) {
    texture_ = texture;
    if (texture_.texture) {
        SDL_GetTextureSize(texture_.texture, &texture_.srcRect.w, &texture_.srcRect.h);
        size_.x = texture_.srcRect.w;
        size_.y = texture_.srcRect.h;
    }
}
void Sprite::render() {
    if (!texture_.texture) {
        return;
    }
    if (!parent_) {
        return;
    }
    if (isFinished_) {
        return;
    }
    auto pos = parent_->getRenderPosition() + offset_;
    game_.renderTexture(texture_, pos, size_);
}
/**
 * @brief addSprite and link it to the object_parent
 *
 *
 * @param object_parent
 * @param filePath
 * @param scale
 * @return Sprite*
 */
Sprite* Sprite::addSprite(ObjectScreen* object_parent, const std::string filePath, float scale, Anchor anchor) {
    auto sprite = new Sprite();
    sprite->init();
    sprite->setAnchor(anchor);
    sprite->setTexture(Texture(filePath));
    sprite->setScale(scale);
    sprite->setParent(object_parent);
    object_parent->addObject(sprite);
    return sprite;
}
