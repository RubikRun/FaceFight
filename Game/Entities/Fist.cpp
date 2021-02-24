#include "Fist.h"

namespace FaceFight
{

Fist::Fist(
    sf::Texture const& texture,
    sf::Vector2f const& position)
    : _fist(texture)
{
    Movable::SetPosition(position);
}

void Fist::Draw(
    sf::RenderTarget& renderTarget) const
{
    renderTarget.draw(_fist);
}

void Fist::FollowCenter()
{
    _fist.setPosition({
        Movable::GetPosition().x - _fist.getGlobalBounds().width / 2,
        Movable::GetPosition().y - _fist.getGlobalBounds().height / 2
    });
}

} // namespace FaceFight