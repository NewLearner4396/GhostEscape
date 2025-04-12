#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "Game.h"
#include "defs.h"

class Object {
   public:
    // do not rely constructor and destructor
    // to initialize and clean up the object
    // use init() and clean() instead
    Object() = default;
    virtual ~Object() = default;

    virtual void init() = 0;
    virtual void clean();
    virtual bool handleEvents(SDL_Event& event); //* return true if event is handled and should not be passed to other objects
    virtual void update(float dT);
    virtual void render();

    virtual void addObject(Object* object) { objects_.push_back(object); }
    virtual void removeObject(Object* object) {
        objects_.erase(std::remove(objects_.begin(), objects_.end(), object), objects_.end());
    }
    void safeAddObject(Object* object) {objects_to_add_.push_back(object);}

    ObjectType getObjectType() const { return object_type_; }
    void setObjectType(ObjectType object_type) { object_type_ = object_type; }    
    bool getActive() const {return is_active_;}
    void setActive(bool is_active) { is_active_ = is_active; }
    bool getNeedRemove() const {return need_remove_;}
    void setNeedRemove(bool need_remove) { need_remove_ = need_remove; }

   protected:
    Game& game_ = Game::getInstance();
    std::vector<Object*> objects_;
    std::vector<Object*> objects_to_add_;
    ObjectType object_type_ = ObjectType::NONE;
    bool is_active_ = true;
    bool need_remove_ = false;
};
#endif
