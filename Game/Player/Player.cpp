#include "Player.h"

namespace
{

auto constexpr TEXTURE_FILE = "Textures/naruto.png";
auto constexpr FIST_TEXTURE_FILE = "Textures/fist.png";
auto constexpr HIT_SOUND_FILE = "Sound/naruto.wav";

/// Scaler to scale the texture in the player sprite
sf::Vector2f const TEXTURE_SCALE = {1.f, 1.f};

/// Scaler to scale the fist texture in the fist sprite
sf::Vector2f const FIST_TEXTURE_SCALE = {0.2f, 0.2f};

sf::Vector2f const HEALTH_BAR_SIZE = {500.f, 40.f};

sf::Vector2f const HEALTH_BAR_POSITION = {120.f, 50.f};

} // namespace

Player::Player(sf::Vector2f const& position)
    : Entity(
        TEXTURE_FILE,
        FIST_TEXTURE_FILE,
        HEALTH_BAR_POSITION,
        HEALTH_BAR_SIZE,
        HIT_SOUND_FILE,
        TEXTURE_SCALE,
        FIST_TEXTURE_SCALE)
{

}