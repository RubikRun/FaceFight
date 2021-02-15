#include "Player.h"

namespace
{

auto constexpr TEXTURE_FILE = "Textures/naruto.png";
auto constexpr FIST_TEXTURE_FILE = "Textures/fist.png";

/// Scaler to scale the texture in the player sprite
sf::Vector2f const TEXTURE_SCALE = {1.f, 1.f};

/// Scaler to scale the fist texture in the fist sprite
sf::Vector2f const FIST_TEXTURE_SCALE = {0.3f, 0.3f};

} // namespace

Player::Player(sf::Vector2f const& position)
    : Entity(
        TEXTURE_FILE,
        FIST_TEXTURE_FILE,
        TEXTURE_SCALE,
        FIST_TEXTURE_SCALE)
{

}