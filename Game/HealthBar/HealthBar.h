#pragma once

#include <SFML/Graphics.hpp>

/**
 * A class representing a rectangular health bar,
 * which shows a certain percent of health remaining.
 */
class HealthBar
{
  
  public:

    /**
     * Creates a health bar with the given size on the given position.
     * Optionally capacity and initial health can be specified
     * 
     * @param[in] position
     *  position of the upper left corner of the health bar
     * @param[in] size
     *  size of the health bar - width and height
     * @param[in] capacity
     *  health points capacity of the health bar
     * @param[in] initiail
     *  initial health points in the health bar
     */
    HealthBar(
        sf::Vector2f const& position,
        sf::Vector2f const& size,
        int initial = INITIAL_DEFAULT,
        int capacity = CAPACITY_DEFAULT
    );

    /**
     * Draws the health bar on the given render target
     * 
     * @param[in] target
     *  Render target where we want to draw the health bar
     */
    void Draw(sf::RenderTarget& target) const;

    /**
     * Returns health bar's capacity in health points
     * 
     * @return health bar's capacity
     */
    int GetCapacity() const;

    /**
     * Returns current health points in the health bar
     * 
     * @return current health
     */
    int GetHealth() const;

    /**
     * Sets the health points in the health bar to the given points
     * 
     * @param[in] health
     *  health points to set
     */
    void SetHealth(int health);

    /**
     * Changes health points with the given delta
     * 
     * @param[in] delta
     *  health points (positive/negative) by which to increase/decrease the health
     */
    void ChangeHealth(int delta);

  private: /* functions */

    /**
     * Updates the health and lost healt rectangles,
     * according to the current health points
     */
    void Update();

  private:

    /// Health points currently in the health bar
    int _health;

    /// The amount of health points that the health bar can contain
    int _capacity;

    /// Outline/frame of the health bar
    sf::RectangleShape _outline;

    /// A rectangle of width representing the health points remaining
    sf::RectangleShape _healthRect;

    /// A rectangle of width representing the health points lost
    sf::RectangleShape _lostHealthRect;

    /// The default capacity of the health bar
    static int const CAPACITY_DEFAULT = 100;

    /// The default initial health in a health bar
    static int const INITIAL_DEFAULT = CAPACITY_DEFAULT;
};