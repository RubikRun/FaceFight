#include "Game.h"

#include "Geometry/Geometry.hpp"

namespace
{

int const FRAMERATE_LIMIT = 60;

sf::Keyboard::Key const KEY_QUIT_GAME = sf::Keyboard::Escape;

std::string const RESOURCES_DIR = "Game/Resources/";

float const ENEMY_SPEED = 5.f;

float const PUNCH_DIST = 350.f;

// Frequency of enemy punches, in frames
int const ENEMY_PUNCH_FREQ = FRAMERATE_LIMIT / 2;

int const WINNER_TEXT_OFFSET = 20.f;

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
        sf::Style::Fullscreen),
    _playerHealthBar(
        sf::Vector2f(100.f, 50.f),
        sf::Vector2f(500.f, 40.f),
        &_player.GetHealth()
    ),
    _enemyHealthBar(
        sf::Vector2f(1320.f, 50.f),
        sf::Vector2f(500.f, 40.f),
        &_enemy.GetHealth()  
    ),
    _mouseLeftIsPressed(false),
    _lastEnemyPunchTimer(ENEMY_PUNCH_FREQ)
{
    // Set frame rate limit to not torture the GPU too much
    _window.setFramerateLimit(FRAMERATE_LIMIT);

    // Enable vertical sync for screens that get screen tearing
    _window.setVerticalSyncEnabled(true);

    // Load and open resources
    LoadOpenResources();

    _player.SetFaceTexture(
        _textureHandler.Get(Texture::Id::Naruto)
    );
    _player.SetFistTexture(
        _textureHandler.Get(Texture::Id::Fist)
    );
    _player.SetFistScale({0.3f, 0.3f});
    _player.SetEnemy(&_enemy);

    _enemy.SetFaceTexture(
        _textureHandler.Get(Texture::Id::Sasuke)
    );
    _enemy.SetFistTexture(
        _textureHandler.Get(Texture::Id::Fist)
    );
    _enemy.SetFistScale({0.3f, 0.3f});
    _enemy.SetPosition({
        (float)_window.getSize().x / 2, (float)_window.getSize().y / 2
    });
    _enemy.SetEnemy(&_player);

    _winnerText.setFont(_fontHandler.Get(Font::Id::Amatic));
    _winnerText.setCharacterSize(100);
    _winnerTextBackground.setFillColor(sf::Color(100, 100, 100, 200));

    _player.SetPunchSoundBuffer(_soundHandler.Get(Sound::Id::Punch));
    _enemy.SetPunchSoundBuffer(_soundHandler.Get(Sound::Id::Punch));

    _musicHandler.Get(Music::Id::NarutoTheme).play();
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
{
    _lastEnemyPunchTimer++;

    /// Indicates whether player and enemy are close enough to punch each other
    bool closeEnough = (Geometry::CalcDist(_player.GetPosition(), _enemy.GetPosition()) <= PUNCH_DIST);

    _player.SetPosition({
        (float)sf::Mouse::getPosition().x,
        (float)sf::Mouse::getPosition().y
    });

    bool playerWasAlive = _player.IsAlive();
    bool enemyWasAlive = _enemy.IsAlive();

    if (_player.IsAlive())
    {
        // button state in previous frame
        bool mouseLeftWasPressed = _mouseLeftIsPressed;
        // button state in current frame
        _mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        // punch enemy only if button was not pressed previously but now is
        if (_mouseLeftIsPressed && !mouseLeftWasPressed)
        {
            _player.PunchEnemy(closeEnough && _enemy.IsAlive());
        }
    }

    if (_enemy.IsAlive() && _player.IsAlive())
    {
        // If enemy is not close enough to punch, it moves towards the player
        if (!closeEnough)
        {
            _enemy.Move(Geometry::NormaliseVector(Geometry::GetVector(
                _enemy.GetPosition(),
                _player.GetPosition()
            )) * ENEMY_SPEED);
        }
        // Otherwise enemy punches, if enough time has passed since last punch
        else if (_lastEnemyPunchTimer >= ENEMY_PUNCH_FREQ)
        {
            // Enemy punches player
            _enemy.PunchEnemy();

            _lastEnemyPunchTimer = 0;
        }
    }

    // If player or enemy died, construct the winner text
    if ((playerWasAlive && !_player.IsAlive())
        || (enemyWasAlive && !_enemy.IsAlive()))
    {
        sf::String winnerString;
        if (playerWasAlive && !_player.IsAlive())
        {
            winnerString = "Game over. You lost.";
        }
        else if (enemyWasAlive && !_enemy.IsAlive())
        {
            winnerString = "Congratulations! You win!";
        }
        _winnerText.setString(winnerString);
        _winnerText.setPosition(sf::Vector2f(
            (float)_window.getSize().x / 2 - _winnerText.getGlobalBounds().width / 2,
            (float)_window.getSize().y / 2 - _winnerText.getGlobalBounds().height / 2
        ));
        _winnerTextBackground.setSize({
            _winnerText.getGlobalBounds().width + WINNER_TEXT_OFFSET * 2,
            _winnerText.getGlobalBounds().height + WINNER_TEXT_OFFSET * 2});
        _winnerTextBackground.setPosition({
            _winnerText.getGlobalBounds().left - WINNER_TEXT_OFFSET,
            _winnerText.getGlobalBounds().top - WINNER_TEXT_OFFSET});
    }

    _player.Update();
    _enemy.Update();
    _playerHealthBar.Update();
    _enemyHealthBar.Update();
}

void Game::Draw()
{
    _enemy.DrawFace(_window);
    _player.DrawFace(_window);
    _enemy.DrawFist(_window);
    _player.DrawFist(_window);

    _playerHealthBar.Draw(_window);
    _enemyHealthBar.Draw(_window);

    _window.draw(_winnerTextBackground);
    _window.draw(_winnerText);
}

void Game::LoadOpenResources()
{
    // Load textures with the texture handler
    _textureHandler.Load(Texture::Id::Naruto, RESOURCES_DIR + "Textures/naruto.png");
    _textureHandler.Load(Texture::Id::Sasuke, RESOURCES_DIR + "Textures/sasuke.png");
    _textureHandler.Load(Texture::Id::Fist, RESOURCES_DIR + "Textures/fist.png");

    // Load sound effects with the sound handler
    _soundHandler.Load(Sound::Id::Punch, RESOURCES_DIR + "Sounds/punch.wav");

    // Open music files with the music handler
    _musicHandler.Open(Music::Id::NarutoTheme, RESOURCES_DIR + "Music/naruto-theme.wav");

    // Load font files with the font handler
    _fontHandler.Load(Font::Id::Amatic, RESOURCES_DIR + "Fonts/raleway.ttf");
}

} // namespace FaceFight