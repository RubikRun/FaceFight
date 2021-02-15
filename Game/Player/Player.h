#pragma once

#include "../Entity/Entity.h"

#include <SFML/Graphics.hpp>

/**
 * A class representing the player entity
 */
class Player : public Entity
{
  public:

    /**
     * Creates a player entity on the given position
     * 
     * @param[in] position (optional)
     *  position of the upper left corner of the player
     */
    Player(sf::Vector2f const& position = {0, 0});
};