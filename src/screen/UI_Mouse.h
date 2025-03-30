#ifndef UI_MOUSE_H
#define UI_MOUSE_H

#include "ObjectScreen.h"

class Sprite;
class UI_Mouse : public ObjectScreen {
   public:
    virtual void init() override { object_type_ = ObjectType::OBJECT_SCREEN; }
    virtual void update(float dT) override;

    static UI_Mouse* addMouse(Object* parent, const std::string& file_path1, const std::string& file_path2,
                              float scale = 1.0f, Anchor anchor = Anchor::CENTER);

    // getters and setters
    Sprite* getSprite1() const { return sprite1_; }
    void setSprite1(Sprite* sprite) { sprite1_ = sprite; }
    Sprite* getSprite2() const { return sprite2_; }
    void setSprite2(Sprite* sprite) { sprite2_ = sprite; }

   protected:
    Sprite* sprite1_ = nullptr;
    Sprite* sprite2_ = nullptr;
    float timer_ = 0.0f;
};

#endif  // UI_MOUSE_H
