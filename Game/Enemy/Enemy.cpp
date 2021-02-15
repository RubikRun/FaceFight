#include "Enemy.h"

#include <cmath>

namespace
{

auto constexpr TEXTURE_FILE = "Textures/sasuke.png";
auto constexpr FIST_TEXTURE_FILE = "Textures/fist.png";

/// Scaler to scale the texture in the enemy sprite
sf::Vector2f const TEXTURE_SCALE = {1.f, 1.f};

/// Scaler to scale the fist texture in the fist sprite
sf::Vector2f const FIST_TEXTURE_SCALE = {0.3f, 0.3f};

} // namespace

Enemy::Enemy(sf::Vector2f const& position)
    : Entity(
        TEXTURE_FILE,
        FIST_TEXTURE_FILE,
        TEXTURE_SCALE,
        FIST_TEXTURE_SCALE)
{}

float const Enemy::SPEED = 5.f;