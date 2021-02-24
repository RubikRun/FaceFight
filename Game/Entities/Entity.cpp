#include "Entity.h"

#include "Fist.h"

#include "../Geometry/Geometry.hpp"

namespace
{

/// Distance between the entity and their fist (their centers)
float const ENTITY_FIST_DIST = 100.f;

} // namespace

namespace FaceFight
{

Entity::Entity(
    sf::Texture const& faceTexture,
    sf::Texture const& fistTexture,
    sf::Vector2f const& position)
    : _face(faceTexture),
    _fist(std::make_unique<Fist>(fistTexture)),
    _enemy(nullptr)
{
    Movable::SetPosition(position);
}

void Entity::Draw(
    sf::RenderTarget& renderTarget) const
{
    renderTarget.draw(_face);
    _fist->Draw(renderTarget);
}

void Entity::SetEnemy(
    Entity* const enemy)
{
    _enemy = enemy;
}

Entity const* Entity::GetEnemy() const
{
    return _enemy;
}

void Entity::Update()
{
    PointFistTowardsEnemy();
}

void Entity::FollowCenter()
{
    _face.setPosition({
        Movable::GetPosition().x - _face.getGlobalBounds().width / 2,
        Movable::GetPosition().y - _face.getGlobalBounds().height / 2
    });
}

void Entity::PointFistTowardsEnemy()
{
    // Get vector from this entity to the enemy entity
    sf::Vector2f enemyUnitVector = Geometry::GetVector(
        this->GetPosition(),
        _enemy->GetPosition()
    );
    // Normalise that vector to get a unit vector
    enemyUnitVector = Geometry::NormaliseVector(enemyUnitVector);

    /* Multiplying the unit vector pointing towards the enemy
       with the distance to the fist that we want,
       would result to a vector from this entity to where the fist is supposed to be,
       to be pointing towards the enemy and be such distance away from this entity */
    sf::Vector2f fistVector = enemyUnitVector * ENTITY_FIST_DIST;

    // What is left is to move the fist there
    _fist->SetPosition(this->GetPosition() + fistVector);
}

} // namespace FaceFight