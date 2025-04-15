#ifndef SCENE_H
#define SCENE_H
#include <glm/glm.hpp>
#include <vector>

#include "Object.h"
#include "ObjectWorld.h"

class Scene : public Object {
   public:
    virtual void init() override { object_type_ = ObjectType::OBJECT_SCREEN; };
    virtual void clean() override;
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dT) override;
    virtual void render() override;

    virtual void addObject(Object* object) override;
    virtual void removeObject(Object* object) override;

    virtual void saveData(const std::string&) {}
    virtual void loadData(const std::string&) {}

    bool getIsPaused() const { return is_paused_; }
    void setIsPaused(bool is_paused) { is_paused_ = is_paused; }
    glm::vec2 getWorldSize() const { return world_size_; }
    void setWorldSize(const glm::vec2& world_size) { world_size_ = world_size; }
    glm::vec2 positionWorldToScreen(const glm::vec2& world_position) const { return world_position - camera_position_; }
    glm::vec2 positionScreenToWorld(const glm::vec2& screen_position) const {
        return screen_position + camera_position_;
    }
    glm::vec2 getCameraPosition() const { return camera_position_; }
    void setCameraPosition(const glm::vec2& camera_position);
    glm::vec2 getCameraSize() const { return camera_size_; }
    std::vector<ObjectWorld*>& getObjectsWorld() { return objects_world_; }
    std::vector<ObjectScreen*>& getObjectsScreen() { return objects_screen_; }

    void pause() {
        is_paused_ = true;
        game_.pauseSound();
    }
    void resume() {
        is_paused_ = false;
        game_.resumeSound();
    }

   protected:
    bool is_paused_ = false;
    glm::vec2 world_size_;
    glm::vec2 camera_position_ = glm::vec2(0.0f, 0.0f);
    glm::vec2 camera_size_ = glm::vec2(800.0f, 600.0f);
    std::vector<ObjectWorld*> objects_world_;
    std::vector<ObjectScreen*> objects_screen_;
};

#endif