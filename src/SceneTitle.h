#ifndef SCENETITLE_H
#define SCENETITLE_H

#include "Scene.h"

#include <optional>

class SceneTitle : public Scene {
   public:
    SceneTitle() = default;
    ~SceneTitle() = default;

    void init() override;
    void clean() override;
    void handleEvents(SDL_Event& event) override;
    void update(float dT) override;
    void render() override;

   protected:
    SDL_FColor boundary_color_ = {0.5f, 0.5f, 0.5f, 1.0f};
    float color_timer = 0.0f;

   private:
    void renderBackground();
    void updateBoundaryColor(std::optional<float> a = std::nullopt, std::optional<float> b = std::nullopt,
                             std::optional<float> c = std::nullopt,
                             std::optional<float> d = std::nullopt);  //? C++17 feature:optional parameter
};

#endif  // SCENETITLE_H
