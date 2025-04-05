#include "HUD_Text.h"

#include "Sprite.h"
#include "TextLabel.h"

HUD_Text* HUD_Text::addHUDText(Object* parent, const std::string& text, glm::vec2 render_pos, glm::vec2 size,
                               const std::string& file_font, const float font_size, const std::string& bg_path,
                               Anchor anchor) {
    auto hud_text = new HUD_Text();
    hud_text->init();
    hud_text->setRenderPosition(render_pos);
    hud_text->setSpriteBG(Sprite::addSprite(hud_text, bg_path, 1, anchor));
    hud_text->setSize(size);
    hud_text->setTextLabel(TextLabel::addTextLabel(hud_text, text, file_font, font_size, anchor));
    if (parent)
        parent->safeAddObject(hud_text);
    return hud_text;
}

void HUD_Text::setSize(const glm::vec2& size) {
    size_ = size;
    sprite_bg_->setSize(size_);
}

std::string HUD_Text::getText() const { return text_label_->getText(); }
void HUD_Text::setText(const std::string& text) { text_label_->setText(text); }

void HUD_Text::setBackground(const std::string& file_path) {
    if (sprite_bg_)
        sprite_bg_->setTexture(file_path);
    else
        sprite_bg_ = Sprite::addSprite(this, file_path, 1.0f, Anchor::CENTER);
}
