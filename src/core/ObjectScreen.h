#ifndef OBJECTSCREEN_H
#define OBJECTSCREEN_H
#include "Object.h"

class ObjectScreen : public Object {
   protected:
    glm::vec2 render_position_;

   public:
   virtual void init() override {object_type_ = ObjectType::OBJECT_SCREEN;}
    // getters and setters
    glm::vec2 getRenderPosition() const { return render_position_; }
    virtual void setRenderPosition(const glm::vec2& position) { render_position_ = position; }
    virtual glm::vec2 getPosition() const { return glm::vec2(0); }
};

#endif