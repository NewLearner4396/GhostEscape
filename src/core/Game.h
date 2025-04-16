#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <glm/glm.hpp>
#include <iostream>
#include <random>
#include <string>

#include "AssetStore.h"

struct Texture;
class Scene;
class Game {
   public:
    static Game& getInstance() {
        static Game gameInstance;
        return gameInstance;
    }
    ~Game();
    void init(const std::string& title, int width, int height);  // initialize the game
    void clean();                                                // clean up the game resources
    void run();                                                  // run the game loop
    void handleEvents();                                         // handle events
    void update(float dT);                                       // update the game state
    void render();                                               // render the game

    void safeChangeScene(Scene* scene) { nextScene_ = scene; }
    void changeScene();  //* do not call this function directly, use safeChangeScene instead
    void quit() {
        isRunning_ = false;
        exeRunning_ = false;
    }

    // getters and setters
    glm::vec2 getWindowSize() const { return window_size_; }
    void getWindow(SDL_Window*& window) const { window = window_; }
    void getRenderer(SDL_Renderer*& renderer) const { renderer = renderer_; }
    Scene* getCurrentScene() const { return currentScene_; }
    void setCurrentScene(Scene* scene) { currentScene_ = scene; }
    AssetStore* getAssetStore() const { return assetStore_; }
    glm::vec2 getMousePosition() const { return mouse_position_; }
    void setMousePosition(const glm::vec2& position) { mouse_position_ = position; }
    SDL_MouseButtonFlags getMouseButton() const { return mouse_button_; }
    void setMouseButton(SDL_MouseButtonFlags button) { mouse_button_ = button; }
    float getScore() const { return score_; }
    void setScore(float score) {
        score_ = score;
        high_score_ = std::max(high_score_, score_);
    }
    float getHighScore() const { return high_score_; }
    void setHighScore(float high_score) { high_score_ = high_score; }

    //* utility functions
    //* random functions
    float randomFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(gen_); }
    int randomInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(gen_); }
    glm::vec2 randomVec2(const glm::vec2& min, const glm::vec2& max) {
        return {randomFloat(min.x, max.x), randomFloat(min.y, max.y)};
    }
    glm::ivec2 randomIVec2(const glm::ivec2& min, const glm::ivec2& max) {
        return {randomInt(min.x, max.x), randomInt(min.y, max.y)};
    }
    //* draw functions
    void drawGrid(const glm::vec2& leftTop, const glm::vec2& rightBottom, int gridWidth, int gridHeight,
                  SDL_FColor color);
    void drawBoundary(const glm::vec2& leftTop, const glm::vec2& rightBottom, float width, SDL_FColor color,
                      bool inner = true);
    void drawPoints(const std::vector<glm::vec2>& points, glm::vec2 render_pos, SDL_FColor color);
    //* render functions
    void renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size,
                       const glm::vec2& mask = {1.0f, 1.0f});
    void renderFilledCircle(const glm::vec2& position, const glm::vec2& size, float alpha);
    void renderHBar(const glm::vec2& position, const glm::vec2& size, float percentage, SDL_FColor color);
    TTF_Text* createTTF_Text(const std::string& text, const std::string& font_path, float font_size = 16);
    //* music functions
    void playMusic(const std::string& music_path, bool loops = true) {
        Mix_PlayMusic(assetStore_->getMusic(music_path), loops ? -1 : 0);
    }
    void pauseMusic() { Mix_PauseMusic(); }
    void resumeMusic() { Mix_ResumeMusic(); }
    void stopMusic() { Mix_HaltMusic(); }
    // every sound will be operated simultaneously
    void playSound(const std::string& sound_path) { Mix_PlayChannel(-1, assetStore_->getSound(sound_path), 0); }
    void pauseSound() { Mix_Pause(-1); }
    void resumeSound() { Mix_Resume(-1); }
    void stopSound() { Mix_HaltChannel(-1); }
    //* check functions
    bool isMouseInRect(const glm::vec2& leftTop, const glm::vec2& rightBottom) const {
        return mouse_position_.x >= leftTop.x && mouse_position_.x <= rightBottom.x && mouse_position_.y >= leftTop.y &&
               mouse_position_.y <= rightBottom.y;
    }
    //* file functions
    std::string loadTextFile(const std::string& file_path);

   private:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    glm::vec2 window_size_ = {800, 600};
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    TTF_TextEngine* ttf_engine_ = nullptr;
    glm::vec2 mouse_position_ = {0, 0};
    SDL_MouseButtonFlags mouse_button_ = 0;
    Scene* currentScene_ = nullptr;
    Scene* nextScene_ = nullptr;
    bool exeRunning_ = false;
    bool isRunning_ = false;
    int FPS_ = 60;
    Uint64 frameInterval_ = 0;
    float frameCurrentInterval_ = 0.0f;
    AssetStore* assetStore_ = nullptr;
    std::mt19937 gen_ = std::mt19937(std::random_device{}());  // random number generator

    float score_ = 0.0f;       // score of the game
    float high_score_ = 0.0f;  // high score of the game
};
#endif  // GAME_H
