#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "registry.h"
#include "sprite.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <utility>

using SpriteID = size_t;

class SpriteManager {
public:
    sf::Texture& registerTexture(const std::string& filepath) {
        auto iter = mTextureIds.find(filepath);
        if (iter == mTextureIds.end()) {
            size_t id = mTextures.emplace();
            iter = mTextureIds.emplace(filepath, id).first;
        }
        return mTextures[iter->second];
    }

    template <typename... Args>
    SpriteID createSprite(Args&&... args) {
        return mSprites.emplace(std::forward<Args>(args)...);
    }

    Sprite& getSprite(SpriteID id) {
        return mSprites[id];
    }

private:
    Registry<sf::Texture> mTextures;
    Registry<Sprite> mSprites;
    std::unordered_map<std::string, size_t> mTextureIds;
};

#endif  // SPRITE_MANAGER_H
