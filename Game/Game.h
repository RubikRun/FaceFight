#pragma once

#include <SFML/Graphics.hpp>

#include "Player/Player.h"
#include "Enemy/Enemy.h"

/**
 * A class for easily creating and running the Game.
 */
class Game
{

  public:

    /**
     * Sets up a new game.
     */
    Game();

    /**
     * Runs the game.
     */
    void Run();

    /**
     * Cleans up after the game has ended.
     */
    ~Game();

  private:

    /// Updates the game for the next frame.
    void Update();

    /// Draws the game to the window
    void Draw();

  private:

    /// The window where the game is rendered
    sf::RenderWindow _window;

    /// Object representing the player entity
    Player _player;

    /// Object representing the enemy entity
    Enemy _enemy;

    /// Indicates whether the left mouse button is currently pressed
    bool _mouseLeftIsPressed;

    /// Timer for how many frames until the enemy can hit the player again
    int _enemyHitTimer;
};