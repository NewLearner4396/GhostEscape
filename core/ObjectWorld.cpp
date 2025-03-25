#include "ObjectWorld.h"

#include "Scene.h"

void ObjectWorld::update(float dT) {
    ObjectScreen::update(dT);
    // update the render position based on the world position
    render_position_ = game_.getCurrentScene()->positionWorldToScreen(position_);
}
// getters and setters
void ObjectWorld::setPosition(const glm::vec2& position) {
    // set the world position and update the render position
    position_ = position;
    render_position_ = game_.getCurrentScene()->positionWorldToScreen(position);
}

void ObjectWorld::setRenderPosition(const glm::vec2& position) {
    // set the render position and update the world position
    render_position_ = position;
    position_ = game_.getCurrentScene()->positionScreenToWorld(position);
}
