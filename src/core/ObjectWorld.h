#ifndef OBJECTWORLD_H
#define OBJECTWORLD_H
#include "Collider.h"
#include "ObjectScreen.h"

class ObjectWorld : public ObjectScreen {
   public:
    virtual void init() override { object_type_ = ObjectType::OBJECT_WORLD; }
    virtual void update(float dT) override;
    // getters and setters
    glm::vec2 getRenderPosition() const { return render_position_; }
    virtual void setRenderPosition(const glm::vec2& position) override;
    virtual glm::vec2 getPosition() const override { return position_; }
    void setPosition(const glm::vec2& position);
    Collider* getCollider() const { return collider_; }
    void setCollider(Collider* new_) { collider_ = new_; }

   protected:
    glm::vec2 position_;  // world position
    Collider* collider_ = nullptr;
};
#endif  // OBJECTWORLD_H
