#include "HUD_Skill.h"

#include "Sprite.h"

void HUD_Skill::render() {
    // render the icon with a color mod to make it transparent
    SDL_SetTextureColorModFloat(icon_->getTexture().texture, 0.3f, 0.3f, 0.3f);  // set the color mod of the icon texture
    auto pos = getRenderPosition() + icon_->getOffset();  // get the render position of the icon
    game_.renderTexture(icon_->getTexture(), pos, icon_->getSize());  // render the full  transparent icon texture
    SDL_SetTextureColorModFloat(icon_->getTexture().texture, 1.0f, 1.0f, 1.0f);  // reset the color mod of the icon texture
    // render the icon with the percentage
    ObjectScreen::render();  // call the base class render function
}

HUD_Skill* HUD_Skill::addHUDSkill(Object* parent, const std::string& file_name, const glm::vec2& position, float scale,
                                  Anchor anchor) {
    auto* skill = new HUD_Skill();
    skill->setIcon(Sprite::addSprite(skill, file_name, scale, anchor));
    skill->setRenderPosition(position);
    if (parent)
        parent->safeAddObject(skill);  // add the skill to the parent object
    return skill;
}

void HUD_Skill::setPercentage(float percentage) {
    percentage_ = glm::clamp(percentage, 0.0f, 1.0f);  // clamp the percentage between 0 and 1
    if (icon_)
        icon_->setPercentage(glm::vec2(1.0f, percentage_));
}
