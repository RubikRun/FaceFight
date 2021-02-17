#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../HealthBar/HealthBar.h"

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
     * @param[in] healthBarPosition
     *  position of the upper left corner of entity's health bar
     * @param[in] healthBarSize
     *  size (width and height) of entity's health bar
     * @param[in] hitSoundFile
     *  name of the file where the sound of hitting is located
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
        sf::Vector2f const& healthBarPosition,
        sf::Vector2f const& healthBarSize,
        std::string const& hitSoundFile,
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
     * Draws the health bar of the entity
     */
    void DrawHealthBar(sf::RenderTarget& target) const;

    /**
     * Updates entity for next frame
     * 
     * @param[in] otherPosition
     *  position of the other entity
     */
    void Update(sf::Vector2f const& otherPosition);

    /**
     * Returns entity's health points
     * 
     * @return health
     */
    int GetHealth() const;

    /**
     * Returns a const reference to entit's health bar
     * 
     * @return entity's health bar
     */
    HealthBar const& GetHealthBar() const;

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

    /**
     * Checks whether the entity is dead (has 0 health)
     * 
     * @return true for dead, false otherwise
     */
    bool IsDead() const;

  private:

    /// Health bar of the entity
    HealthBar _healthBar;

    /// Texture for the entity
    sf::Texture _tex;

    /// Sprite of the entity where it will be drawn
    sf::Sprite _sprite;

    /// Sound buffer for the sound of hitting
    sf::SoundBuffer _hitSoundBuffer;

    /// Sound object for the sound of hitting
    sf::Sound _hitSound;

    /// Texture for entity's fist
    sf::Texture _fistTex;

    /// Sprite of the entity's fist where it will be drawn
    sf::Sprite _fistSprite;

    /// Hit timer, indicating how many more frames are left of the current hit
    int _hitTimer;

    /// Velocity of the movement of the fist while hitting
    sf::Vector2f _hitVelocity;

    /// Get hit timer, indicating frames left of the getting hit
    int _getHitTimer;

    static int const HEALTH_INITIAL = 100;
};