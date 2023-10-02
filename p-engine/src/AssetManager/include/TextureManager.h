#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Global.h"

// https://free-game-assets.itch.io/pixel-art-tiny-hero-sprite-sheets-pack-2

inline int PLAYER_TEXTURE_ROWS    = 14;
inline int PLAYER_TEXTURE_COLUMNS = 8;

const std::string TEXT_PATH_PLAYER = TEXTURE_DIR + "player/" + "player_spritesheet.png";
const std::string TEXT_PATH_DIRT   = TEXTURE_DIR + "dirt.png";
const std::string TEXT_PATH_WALL   = TEXTURE_DIR + "wall.png";

class TextureManager
{
public:
    static sf::Texture& get_player_texture();
    static sf::Texture& get_dirt_texture();
    static sf::Texture& get_wall_texture();

private:
    static sf::Texture playerText;
    static sf::Texture dirtText;
    static sf::Texture wallText;
};
