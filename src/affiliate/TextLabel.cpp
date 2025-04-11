#include "TextLabel.h"

#include "Game.h"

void TextLabel::render() {
    ObjectAffiliate::render();
    auto pos = parent_->getRenderPosition() + offset_;
    TTF_DrawRendererText(ttf_text_, pos.x, pos.y);
}

void TextLabel::clean() {
    ObjectAffiliate::clean();
    if (ttf_text_) {
        TTF_DestroyText(ttf_text_);
        ttf_text_ = nullptr;
    }
}

TextLabel* TextLabel::addTextLabel(ObjectScreen* parent, const std::string& text, const std::string& font_path,
                                   float font_size, Anchor anchor) {
    auto text_label = new TextLabel();
    text_label->init();
    text_label->setFont(font_path, font_size);
    text_label->setText(text);
    text_label->setAnchor(anchor);
    text_label->setOffsetByAnchor(anchor);
    text_label->updateTextSize();
    if (parent) {
        parent->safeAddObject(text_label);
        text_label->setParent(parent);
    }
    return text_label;
}

void TextLabel::setFont(const std::string& font_path, float font_size) {
    font_path_ = font_path;
    font_size_ = font_size;
    // get the font from the asset store and set it to the ttf_text_
    auto font = game_.getAssetStore()->getFont(font_path_, font_size_);
    if (!ttf_text_)
        ttf_text_ = game_.createTTF_Text("", font_path_, font_size_);
    TTF_SetTextFont(ttf_text_, font);
    updateTextSize();
}

void TextLabel::setFontPath(const std::string& font_path) {
    font_path_ = font_path;
    // get the font from the asset store and set it to the ttf_text_
    auto font = game_.getAssetStore()->getFont(font_path_, font_size_);
    TTF_SetTextFont(ttf_text_, font);
    updateTextSize();
}

void TextLabel::setFontSize(float font_size) {
    font_size_ = font_size;
    // get the font from the asset store and set it to the ttf_text_
    auto font = game_.getAssetStore()->getFont(font_path_, font_size_);
    TTF_SetTextFont(ttf_text_, font);
    updateTextSize();
}

void TextLabel::setText(const std::string& text) {
    TTF_SetTextString(ttf_text_, text.c_str(), 0);
    updateTextSize();
}

void TextLabel::updateTextSize() {
    int w, h;
    TTF_GetTextSize(ttf_text_, &w, &h);
    setSize(glm::vec2(w, h));
}
