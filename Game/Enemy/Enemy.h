#pragma once

#include "../Entity/Entity.h"

#include <SFML/Graphics.hpp>

/**
 * A class representing the enemy entity
 */
class Enemy : public Entity
{
  public:

    /**
     * Creates an enemy entity on the given position
     * 
     * @param[in] position (optional)
     *  position of the upper left corner of the enemy
     */
    Enemy(sf::Vector2f const& position = {0, 0});

    /// The speed by which an enemy entity moves
    static float const SPEED;
};