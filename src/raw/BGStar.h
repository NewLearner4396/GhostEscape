#ifndef BGSTAR_H
#define BGSTAR_H

#include "Object.h"
class BGStar : public Object {
   public:
    void init() { object_type_ = ObjectType::NONE; }
    void update(float dT) override;
    void render() override;

    static BGStar* addBGStar(Object* parent, float num, float scale_far, float scale_mid, float scale_near);

   protected:
    std::vector<glm::vec2> stars_far_;
    std::vector<glm::vec2> stars_mid_;
    std::vector<glm::vec2> stars_near_;
    float scale_far_ = 0.2f;
    float scale_mid_ = 0.5f;
    float scale_near_ = 0.7f;
    SDL_FColor color_far_ = {0.0, 0.0, 0.0, 1};
    SDL_FColor color_mid_ = {0.0, 0.0, 0.0, 1};
    SDL_FColor color_near_ = {0.0, 0.0, 0.0, 1};
    float timer_ = 0.0;
    float num_ = 2200;  // stars number of each layer
};
#endif  // BGSTAR_H
