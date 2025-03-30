#include "Scene.h"

void Scene::clean() {
    Object::clean();
    for (auto& object : objects_world_) {
        object->clean();
        delete object;
    }
    objects_world_.clear();
    for (auto& object : objects_screen_) {
        object->clean();
        delete object;
    }
    objects_screen_.clear();
}

void Scene::handleEvents(SDL_Event& event) {
    Object::handleEvents(event);
    for (auto& object : objects_screen_) {
        if (object && object->getActive())
            object->handleEvents(event);
    }
    for (auto& object : objects_world_) {
        if (object && object->getActive())
            object->handleEvents(event);
    }
}

void Scene::update(float dT) {
    Object::update(dT);
    for (auto iter = objects_world_.begin(); iter != objects_world_.end();) {
        auto object = *iter;
        if (object->getNeedRemove()) {
            iter = objects_world_.erase(iter);
            object->clean();
            delete object;
        } else {
            if (object->getActive())
                object->update(dT);
            ++iter;
        }
    }
    for (auto iter = objects_screen_.begin(); iter != objects_screen_.end();) {
        auto object = *iter;
        if (object->getNeedRemove()) {
            iter = objects_screen_.erase(iter);
            object->clean();
            delete object;
        } else {
            if (object->getActive())
                object->update(dT);
            ++iter;
        }
    }
}

void Scene::render() {
    Object::render();
    for (auto& object : objects_world_) {
        if (object->getActive())
            object->render();
    }
    for (auto& object : objects_screen_) {
        if (object->getActive())
            object->render();
    }
}

void Scene::addObject(Object* object) {
    switch (object->getObjectType()) {
        case ObjectType::OBJECT_WORLD:
        case ObjectType::ENEMY:
            objects_world_.push_back(
                dynamic_cast<ObjectWorld*>(object));  // dynamic_cast is used to safely cast for derived classes
            break;
        case ObjectType::OBJECT_SCREEN:
            objects_screen_.push_back(dynamic_cast<ObjectScreen*>(object));
            break;
        default:
            objects_.push_back(object); 
            break;
    }
}

void Scene::removeObject(Object* object) {
    switch (object->getObjectType()) {
        case ObjectType::OBJECT_WORLD:
        case ObjectType::ENEMY:
            objects_world_.erase(
                std::remove(objects_world_.begin(), objects_world_.end(), static_cast<ObjectWorld*>(object)),
                objects_world_.end());
            break;
        case ObjectType::OBJECT_SCREEN:
            objects_screen_.erase(
                std::remove(objects_screen_.begin(), objects_screen_.end(), static_cast<ObjectScreen*>(object)),
                objects_screen_.end());
            break;
        default:
            break;
    }
}

void Scene::setCameraPosition(const glm::vec2& camera_position) {
    camera_position_ = camera_position;
    camera_position_ = glm::clamp(camera_position_, -glm::vec2(30), world_size_ - camera_size_ + glm::vec2(30));
}