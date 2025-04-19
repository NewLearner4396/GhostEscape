#ifndef EFFECT_H
#define EFFECT_H

#include <string>

#include "ObjectWorld.h"
#include "SpriteAnim.h"

class Effect : public ObjectWorld {
   public:
    static Effect* addEffect(Object* parent, const std::string& file_path, glm::vec2 pos, float scale = 1.0f,
                             ObjectWorld* next_object = nullptr);
    virtual void update(float dT) override;
    virtual void clean() override;

   protected:
    SpriteAnim* sprite_ = nullptr;
    ObjectWorld* next_object_ = nullptr;

   private:
    void checkFinish(void);
};

#endif  // EFFECT_H
