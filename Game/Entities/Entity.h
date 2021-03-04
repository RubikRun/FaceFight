#pragma once

#include "Animatable.hpp"
#include "Movable.h"

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
class Entity :
    public Movable,
    public Animatable<float>, // for punch animation - distance to fist will be animated
    public Animatable<Entity> // for getting punched animation - the whole entity will be animated
{

  public:

    /**
     * Constructs a default entity with no textures
     */
    Entity();

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
     * Draws the entity's face on the given render target
     * 
     * @param[in] renderTarget
     *  Render target on which to draw the entity's face
     */
    void DrawFace(sf::RenderTarget& renderTarget) const;

    /**
     * Draws the entity's fist on the given render target
     * 
     * @param[in] renderTarget
     *  Render target on which to draw the entity's fist
     */
    void DrawFist(sf::RenderTarget& renderTarget) const;

    /**
     * Updates the entity for the next frame
     */
    void Update();

    /**
     * Sets a texture for entity's face
     * 
     * @param[in] faceTexture
     *  Texture to set for face
     */
    void SetFaceTexture(sf::Texture const& faceTexture);

    /**
     * Sets a texture for entity's fist
     * 
     * @param[in] fistTexture
     *  Texture to set for fist
     */
    void SetFistTexture(sf::Texture const& fistTexture);

    /**
     * Sets scale for the face sprite
     * 
     * @param[in] scale
     *  The amount by which we want to scale the face in the x and y direction
     */
    void SetFaceScale(sf::Vector2f const& scale);

    /**
     * Sets scale for the fist sprite
     * 
     * @param[in] scale
     *  The amount by which we want to scale the fist in the x and y direction
     */
    void SetFistScale(sf::Vector2f const& scale);

    /**
     * Sets the given entity to be this entity's enemy
     * 
     * @param[in] enemy
     *  Pointer to the entity that we want to set as enemy
     */
    void SetEnemy(Entity* const enemy);

    /**
     * Punches the enemy using entity's fist.
     * Plays the punching animation of the fist.
     * If enemy is not close enough, they don't get punched
     * 
     * @param[in] enemyCanGetPunched
     *  Specifies whether the enemy can be punched,
     *  meaning that they are alive and close enough
     */
    void PunchEnemy(bool enemyCanGetPunched = true);

    /**
     * Returns a reference to entity's health points
     */
    int const& GetHealth() const;

    /**
     * Checks if the entity is alive
     */
    bool IsAlive() const;

  public: /* variables */

    static int const MAX_HEALTH = 100;

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

    /**
     * Gets punched by the enemy.
     * Plays the getting punched animation,
     * and decreases health points
     */
    void GetPunched();

    /**
     * Initializes entity's animations
     */
    void InitAnimations();

    /**
     * Constructs the punch action for the punch animation
     * 
     * @return punch action
     */
    Animatable<float>::Action ConstructPunchAction();

    /**
     * Constructs the get punched action for the get punched animation
     * 
     * @return get punched action
     */
    Animatable<Entity>::Action ConstructGetPunchedAction();

  private: /* variables */

    /* Face of the entitiy,
       as an SFML sprite, which points to a texture,
       and keeps track of the entity's position */
    sf::Sprite _face;

    /* Fist of the entitiy,
       as an SFML sprite, which points to a texture,
       and keeps track of the entity's position */
    sf::Sprite _fist;

    /* Distance between the entity and its fist.
       Technically between the centers of the face and the fist. */
    float _fistDist;

    /// Pointer to the enemy entity
    Entity* _enemy;

    /// Health points of the entity
    int _health;
};

} // namespace FaceFight