#ifndef SPRITE_ANIM_H
#define SPRITE_ANIM_H

#include "Sprite.h"

class SpriteAnim : public Sprite {
   private:
    int totalFrames_ = 0;
    int currentFrame_ = 0;
    int fps_ = 10;
    float frameTimer_ = 0;

    bool isLoop_ = true;


   public:
    virtual void update(float dT) override;

    static SpriteAnim* addSpriteAnim(ObjectScreen* object_parent, const std::string filePath, float scale = 1.0f, Anchor anchor = Anchor::CENTER); 
    
    // getters and setters
    virtual void setTexture(const Texture& texture) override;
    int getTotalFrames() const { return totalFrames_; }
    void setTotalFrames(int totalFrames) { this->totalFrames_ = totalFrames; }
    int getCurrentFrame() const { return currentFrame_; }
    void setCurrentFrame(int currentFrame) { this->currentFrame_ = currentFrame; }
    int getFps() const { return fps_; }
    void setFps(int fps) { fps_ = fps; }
    float getFrameTimer() const { return frameTimer_; }
    void setFrameTimer(float frameTimer) { frameTimer_ = frameTimer; }
    bool getIsLoop() const { return isLoop_; }
    void setIsLoop(bool isLoop) { isLoop_ = isLoop; }


};


#endif