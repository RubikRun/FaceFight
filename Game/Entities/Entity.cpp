#include "Entity.h"

#include "../Geometry/Geometry.hpp"

namespace
{

/// Distance to fist by default
float const FIST_DIST_DEFAULT = 100.f;
/// Distance to fist that is reached when punching the enemy
float const FIST_DIST_PUNCH = 150.f;

size_t const PUNCH_ANIMATION_DURATION = 15;

size_t const GET_PUNCHED_ANIMATION_DURATION = 10;

float PUNCH_POWER = 5.f;

int PUNCH_SOUND_VOLUME = 35;

} // namespace

namespace FaceFight
{

Entity::Entity()
    : _fistDist(FIST_DIST_DEFAULT),
    _enemy(nullptr),
    _health(MAX_HEALTH)
{
    InitAnimations();
}

Entity::Entity(
    sf::Texture const& faceTexture,
    sf::Texture const& fistTexture,
    sf::Vector2f const& position)
    : _face(faceTexture),
    _fist(fistTexture),
    _fistDist(FIST_DIST_DEFAULT),
    _enemy(nullptr),
    _health(MAX_HEALTH)
{
    Movable::SetPosition(position);
    InitAnimations();
}

void Entity::DrawFace(
    sf::RenderTarget& renderTarget) const
{
    renderTarget.draw(_face);
    renderTarget.draw(_fist);
}

void Entity::DrawFist(
    sf::RenderTarget& renderTarget) const
{
    renderTarget.draw(_fist);
}

void Entity::Update()
{
    Animatable<float>::UpdateAnimation();
    Animatable<Entity>::UpdateAnimation();
    PointFistTowardsEnemy();
}

void Entity::SetFaceTexture(sf::Texture const& faceTexture)
{
    _face.setTexture(faceTexture);
}

void Entity::SetFistTexture(sf::Texture const& fistTexture)
{
    _fist.setTexture(fistTexture);
}

void Entity::SetFaceScale(sf::Vector2f const& scale)
{
    _face.setScale(scale);
}

void Entity::SetFistScale(sf::Vector2f const& scale)
{
    _fist.setScale(scale);
}

void Entity::SetEnemy(
    Entity* const enemy)
{
    _enemy = enemy;
}

void Entity::SetPunchSoundBuffer(sf::SoundBuffer& punchSoundBuffer)
{
    _punchSound.setBuffer(punchSoundBuffer);
    _punchSound.setVolume(PUNCH_SOUND_VOLUME);
}

void Entity::PunchEnemy(bool enemyCanGetPunched)
{
    Animatable<float>::GetAction("punch").Play();
    _punchSound.play();
    if (enemyCanGetPunched)
    {
        _enemy->GetPunched();
    }
}

int const& Entity::GetHealth() const
{
    return _health;
}

bool Entity::IsAlive() const
{
    return (_health > 0);
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
    // If there is no enemy, just point fist to the right
    if (_enemy == nullptr || !IsAlive())
    {
        _fist.setPosition(this->GetPosition() + sf::Vector2f(_fistDist, 0.f)
            - sf::Vector2f(_fist.getGlobalBounds().width / 2.f, _fist.getGlobalBounds().height / 2.f));
        return;
    }

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
    sf::Vector2f fistVector = enemyUnitVector * _fistDist;

    // What is left is to move the fist there
    _fist.setPosition(this->GetPosition() + fistVector
        - sf::Vector2f(_fist.getGlobalBounds().width / 2.f, _fist.getGlobalBounds().height / 2.f));
}

void Entity::GetPunched()
{
    Animatable<Entity>::GetAction("get-punched").Play();
    _health -= PUNCH_POWER;
}

void Entity::InitAnimations()
{
    // Add punching action to the animation
    Animatable<float>::AddAction(
        "punch",
        ConstructPunchAction()
    );

    // Add getting punched action to the animation
    Animatable<Entity>::AddAction(
        "get-punched",
        ConstructGetPunchedAction()
    );
}

Animatable<float>::Action Entity::ConstructPunchAction()
{
    return {
        &_fistDist,
        [](float* fistDist, float instance) {
            if (instance < 0.5f)
            {
                *fistDist = FIST_DIST_DEFAULT
                    + 2 * instance * (FIST_DIST_PUNCH - FIST_DIST_DEFAULT);
            }
            else
            {
                *fistDist = FIST_DIST_DEFAULT
                    + 2 * (1 - instance) * (FIST_DIST_PUNCH - FIST_DIST_DEFAULT);
            }
        },
        PUNCH_ANIMATION_DURATION
    };
}

Animatable<Entity>::Action Entity::ConstructGetPunchedAction()
{
    return {
        this,
        [](Entity* entity, float instance) {
            if (instance <= 0.0001f)
            {
                entity->_face.setColor(sf::Color::Red);
            }
            if (instance >= 0.9999f)
            {
                entity->_face.setColor(sf::Color::White);
            }

            // Unit vector from enemy to this entity
            sf::Vector2f fromEnemyUnitVector = Geometry::NormaliseVector(
                Geometry::GetVector(
                    entity->_enemy->GetPosition(),
                    entity->GetPosition()
                )
            );

            if ((int)(instance * 20) % 2 == 0)
            {
                entity->Move(fromEnemyUnitVector * PUNCH_POWER);
            }
            else
            {
                entity->Move(-fromEnemyUnitVector * PUNCH_POWER);
            }
        },
        GET_PUNCHED_ANIMATION_DURATION
    };
}

} // namespace FaceFight