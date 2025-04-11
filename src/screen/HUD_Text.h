#ifndef HUD_TEXT_H
#define HUD_TEXT_H

#include "ObjectScreen.h"

class TextLabel;
class Sprite;
class HUD_Text : public ObjectScreen {
   public:
    virtual void init() override { ObjectScreen::init(); }

    static HUD_Text* addHUDText(Object* parent, const std::string& text, glm::vec2 render_pos, glm::vec2 size,
                                const std::string& file_font = "../assets/font/VonwaonBitmap-16px.ttf",
                                const float font_size = 32,
                                const std::string& bg_path = "../assets/UI/Textfield_01.png",
                                Anchor anchor = Anchor::CENTER);

    void setBgSizeByText(float margin = 10.0f);  // set the background size based on the text size and margin

    // getters and setters
    TextLabel* getTextLabel() const { return text_label_; }
    void setTextLabel(TextLabel* text_label) { this->text_label_ = text_label; }
    Sprite* getSpriteBG() const { return sprite_bg_; }
    void setSpriteBG(Sprite* sprite_bg) { this->sprite_bg_ = sprite_bg; }
    void setSize(const glm::vec2& size);

    std::string getText() const;
    void setText(const std::string& text);
    void setBackground(const std::string& file_path);

   protected:
    TextLabel* text_label_ = nullptr;         // the text label object
    Sprite* sprite_bg_ = nullptr;             // the background sprite object
    glm::vec2 size_ = glm::vec2(0.0f, 0.0f);  // the size of the background sprite
};
#endif  // HUD_TEXT_H
