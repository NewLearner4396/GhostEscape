#ifndef AFFILIATEBAR_H
#define AFFILIATEBAR_H

#include "ObjectAffiliate.h"

class AffiliateBar : public ObjectAffiliate {
    public:
    void render() override;

    static AffiliateBar* addAffiliateBar(Object* parent, glm::vec2 size, Anchor anchor = Anchor::CENTER);

    // getters and setters
    float getBarWidthPercentage() const { return bar_width_percentage_; }
    void setBarWidthPercentage(float bar_width_percentage) { bar_width_percentage_ = bar_width_percentage; }
    
    SDL_FColor getColorHigh() const { return color_high_; }
    void setColorHigh(SDL_FColor color_high) { color_high_ = color_high; }
    SDL_FColor getColorMedium() const { return color_medium_; }
    void setColorMedium(SDL_FColor color_medium) { color_medium_ = color_medium; }
    SDL_FColor getColorLow() const { return color_low_; }
    void setColorLow(SDL_FColor color_low) { color_low_ = color_low; }

    protected:
    float bar_width_percentage_ = 0.0f;
    SDL_FColor color_high_ = {0.0f, 1.0f, 0.0f, 1.0f}; // green
    SDL_FColor color_medium_ = {1.0f, 0.65f, 0.0f, 1.0f}; // orange
    SDL_FColor color_low_ = {1.0f, 0.0f, 0.0f, 1.0f}; // red
};

#endif // AFFILIATEBAR_H
