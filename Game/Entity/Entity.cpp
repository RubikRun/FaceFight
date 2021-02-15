#include "Entity.h"

#include <cmath>

namespace
{

/// Distance between the body (entity sprite) and the fist
float const FIST_BODY_DIST = 100.f;

/// Hit duration in frames
int const HIT_DURATION = 10;

int const HIT_DAMAGE = 5;

} // namespace

Entity::Entity(
    std::string const& textureFile,
    std::string const& fistTextureFile,
    sf::Vector2f const& scale,
    sf::Vector2f const& fistScale,
    sf::Vector2f const& position)
    : _fistVisible(false),
    _hitTimer(0),
    _health(HEALTH_INITIAL)
{
    if (!_tex.loadFromFile(textureFile))
    {
        throw "Error: Cannot load entity texture from file: " + textureFile;
    }
    _sprite.setTexture(_tex);

    _sprite.setScale(scale);

    _sprite.setPosition(position);

    if (!_fistTex.loadFromFile(fistTextureFile))
    {
        throw "Error: Cannot load entity's fist texture from file: " + fistTextureFile;
    }
    _fistSprite.setTexture(_fistTex);

    _fistSprite.setScale(fistScale);
}

void Entity::DrawEntity(sf::RenderTarget& target) const
{
    target.draw(_sprite);
}

void Entity::DrawFist(sf::RenderTarget& target) const
{
    if (_fistVisible)
    {
        target.draw(_fistSprite);
    }
}

void Entity::Update()
{
    if (_hitTimer > 0)
    {
        _hitTimer--;
        if (_hitTimer == 0)
        {
            _fistVisible = false;
        }
    }
}

int Entity::GetHealth() const
{
    return _health;
}

sf::Vector2f Entity::GetPosition() const
{
    return _sprite.getPosition() + sf::Vector2f(GetWidth() / 2, GetHeight() / 2);
}

void Entity::SetPosition(sf::Vector2f const& position)
{
    _sprite.setPosition(position - sf::Vector2f(GetWidth() / 2, GetHeight() / 2));
}

void Entity::Move(sf::Vector2f const& delta)
{
    SetPosition(GetPosition() + delta);
}

void Entity::MoveTowards(
    sf::Vector2f const& otherPos,
    float speed)
{
    // get vector from entity position to the other position
    sf::Vector2f delta = otherPos - Entity::GetPosition();
    /* divide by its own length to get a unit vector,
       and multiply by speed to get a vector with length equal to the speed */
    delta = delta * speed / (float)sqrt(delta.x * delta.x + delta.y * delta.y);

    Move(delta);
}

float Entity::GetWidth() const
{
    return _sprite.getGlobalBounds().width;
}

float Entity::GetHeight() const
{
    return _sprite.getGlobalBounds().height;
}

void Entity::PointFistTowards(sf::Vector2f const& otherPos)
{
    sf::Vector2f delta = otherPos - GetPosition();
    delta *= FIST_BODY_DIST / (float)sqrt(delta.x * delta.x + delta.y * delta.y);

    _fistSprite.setPosition(GetPosition() + delta
        - sf::Vector2f(_fistSprite.getGlobalBounds().width / 2, _fistSprite.getGlobalBounds().height / 2));
}

void Entity::Hit(sf::Vector2f const& otherPos)
{
    // if we are currently hitting, skip
    if (_hitTimer > 0)
    {
        return;
    }

    PointFistTowards(otherPos);

    _fistVisible = true;
    _hitTimer = HIT_DURATION;
}

void Entity::GetHit()
{
    _health -= HIT_DAMAGE;
}