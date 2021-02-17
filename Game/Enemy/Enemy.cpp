#include "Enemy.h"

#include <cmath>

namespace
{

auto constexpr TEXTURE_FILE = "Textures/sasuke.png";
auto constexpr FIST_TEXTURE_FILE = "Textures/fist.png";
auto constexpr HIT_SOUND_FILE = "Sound/sasuke.wav";

/// Scaler to scale the texture in the enemy sprite
sf::Vector2f const TEXTURE_SCALE = {1.f, 1.f};

/// Scaler to scale the fist texture in the fist sprite
sf::Vector2f const FIST_TEXTURE_SCALE = {0.2f, 0.2f};

sf::Vector2f const HEALTH_BAR_SIZE = {500.f, 40.f};

sf::Vector2f const HEALTH_BAR_POSITION = {1300.f, 50.f};

} // namespace

Enemy::Enemy(sf::Vector2f const& position)
    : Entity(
        TEXTURE_FILE,
        FIST_TEXTURE_FILE,
        HEALTH_BAR_POSITION,
        HEALTH_BAR_SIZE,
        HIT_SOUND_FILE,
        TEXTURE_SCALE,
        FIST_TEXTURE_SCALE)
{}

float const Enemy::SPEED = 5.f;