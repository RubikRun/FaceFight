#include "HealthBar.h"

namespace
{

float const OUTLINE_THICKNESS = 2.f;
sf::Color const OUTLINE_COLOR = sf::Color::White;

sf::Color const HEALTH_COLOR = sf::Color(0x269000ff);
sf::Color const LOST_HEALTH_COLOR = sf::Color(0xa50000ff);

} // namespace

HealthBar::HealthBar(
    sf::Vector2f const& position,
    sf::Vector2f const& size,
    int const* health,
    int capacity)
    : _health(health),
    _capacity(capacity),
    _outline(size),
    _healthRect(size),
    _lostHealthRect(size)
{
    /* Fixing the y-component of all 3 rectangles, it will be constant.
       The x-component is what will change and it will change in the Update() function */
    _outline.setPosition(position);
    _healthRect.setPosition(position);
    _lostHealthRect.setPosition(position);

    _outline.setOutlineThickness(OUTLINE_THICKNESS);
    _outline.setOutlineColor(OUTLINE_COLOR);
    _outline.setFillColor(sf::Color(0, 0, 0, 0)); // transparent

    _healthRect.setFillColor(HEALTH_COLOR);
    _lostHealthRect.setFillColor(LOST_HEALTH_COLOR);

    Update();
}

void HealthBar::Draw(
    sf::RenderTarget& target) const
{
    target.draw(_healthRect);
    target.draw(_lostHealthRect);
    target.draw(_outline);
}

void HealthBar::Update()
{
    float healthPercent = (float)*_health / _capacity;
    if (healthPercent < 0)
    {
        healthPercent = 0;
    }
    else if (healthPercent > 1)
    {
        healthPercent = 1;
    }

    float splitPoint = _outline.getSize().x * healthPercent;

    _healthRect.setSize({
        splitPoint,
        _healthRect.getSize().y
    });
    
    _lostHealthRect.setPosition({
        _outline.getPosition().x + splitPoint,
        _lostHealthRect.getPosition().y
    });
    _lostHealthRect.setSize({
        _outline.getSize().x - splitPoint,
        _lostHealthRect.getSize().y
    });
}

int HealthBar::GetCapacity() const
{
    return _capacity;
}

int HealthBar::GetHealth() const
{
    return *_health;
}