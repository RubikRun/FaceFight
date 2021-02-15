#include "Game.h"

#include <iostream>

namespace
{

int const SCREEN_WIDTH = 1920;
int const SCREEN_HEIGHT = 1080;

int const FRAMERATE_LIMIT = 60;

sf::Keyboard::Key const KEY_QUIT_GAME = sf::Keyboard::Escape;

/* Enemy is considered to have reached the player,
   if the distance between them is <= this constant. */
float const ENEMY_REACH_PLAYER_DIST = 150.f;

float CalcDistSquared(sf::Vector2f const& a, sf::Vector2f const& b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int const ENEMY_HIT_FREQ = 30;

} // namespace

Game::Game()
    : _window( // Initialize window to be fullscreen
        sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
        "Face Fight",
        sf::Style::Fullscreen),
    _mouseLeftIsPressed(false),
    _enemyHitTimer(0)
{
    // Set frame rate limit to not torture the GPU too much
    _window.setFramerateLimit(FRAMERATE_LIMIT);

    // Enable vertical sync for some screens that get screen tearing
    _window.setVerticalSyncEnabled(true);

    // Hide the mouse cursor
    _window.setMouseCursorVisible(false);

    _enemy.SetPosition({SCREEN_WIDTH - 400.f, 600.f});
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
    if (_enemyHitTimer > 0)
    {
        _enemyHitTimer--;
    }

    _player.SetPosition({
        (float)sf::Mouse::getPosition(_window).x,
        (float)sf::Mouse::getPosition(_window).y
    });

    bool closeEnough = (CalcDistSquared(_player.GetPosition(), _enemy.GetPosition())
        <= ENEMY_REACH_PLAYER_DIST * ENEMY_REACH_PLAYER_DIST);

    // If enemy is not close enough to player, it moves towards player
    if (!closeEnough)
    {
        _enemy.MoveTowards(_player.GetPosition(), Enemy::SPEED);
    }
    // otherwise enemy will be close enough and it will be hitting player
    else if (_enemyHitTimer == 0)
    {
        _enemy.Hit(_player.GetPosition());
        _player.GetHit();
        _enemyHitTimer = ENEMY_HIT_FREQ;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!_mouseLeftIsPressed)
        {
            _player.Hit(_enemy.GetPosition());
            if (closeEnough)
            {
                _enemy.GetHit();
            }
            _mouseLeftIsPressed = true;
        }
    }
    else
    {
        _mouseLeftIsPressed = false;
    }

    _player.Update();
    _enemy.Update();
}

void Game::Draw()
{
    _enemy.DrawEntity(_window);
    _player.DrawEntity(_window);

    _enemy.DrawFist(_window);
    _player.DrawFist(_window);

    _enemy.DrawHealthBar(_window);
    _player.DrawHealthBar(_window);
}