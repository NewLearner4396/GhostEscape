#include "Collider.h"

void Collider::init() {}

void Collider::clean() {
    ObjectAffiliate::clean();
}

void Collider::render() {
    ObjectAffiliate::render();
#ifdef DEBUG_MODE
    auto pos = parent_->getRenderPosition() + offset_;
    game_.renderFilledCircle(pos, size_, 0.3f);
#endif
}

bool Collider::isColliding(Collider* other) {
    if (!other) {
        std::cout << "Collision check failed: other is null" << std::endl;
        return false;
    }
    
    if (!parent_) {
        std::cout << "Collision check failed: this.parent_ is null" << std::endl;
        return false;
    }
    
    if (!other->getParent()) {
        std::cout << "Collision check failed: other.parent is null" << std::endl;
        return false;
    }
    // two circle
    if (type_ == ColliderType::CIRCLE && other->getColliderType() == ColliderType::CIRCLE) {
        auto point1 = parent_->getPosition() + offset_ + size_ / 2.0f;
        auto point2 = other->getParent()->getPosition() + other->getOffset() + other->getSize() / 2.0f;
        return glm::length(point1 - point2) < (size_.x + other->getSize().x) / 2.0f;
    }
    return false;
    // TODO:: other condition
}

Collider* Collider::addCollider(ObjectScreen* parent, glm::vec2 size, ColliderType type, Anchor anchor) {
    if (!parent) {
        std::cout << "Error: Cannot add collider to null parent" << std::endl;
        return nullptr;
    }
    auto collider = new Collider();
    collider->init();
    collider->setAnchor(anchor);
    collider->setSize(size);
    collider->setColliderType(type);
    collider->setParent(parent);
    parent->addObject(collider);
    return collider;
}
