#ifndef SCENETITLE_H
#define SCENETITLE_H

#include "Scene.h"

#include <optional>

class HUD_Button;
class HUD_Text;
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

    HUD_Button* button_start_ = nullptr;
    HUD_Button* button_credits_ = nullptr;
    HUD_Button* button_quit_ = nullptr;

    HUD_Text* text_credits_ = nullptr;

   private:
    void renderBackground();
    void updateBoundaryColor(std::optional<float> a = std::nullopt, std::optional<float> b = std::nullopt,
                             std::optional<float> c = std::nullopt,
                             std::optional<float> d = std::nullopt);  //? C++17 feature:optional parameter
    void checkButtonState();
};

#endif  // SCENETITLE_H
