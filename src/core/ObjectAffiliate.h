#ifndef OBJECT_AFFILIATE_H
#define OBJECT_AFFILIATE_H

#include "ObjectScreen.h"

class ObjectAffiliate : public Object {
   protected:
    ObjectScreen* parent_ = nullptr;     // the object that this object is affiliated with
    glm::vec2 offset_ = glm::vec2(0.0f, 0.0f);  // the offset from the parent object
    glm::vec2 size_ = glm::vec2(0.0f, 0.0f);    // the size of the object
    Anchor anchor_ = Anchor::CENTER;              // the anchor point of the object used to move the object

   public:
    // getters and setters
    glm::vec2 getOffset() const { return offset_; }
    void setOffset(const glm::vec2& offset) { this->offset_ = offset; }
    glm::vec2 getSize() const { return size_; }
    void setSize(const glm::vec2& size) { this->size_ = size; setOffsetByAnchor(anchor_); } // set size and set offset by anchor
    void setScale(float scale) { size_ *= scale; setOffsetByAnchor(anchor_); }
    ObjectScreen* getParent() const { return parent_; }
    void setParent(ObjectScreen* object_parent) { this->parent_ = object_parent; }
    Anchor getAnchor() const { return anchor_; }
    void setAnchor(Anchor anchor) { this->anchor_ = anchor; }
    void setOffsetByAnchor(const Anchor anchor);

    virtual void init() override { object_type_ = ObjectType::OBJECT_SCREEN; }
    // virtual void update(float dT) override;
};

#endif  // OBJECT_AFFILIATE_H
