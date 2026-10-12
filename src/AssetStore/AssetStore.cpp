#include "./AssetStore.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL_image.h>

AssetStore::AssetStore() {
    Logger::Log("AssetStore constructor called!");
}

AssetStore::~AssetStore() {
    ClearAssets();
    Logger::Log("AssetStore destructor called!");
}

void AssetStore::ClearAssets() {
    for (auto texture: textures) {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();

    for (auto font: fonts) {
        TTF_CloseFont(font.second);
    }
    fonts.clear();
}

void AssetStore::AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        Logger::Err("Failed to load image '" + filePath + "': " + IMG_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); //freed on EVERY path from here on
    if (!texture) {
        Logger::Err("Failed to create texture '" + assetId + "': " + SDL_GetError());
        return;
    }

    auto it = textures.find(assetId);
    if (it != textures.end()) {                   
        SDL_DestroyTexture(it->second);//free the OLD texture
        it->second = texture;//store the new one in its place
        Logger::Log("Texture replaced in the AssetStore with id " + assetId);
        return;
    }

    textures.emplace(assetId, texture);
    Logger::Log("Texture added to the AssetStore with id " + assetId);
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId) {
    auto it = textures.find(assetId);             
    if (it == textures.end()) {
        Logger::Err("Texture not found: " + assetId);//log FIRST
        return nullptr;
    }
    return it->second;
}

void AssetStore::AddFont(const std::string& assetId, const std::string& filePath, int fontSize) {
    fonts.emplace(assetId, TTF_OpenFont(filePath.c_str(), fontSize));
}

TTF_Font* AssetStore::GetFont(const std::string& assetId) {
    return fonts[assetId];
}
