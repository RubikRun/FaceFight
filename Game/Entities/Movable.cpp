#include "Movable.h"

Movable::Movable(
    sf::Vector2f const& position)
    : _center(position)
{}

void Movable::SetPosition(
    sf::Vector2f const& position)
{
    _center = position;
    // Make the whole object "follow" the center to its new position
    FollowCenter();
}

sf::Vector2f Movable::GetPosition() const
{
    return _center;
}

void Movable::Move(
    sf::Vector2f const& delta)
{
    SetPosition(GetPosition() + delta);
}