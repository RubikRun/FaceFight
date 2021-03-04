#pragma once

#include <SFML/Graphics.hpp>

/**
 * A class representing a rectangular health bar,
 * which keeps track of some health variable,
 * and visualises it as how much health is remaining at any time.
 */
class HealthBar
{

  public:

    /**
     * Creates a health bar with the given size on the given position,
     * that keeps track of the given health variable.
     * Optionally capacity can be specified.
     * 
     * @param[in] position
     *  position of the upper left corner of the health bar
     * @param[in] size
     *  size of the health bar - width and height
     * @param[in] health
     *  pointer to the health variable that will be visualised
     * @param[in] capacity (optional, default = 100)
     *  health points capacity of the health bar
     */
    HealthBar(
        sf::Vector2f const& position,
        sf::Vector2f const& size,
        int const* health,
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
     * Updates the health bar for next frame,
     * according to the current value of the health variable.
     */
    void Update();

    /**
     * Returns health bar's capacity in health points
     * 
     * @return health bar's capacity
     */
    int GetCapacity() const;

    /**
     * Returns the current health in the health bar
     * 
     * @return current health points being visualised in the health bar
     */
    int GetHealth() const;

  private: /* variables */

    /* Pointer to the variable holding the current health points,
       that the health bar is supposed to visualise */
    int const* _health;

    /// Capacity of the health bar - maximum health points it can hold
    int _capacity;

    /// Outline/frame of the health bar
    sf::RectangleShape _outline;

    /// A rectangle with width representing the health remaining
    sf::RectangleShape _healthRect;

    /// A rectangle with width representing the health lost
    sf::RectangleShape _lostHealthRect;

    /// The default capacity of the health bar
    static int const CAPACITY_DEFAULT = 100;
};