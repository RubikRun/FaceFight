#pragma once

#include "Movable.h"
#include "Fist.h"

#include <SFML/Graphics.hpp>

namespace FaceFight
{

/**
 * A class representing an entity in the game.
 * Entities have a face, which is their main visual component,
 * and a fist, which is always pointed towards the enemy entity.
 * Entities also have health points,
 * and can punch their enemy using their fist,
 * which brings down their enemy's health points.
 * 
 * @sidenote: An entity's position is considered to be the center of their face
 */
class Entity : public Movable
{

  public:

    /**
     * Creates an entity with the given texture
     * 
     * @param[in] faceTexture
     *  Texture object to be used to visualise entity's face
     * @param[in] fistTexture
     *  Texture object to be used to visualise entity's fist
     * @param[in] position (optional)
     *  Initial position of the entity
     */
    Entity(
        sf::Texture const& faceTexture,
        sf::Texture const& fistTexture,
        sf::Vector2f const& position = {0.f, 0.f}
    );

    /**
     * Draws the entity on the given render target
     * 
     * @param[in] renderTarget
     *  Render target on which to draw the entity
     */
    void Draw(sf::RenderTarget& renderTarget) const;

    /**
     * Sets the given entity to be this entity's enemy
     * 
     * @param[in] enemy
     *  Pointer to the entity that we want to set as enemy
     */
    void SetEnemy(Entity* const enemy);

    /**
     * Returns a pointer to the enemy entity
     * 
     * @return pointer to enemy
     */
    Entity const* GetEnemy() const;

    /**
     * Updates the entity for the next frame
     */
    void Update();

  private: /* functions */

    /**
     * Describes how the entity should move relative to the center,
     * so that the whole entity can be moved easily through the base class Movable
     */
    void FollowCenter();

    /**
     * Points entity's fist object towards their enemy
     */
    void PointFistTowardsEnemy();

  private: /* variables */

    /* Face of the entitiy,
       as an SFML sprite, which points to a texture,
       and keeps track of the entity's position */
    sf::Sprite _face;

    /* Entity's fist, as a unique pointer,
       because the entity should be the only owner of their fist */
    std::unique_ptr<Fist> _fist;

    /// Pointer to the enemy entity
    Entity* _enemy;
};

} // namespace FaceFight