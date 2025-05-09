#include "Object.h"

bool Object::handleEvents(SDL_Event& event) {
    for (auto& object : objects_) {
        if (object->getActive())
            if (object->handleEvents(event)) // If the event is handled by the object, return true
                return true;
    }
    return false;  // Return false to indicate that the event was not handled
}

void Object::update(float dT) {
    for (auto& object : objects_to_add_) {
        addObject(object);
    }
    objects_to_add_.clear();
    for (auto iter = objects_.begin(); iter != objects_.end();) {
        auto object = *iter;
        if (!object) {  // Check for null pointer
            std::cout << "Warning: Null object found in objects_ list" << std::endl;
            iter = objects_.erase(iter);
            continue;
        }

        if (object->getNeedRemove()) {
            iter = objects_.erase(iter);
            try {
                object->clean();
                delete object;
            } catch (const std::exception& e) {
                std::cout << "Exception during object cleanup: " << e.what() << std::endl;
            }
        } else {
            if (object->getActive()) {
                try {
                    object->update(dT);
                } catch (const std::exception& e) {
                    std::cout << "Exception during object update: " << e.what() << std::endl;
                    // Handle the exception as needed
                    // For example, you might want to set the object to be inactive or remove it
                    object->setNeedRemove(true);
                }
            }
            ++iter;
        }
    }
}

void Object::render() {
    for (auto& object : objects_) {
        if (object->getActive())
            object->render();
    }
}

void Object::clean() {
    for (auto& object : objects_) {
        if (!object)
            continue;  // Check for null pointer
        try {
            object->clean();
            delete object;
        } catch (const std::exception& e) {
            std::cout << "Exception during object cleaning: " << e.what() << std::endl;
        }
    }
    objects_.clear();
}