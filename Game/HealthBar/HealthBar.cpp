#include "HealthBar.h"

namespace
{

sf::Color const OUTLINE_COLOR_DEFAULT = sf::Color::White;
sf::Color const HEALTH_COLOR_DEFAULT = sf::Color(0, 153, 51);
sf::Color const LOST_HEALTH_COLOR_DEFAULT = sf::Color(200, 0, 0, 100);

float const OUTLINE_THICKNESS = 2.f;

} // namespace

HealthBar::HealthBar(
    sf::Vector2f const& position,
    sf::Vector2f const& size,
    int initial,
    int capacity)
    : _outline(size),
    _health(initial),
    _capacity(capacity)
{
    _outline.setPosition(position);
    _outline.setOutlineColor(OUTLINE_COLOR_DEFAULT);
    _outline.setOutlineThickness(OUTLINE_THICKNESS);
    _outline.setFillColor(sf::Color(0, 0, 0, 0));

    _healthRect.setPosition(position);
    _healthRect.setFillColor(HEALTH_COLOR_DEFAULT);

    _lostHealthRect.setFillColor(LOST_HEALTH_COLOR_DEFAULT);

    Update();
}

void HealthBar::Draw(sf::RenderTarget& target) const
{
    target.draw(_outline);
    target.draw(_healthRect);
    target.draw(_lostHealthRect);
}

int HealthBar::GetCapacity() const
{
    return _capacity;
}

int HealthBar::GetHealth() const
{
    return _health;
}

void HealthBar::SetHealth(int health)
{
    _health = health;
    Update();
}

void HealthBar::ChangeHealth(int delta)
{
    if (GetHealth() + delta >= 0 && GetHealth() + delta <= _capacity)
    {
        SetHealth(GetHealth() + delta);
    }
}

void HealthBar::Update()
{
    float healthPercent = (float)_health / _capacity;

    _healthRect.setSize({_outline.getSize().x * healthPercent, _outline.getSize().y});

    _lostHealthRect.setSize({_outline.getSize().x * (1 - healthPercent), _outline.getSize().y});
    _lostHealthRect.setPosition({_healthRect.getPosition().x + _healthRect.getSize().x, _outline.getPosition().y});
}