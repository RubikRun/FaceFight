#pragma once

#include "Resources/ResourceHandler.hpp"
#include "Resources/ResourceIDs.hpp"

#include "Entities/Entity.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace FaceFight
{

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

  private: /* functions */

    /// Updates the game for the next frame.
    void Update();

    /// Draws the game to the window
    void Draw();

    /**
     * Loads and opens all resources needed for the game,
     * using the texture, sound and music handlers
     */
    void LoadOpenResources();

  private: /* variables */

    /// The window where the game is rendered
    sf::RenderWindow _window;

    /// TODO: remove later
    std::unique_ptr<Entity> _player;

    /// Resource handler object for handling texture resources
    ::Resources::ResourceHandler<
        Resources::Texture::Id, sf::Texture> _textureHandler;

    /// Resource handler object for handling sound buffer resources
    ::Resources::ResourceHandler<
        Resources::Sound::Id, sf::SoundBuffer> _soundHandler;

    /// Resource handler object for handling music resources
    ::Resources::ResourceHandler<
        Resources::Music::Id, sf::Music, false> _musicHandler;
};

} // namespace FaceFight