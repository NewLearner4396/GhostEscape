#include "game.h"

#include "SceneMain.h"
#include "sprite.h"
Game::Game() {
    window_ = nullptr;
    renderer_ = nullptr;
    exeRunning = false;
    isRunning = false;
}

Game::~Game() { clean(); }

void Game::init(const std::string& title, int width, int height) {
    window_size_ = glm::vec2(width, height);
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }
    if (!TTF_Init()) {
        std::cerr << "Failed to initialize SDL_ttf: " << SDL_GetError() << std::endl;
        return;
    }
    if (!Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3)) {
        std::cerr << "Failed to initialize SDL_mixer: " << SDL_GetError() << std::endl;
        return;
    }
    if (!Mix_OpenAudio(0, NULL)) {
        std::cerr << "Failed to open audio: " << SDL_GetError() << std::endl;
        return;
    }
    Mix_AllocateChannels(16);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_Volume(-1, MIX_MAX_VOLUME / 4);
    
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &window_, &renderer_);
    if (!window_ || !renderer_) {
        std::cerr << "Failed to create window or renderer: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_SetRenderLogicalPresentation(renderer_, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    assetStore_ = new AssetStore(renderer_);

    frameInterval_ = 1000000000 / FPS_;
    currentScene_ = new SceneMain();
    currentScene_->init();
    isRunning = true;
    exeRunning = true;
}

void Game::clean() {
    if (currentScene_) {
        currentScene_->clean();
        delete currentScene_;
        currentScene_ = nullptr;
    }
    if (assetStore_) {
        assetStore_->clean();
        delete assetStore_;
        assetStore_ = nullptr;
    }
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }
    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::run() {
    while (exeRunning) {
        while (isRunning) {
            auto start = SDL_GetTicksNS();
            handleEvents();
            update(frameCurrentInterval_);
            render();
            auto end = SDL_GetTicksNS();
            auto runTime = end - start;
            if (runTime < frameInterval_) {
                SDL_DelayNS(frameInterval_ - runTime);
                frameCurrentInterval_ = frameInterval_ / 1.0e9f;
            } else
                frameCurrentInterval_ = runTime / 1.0e9f;
        }
    }
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
            exeRunning = false;
        } else
            currentScene_->handleEvents(event);
    }
}

void Game::update(float dT) {
    if (currentScene_) {
        currentScene_->update(dT);
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    if (currentScene_) {
        currentScene_->render();
    }
    SDL_RenderPresent(renderer_);
}

void Game::drawGrid(glm::vec2& leftTop, glm::vec2& rightBottom, int gridWidth, int gridHeight, SDL_FColor color) {
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
    if (gridWidth <= 0 || gridHeight <= 0) {
        return;
    }
    glm::vec2 leftTop_ = {leftTop.x > 0 ? leftTop.x : 0, leftTop.y > 0 ? leftTop.y : 0};
    glm::vec2 rightBottom_ = {
        rightBottom.x < getCurrentScene()->getCameraSize().x ? rightBottom.x : getCurrentScene()->getCameraSize().x,
        rightBottom.y < getCurrentScene()->getCameraSize().y ? rightBottom.y : getCurrentScene()->getCameraSize().y};
    for (float x = leftTop_.x; x <= rightBottom_.x; x += gridWidth) {
        SDL_RenderLine(renderer_, (x), (leftTop_.y), (x), (rightBottom_.y));
    }
    for (float y = leftTop_.y; y <= rightBottom_.y; y += gridHeight) {
        SDL_RenderLine(renderer_, (leftTop_.x), (y), (rightBottom_.x), (y));
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}

void Game::drawBoundary(glm::vec2& leftTop, glm::vec2& rightBottom, float width, SDL_FColor color, bool inner) {
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
    for (int i = 0; i < width; ++i) {
        SDL_FRect rect{leftTop.x + (2 * inner - 1) * i, leftTop.y + (2 * inner - 1) * i,
                       rightBottom.x - leftTop.x - (2 * inner - 1) * 2 * i,
                       rightBottom.y - leftTop.y - (2 * inner - 1) * 2 * i};
        SDL_RenderRect(renderer_, &rect);
    }
}

void Game::renderTexture(Texture& texture, const glm::vec2& position, const glm::vec2& size) {
    SDL_FRect dstRect{position.x, position.y, size.x, size.y};
    SDL_RenderTextureRotated(renderer_, texture.texture, &texture.srcRect, &dstRect, texture.angle, nullptr,
                      texture.isFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Game::renderFilledCircle(const glm::vec2& position, const glm::vec2& size, float alpha) {
    auto texture = assetStore_->getImage("../assets/UI/circle.png");
    SDL_FRect dstRect{position.x, position.y, size.x, size.y};
    SDL_SetTextureAlphaModFloat(texture, alpha);
    SDL_RenderTexture(renderer_, texture, nullptr, &dstRect);
}
