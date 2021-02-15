#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

/**
 * Abstract class for an entity in the game
 */
class Entity
{

  public:

    /**
     * Creates an entity with the given textrure file and scale
     * on the given position
     * 
     * @param[in] textureFile
     *  name of the file where the texture is located
     * @param[in] fistTextureFile
     *  name of the file where the texture of the fist is located
     * @param[in] scale
     *  the texture will be scaled with this scaler
     * @param[in] fistScale
     *  the texture of the fist will be scaled with this scaler
     * @param[in] position (optional)
     *  position of the center of the entity
     */
    Entity(
        std::string const& textureFile,
        std::string const& fistTextureFile,
        sf::Vector2f const& scale = {1.f, 1.f},
        sf::Vector2f const& fistScale = {1.f, 1.f},
        sf::Vector2f const& position = {0, 0}
    );

    /**
     * Draws the entity on the given render target
     * 
     * @param[in] target
     *  render target where to draw the entity
     */
    void DrawEntity(sf::RenderTarget& target) const;

    /**
     * Draws the entity's fist on the given render target
     * 
     * @param[in] target
     *  render target where to draw the fist
     */
    void DrawFist(sf::RenderTarget& target) const;

    /**
     * Updates entity for next frame
     */
    void Update();

    /**
     * Returns entity's health level
     * 
     * @return health
     */
    int GetHealth() const;

    /**
     * Returns entity's position
     * 
     * @return position of the center of the entity
     */
    sf::Vector2f GetPosition() const;

    /**
     * Sets entity's position
     * 
     * @param[in] position
     *  position to set for the center of the entity
     */
    void SetPosition(sf::Vector2f const& position);

    /**
     * Moves the entity with the given delta vector
     * 
     * @param[in] delta
     *  delta vector by which to move the entity
     */
    void Move(sf::Vector2f const& delta);

    /**
     * Moves the entity towards the given position with the given speed
     * 
     * @param[in] otherPosition
     *  the position towards which we want to move the entity
     * @param[in] speed
     *  the speed with which we want the entity to move
     */
    void MoveTowards(
        sf::Vector2f const& otherPosition,
        float speed
    );

    /**
     * Returns the width of the entity
     * 
     * @return width
     */
    float GetWidth() const;

    /**
     * Returns the height of the entity
     * 
     * @return height
     */
    float GetHeight() const;

    /**
     * Rotates and translates the fist such that it points to the given position
     * 
     * @param[in] otherPosition
     *  the position to which we want the fist to point
     */
    void PointFistTowards(sf::Vector2f const& otherPosition);

    /**
     * Performs a hit towards the given position
     * 
     * @param[in] otherPosition
     *  position towards which to perform the hit
     */
    void Hit(sf::Vector2f const& otherPosition);

    /**
     * Gets hit by another entity
     */
    void GetHit();

  private:

    /// Health of the entity
    int _health;

    /// Texture for the entity
    sf::Texture _tex;

    /// Sprite of the entity where it will be drawn
    sf::Sprite _sprite;

    /// Texture for entity's fist
    sf::Texture _fistTex;

    /// Sprite of the entity's fist where it will be drawn
    sf::Sprite _fistSprite;

    /// Keeps track of whether the fist is currently visible
    bool _fistVisible;

    /// Hit timer, indicating how many more frames are left of the current hit
    int _hitTimer;

    static int const HEALTH_INITIAL = 100;
};