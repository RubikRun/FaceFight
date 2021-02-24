#pragma once

#include "Movable.h"

namespace FaceFight
{

/* Forward-declaring class Entity,
   so that we can use an Entity pointer to the fist's owner,
   without creating recursive infinity of includes,
   because an entity also has a pointer to its fist */
class Entity;

/**
 * A class representing an entity's fist.
 * Fists have textures for visualisation,
 * and are updated each frame to point to their owner's enemy.
 * Also they can visually perform a punch, when their owner punches the enemy.
 * 
 * @sidenote: A fist's position is considered to be the center.
 */
class Fist : public Movable
{

  public:
    
    /**
     * Creates a fist with the given texture
     * 
     * @param[in] texture
     *  Texture object to be used to visualise the fist
     * @param[in] position (optional)
     *  Initial position of the fist
     */
    Fist(
        sf::Texture const& texture,
        sf::Vector2f const& position = {0.f, 0.f}
    );

    /**
     * Draws the fist on the given render target
     * 
     * @param[in] renderTarget
     *  Render target on which to draw the fist
     */
    void Draw(sf::RenderTarget& renderTarget) const;

  private: /* functions */

    /**
     * Describes how the fist should move relative to the center,
     * so that the whole fist can be moved easily through the base class Movable
     */
    void FollowCenter();

  private: /* variables */
    
    /* Fist itself,
       as an SFML sprite, which points to a texture,
       and keeps track of the fist's position */
    sf::Sprite _fist;

    /* Pointer to the fist's owner, the Entity object whose fist this is.
       It is not a unique pointer, because we might want entities
       to be able to change/remove their fists.
       When a fist is destroyed, we don't want its owner to be destroyed,
       but when an entity is destroyed, we surely want their fist to be destroyed as well */
    Entity* _owner;
};

} // namespace FaceFight