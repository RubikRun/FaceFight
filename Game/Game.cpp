#include "Game.h"

namespace
{

int const FRAMERATE_LIMIT = 60;

sf::Keyboard::Key const KEY_QUIT_GAME = sf::Keyboard::Escape;

std::string const RESOURCES_DIR = "Game/Resources/";

} // namespace

namespace FaceFight
{

using namespace Resources;

Game::Game()
    : _window( // Initialize window to be fullscreen
        sf::VideoMode(
            sf::VideoMode::getDesktopMode().width,
            sf::VideoMode::getDesktopMode().height),
        "",
        sf::Style::Fullscreen)
{
    // Set frame rate limit to not torture the GPU too much
    _window.setFramerateLimit(FRAMERATE_LIMIT);

    // Enable vertical sync for screens that get screen tearing
    _window.setVerticalSyncEnabled(true);

    LoadOpenResources();

    _player = std::make_unique<Entity>(
        _textureHandler.Get(Texture::Id::Naruto),
        _textureHandler.Get(Texture::Id::Fist)
    );
}

void Game::Run()
{
    /* The game loop.
       Updating and rendering until the player closes the game */
    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            // If the player has pressed the quit key, we close the window
            if (event.type == sf::Event::KeyPressed
                && event.key.code == KEY_QUIT_GAME)
            {
                _window.close();
            }
        }

        // first clear previous frame
        _window.clear();
        // then update game for the next frame
        Update();
        // then draw the next frame
        Draw();
        // and render it on the window
        _window.display();
    }
}

Game::~Game()
{ /* nothing */ }

void Game::Update()
{ /* nothing */ }

void Game::Draw()
{
    _player->Draw(_window);
}

void Game::LoadOpenResources()
{
    // TODO: Probably move file names to a file in Resources directory
    
    // Load textures with the texture handler
    _textureHandler.Load(Texture::Id::Naruto, RESOURCES_DIR + "Textures/naruto.png");
    _textureHandler.Load(Texture::Id::Sasuke, RESOURCES_DIR + "Textures/sasuke.png");
    _textureHandler.Load(Texture::Id::Fist, RESOURCES_DIR + "Textures/fist.png");

    // Load sound effects with the sound handler
    _soundHandler.Load(Sound::Id::Punch, RESOURCES_DIR + "Sounds/punch.wav");

    // Open music files with the music handler
    _musicHandler.Open(Music::Id::NarutoTheme, RESOURCES_DIR + "Music/naruto-theme.wav");
}

} // namespace FaceFight