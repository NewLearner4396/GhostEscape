#ifndef HUD_BUTTON_H
#define HUD_BUTTON_H

#include "ObjectScreen.h"

class Sprite;
class HUD_Button : public ObjectScreen {
   public:
    void handleEvents(SDL_Event& event) override;
    void update(float) override {
        checkHover();
        checkState();
    }

    static HUD_Button* addHUDButton(Object* parent, glm::vec2 render_pos, const std::string& file_path_normal,
                                    const std::string& file_path_hover, const std::string& file_path_press,
                                    float scale = 1.0f, Anchor anchor = Anchor::CENTER);

    void checkHover();
    void checkState();
    // getters and setters
    bool getIsHover() const { return is_hover_; }
    void setIsHover(bool is_hover) { is_hover_ = is_hover; }
    bool getIsPress() const { return is_press_; }
    void setIsPress(bool is_press) { is_press_ = is_press; }
    bool getIsTrigger();  //* if is_trigger_ is true, set it to false and return true
    void setIsTrigger(bool is_trigger) { is_trigger_ = is_trigger; }
    Sprite* getSpriteNomal() const { return sprite_nomal_; }
    Sprite* getSpriteHover() const { return sprite_hover_; }
    Sprite* getSpritePress() const { return sprite_press_; }

   protected:
    bool is_hover_ = false;
    bool is_press_ = false;
    bool is_trigger_ = false;

    Sprite* sprite_nomal_ = nullptr;
    Sprite* sprite_hover_ = nullptr;
    Sprite* sprite_press_ = nullptr;
};

#endif  // HUD_BUTTON_H
