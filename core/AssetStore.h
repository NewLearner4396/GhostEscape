#ifndef ASSETSSTORE_H
#define ASSETSSTORE_H
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <unordered_map>  // using unordered_map can speed up the search

class AssetStore {
   public:
    AssetStore(SDL_Renderer* renderer) { renderer_ = renderer; };
    ~AssetStore() = default;
    // Load assets
    void loadImage(const std::string& filePath);
    void loadFont(const std::string& filePath, float fontSize);
    void loadMusic(const std::string& filePath);
    void loadSound(const std::string& filePath);
    // Get assets
    SDL_Texture* getImage(const std::string& filePath);
    TTF_Font* getFont(const std::string& filePath, float fontSize);
    Mix_Chunk* getSound(const std::string& filePath);
    Mix_Music* getMusic(const std::string& filePath);
    void init();
    void clean();

   private:
    SDL_Renderer* renderer_ = nullptr;
    std::unordered_map<std::string, SDL_Texture*> textures_;
    std::unordered_map<std::string, TTF_Font*> fonts_;
    std::unordered_map<std::string, Mix_Chunk*> sounds_;
    std::unordered_map<std::string, Mix_Music*> musics_;
};

#endif