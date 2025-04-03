#ifndef HUD_SKILL_H
#define HUD_SKILL_H

#include "ObjectScreen.h"

class Sprite;
class HUD_Skill : public ObjectScreen {
public:

virtual void render() override; 

static HUD_Skill* addHUDSkill(Object* parent, const std::string& file_name, const glm::vec2& position, float scale = 1.0f, Anchor anchor = Anchor::CENTER);   

//getters and setters
    Sprite* getIcon() const { return icon_; }
    void setIcon(Sprite* icon) { icon_ = icon; }
    float getPercentage() const { return percentage_; }
    void setPercentage(float percentage);

protected:
    Sprite* icon_ = nullptr; // icon of the skill
    float percentage_ = 1.0f; // percentage of the skill    
};

#endif // HUD_SKILL_H
