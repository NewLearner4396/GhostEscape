#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "ObjectAffiliate.h"

struct Texture {
    SDL_Texture* texture = nullptr;
    SDL_FRect srcRect = {0, 0, 0, 0};
    SDL_FColor color = {1.0f, 1.0f, 1.0f, 1.0f};
    float alpha = 1.0f;
    float angle = 0.0f;
    bool isFlip = false;
    Texture() = default;
    Texture(std::string filePath);
};

class Sprite : public ObjectAffiliate {
   protected:
    Texture texture_;
    bool isFinished_ = false;

   public:
    virtual void render() override;

    static Sprite* addSprite(ObjectScreen* object_parent, const std::string filePath, float scale = 1.0f,
                             Anchor anchor = Anchor::CENTER);

    // getters and setters
    Texture getTexture() const { return texture_; }
    virtual void setTexture(const Texture& texture);
    float getAlpha() const { return texture_.alpha; }
    void setAlpha(float alpha) { texture_.alpha = alpha; }
    float getAngle(float angle) { texture_.angle = angle; }
    void SetAngle(float angle) { texture_.angle = angle; }
    bool isFlip() { return texture_.isFlip; }
    void setFlip(bool isFlip) { texture_.isFlip = isFlip; }
    bool getIsFinished() const { return isFinished_; }
    void setIsFinished(bool isFinished) { isFinished_ = isFinished; }
};

#endif