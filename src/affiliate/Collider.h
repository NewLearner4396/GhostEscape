#ifndef COLLIDER_H
#define COLLIDER_H

#include "ObjectAffiliate.h"

class Collider : public ObjectAffiliate {
    public:
        enum class ColliderType { 
            CIRCLE, // radius = size_.x / 2, default y = x
            RECTANGLE
        };
        
        void init() override;
        void clean() override;
        void render() override;

        bool isColliding(Collider* other);

        ColliderType getColliderType() {return type_;};
        void setColliderType(ColliderType newType) {type_ = newType;};

        static Collider* addCollider(ObjectScreen* parent, glm::vec2 size, ColliderType type=ColliderType::CIRCLE, Anchor anchor=Anchor::CENTER);

    protected:
     ColliderType type_ = ColliderType::CIRCLE;
};


#endif // COLLIDER_H
