#include "AssetStore.h"

#include <iostream>

void AssetStore::loadImage(const std::string& filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer_, filePath.c_str());
    if (!texture) {
        std::cerr << "Failed to load image: " << filePath << ", " << SDL_GetError() << std::endl;
        return;
    }
    textures_.emplace(filePath, texture);  // if the texture already exists, it will not be replaced
}
void AssetStore::loadFont(const std::string& filePath, float fontSize) {
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << filePath << ", " << SDL_GetError() << std::endl;
        return;
    }
    fonts_.emplace(filePath + std::to_string(fontSize), font);  // if the font already exists, it will not be replaced
}

void AssetStore::loadSound(const std::string& filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (!sound) {
        std::cerr << "Failed to load sound: " << filePath << ", " << SDL_GetError() << std::endl;
        return;
    }
    sounds_.emplace(filePath, sound);  // if the sound already exists, it will not be replaced
}

void AssetStore::loadMusic(const std::string& filePath) {
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << filePath << ", " << SDL_GetError() << std::endl;
        return;
    }
    musics_.emplace(filePath, music);  // if the music already exists, it will not be replaced
}

SDL_Texture* AssetStore::getImage(const std::string& filePath) {
    auto it = textures_.find(filePath);
    if (it == textures_.end()) {  // if the texture is not found, load it
        loadImage(filePath);
        it = textures_.find(filePath);
    }
    if (it == textures_.end()) {  // if the texture is still not found, return nullptr
        std::cerr << "Image not found: " << filePath << std::endl;
        return nullptr;
    }
    return it->second;
}

TTF_Font* AssetStore::getFont(const std::string& filePath, float fontSize) {
    auto it = fonts_.find(filePath + std::to_string(fontSize));
    if (it == fonts_.end()) {
        loadFont(filePath, fontSize);
        it = fonts_.find(filePath + std::to_string(fontSize));
    }
    if (it == fonts_.end()) {
        std::cerr << "Font not found: " << filePath << std::endl;
        return nullptr;
    }
    return it->second;
}

Mix_Chunk* AssetStore::getSound(const std::string& filePath) {
    auto it = sounds_.find(filePath);
    if (it == sounds_.end()) {
        loadSound(filePath);
        it = sounds_.find(filePath);
    }
    if (it == sounds_.end()) {
        std::cerr << "Sound not found: " << filePath << std::endl;
        return nullptr;
    }
    return it->second;
}

Mix_Music* AssetStore::getMusic(const std::string& filePath) {
    auto it = musics_.find(filePath);
    if (it == musics_.end()) {
        loadMusic(filePath);
        it = musics_.find(filePath);
    }
    if (it == musics_.end()) {
        std::cerr << "Music not found: " << filePath << std::endl;
        return nullptr;
    }
    return it->second;
}

void AssetStore::init() {}

void AssetStore::clean() {
    for (auto& texture : textures_) {
        SDL_DestroyTexture(texture.second);
    }
    textures_.clear();
    for (auto& font : fonts_) {
        TTF_CloseFont(font.second);
    }
    fonts_.clear();
    for (auto& sound : sounds_) {
        Mix_FreeChunk(sound.second);
    }
    sounds_.clear();
    for (auto& music : musics_) {
        Mix_FreeMusic(music.second);
    }
    musics_.clear();
}
