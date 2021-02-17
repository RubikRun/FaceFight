#include "Entity.h"

#include <cmath>

namespace
{

/// Distance between the body (entity sprite) and the fist
float const FIST_BODY_DIST = 120.f;

/// Hit duration in frames (has to be even)
int const HIT_DURATION = 10;

/// Speed by which the fist is moving when performing a hit
float const HIT_SPEED = 12.f;

/// Get hit duration in frames - the entity turns red for that much frames when they get hit
int const GET_HIT_DURATION = 5;

int const HIT_DAMAGE = 5;

} // namespace

Entity::Entity(
    std::string const& textureFile,
    std::string const& fistTextureFile,
    sf::Vector2f const& healthBarPosition,
    sf::Vector2f const& healthBarSize,
    std::string const& hitSoundFile,
    sf::Vector2f const& scale,
    sf::Vector2f const& fistScale,
    sf::Vector2f const& position)
    : _healthBar(healthBarPosition, healthBarSize),
    _hitTimer(0),
    _getHitTimer(0)
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

    if (!_hitSoundBuffer.loadFromFile(hitSoundFile))
    {
        throw "Error: Cannot load hitting sound from file: " + hitSoundFile;
    }
    _hitSound.setBuffer(_hitSoundBuffer);
}

void Entity::DrawEntity(sf::RenderTarget& target) const
{
    target.draw(_sprite);
}

void Entity::DrawFist(sf::RenderTarget& target) const
{
    target.draw(_fistSprite);
}

void Entity::DrawHealthBar(sf::RenderTarget& target) const
{
    _healthBar.Draw(target);
}

void Entity::Update(sf::Vector2f const& otherPos)
{
    if (_hitTimer > 0)
    {
        if (_hitTimer >= HIT_DURATION / 2)
        {
            _fistSprite.move(_hitVelocity);
        }
        else
        {
            _fistSprite.move(-_hitVelocity);
        }
        _hitTimer--;
    }
    else
    {
        sf::Vector2f delta = otherPos - GetPosition();
        delta *= FIST_BODY_DIST / (float)sqrt(delta.x * delta.x + delta.y * delta.y);
        _fistSprite.setPosition(GetPosition() + delta
            - sf::Vector2f(_fistSprite.getGlobalBounds().width, _fistSprite.getGlobalBounds().height) / 2.f);
    }
    if (_getHitTimer > 0)
    {
        _getHitTimer--;
        if (_getHitTimer == 0)
        {
            _sprite.setColor(sf::Color(255, 255, 255, 255));
        }
    }
}

int Entity::GetHealth() const
{
    return _healthBar.GetHealth();
}

HealthBar const& Entity::GetHealthBar() const
{
    return _healthBar;
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

void Entity::Hit(sf::Vector2f const& otherPos)
{
    // if we are currently hitting, skip
    if (_hitTimer > 0)
    {
        return;
    }

    _hitVelocity = otherPos - GetPosition();
    _hitVelocity *= HIT_SPEED / (float)sqrt(_hitVelocity.x * _hitVelocity.x + _hitVelocity.y * _hitVelocity.y);

    _hitTimer = HIT_DURATION;

    _hitSound.play();
}

void Entity::GetHit()
{
    _healthBar.ChangeHealth(-HIT_DAMAGE);
    _sprite.setColor(sf::Color(250, 0, 0));
    _getHitTimer = GET_HIT_DURATION;
}

bool Entity::IsDead() const
{
    return _healthBar.IsEmpty();
}