#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <glm/glm.hpp>
#include <iostream>
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

    // getters and setters
    glm::vec2 getWindowSize() const { return window_size_; }
    void getWindow(SDL_Window*& window) const { window = window_; }
    void getRenderer(SDL_Renderer*& renderer) const { renderer = renderer_; }
    Scene* getCurrentScene() const { return currentScene_; }
    AssetStore* getAssetStore() const { return assetStore_; }

    // utility functions
    void drawGrid(glm::vec2& leftTop, glm::vec2& rightBottom, int gridWidth, int gridHeight, SDL_FColor color);
    void drawBoundary(glm::vec2& leftTop, glm::vec2& rightBottom, float width, SDL_FColor color, bool inner = true);
    void renderTexture(Texture& texture, const glm::vec2& position, const glm::vec2& size);
    void renderFilledCircle(const glm::vec2& position, const glm::vec2& size, float alpha);

   private:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    glm::vec2 window_size_ = {800, 600};
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    Scene* currentScene_ = nullptr;
    bool exeRunning = false;
    bool isRunning = false;
    int FPS_ = 60;
    Uint64 frameInterval_ = 0;
    float frameCurrentInterval_ = 0.0f;
    AssetStore* assetStore_ = nullptr;
};
#endif  // GAME_H
