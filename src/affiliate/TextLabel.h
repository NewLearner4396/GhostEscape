#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H
#include "ObjectAffiliate.h"

class TextLabel : public ObjectAffiliate {
   public:
    virtual void render() override;
    virtual void clean() override;
    static TextLabel* addTextLabel(ObjectScreen* parent, const std::string& text, const std::string& font_path,
                                   float font_size = 16, Anchor anchor = Anchor::CENTER);

    // setters and getters
    void setFont(const std::string& font_path, float font_size = 16); //* should be called immediately after init()
    std::string getFontPath() const { return font_path_; }
    void setFontPath(const std::string& font_path);
    float getFontSize() const { return font_size_; }
    void setFontSize(float font_size);
    std::string getText() const { return ttf_text_->text; }
    void setText(const std::string& text); 

   private:
    TTF_Text* ttf_text_;
    std::string font_path_;
    float font_size_ = 16;

    void updateTextSize();  // update the text size based on the font size and text length
};
#endif  // TEXT_LABEL_H
