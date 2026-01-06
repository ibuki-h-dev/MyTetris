#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <optional>
#include <ctime>
#include <random>
#include <algorithm>
#include "Board.hpp"
#include "Piece.hpp"
#include "Background.hpp"
enum class State{
    Menu,
    Playing,
    ClearLine,
    GameOver
};

class Game{
public:
sf::Clock clock;
    Game();
    void run();
    void processEvent(float dt);
    void update(float dt);
    void render();
private:
    void handleInput(float dt);
    void refillBag();
    void reset();
    void spawnPiece();

    sf::RenderWindow window;
    State state;

    Board board;
    Piece piece;
    Background bg;

    float timer;
    float lineClearTimer;
    float lockDelay_changable;
    bool isTouchingGround;
    bool canHold;

    std::vector<int> next;
    std::optional<int> hold;
    int currentID;

    bool heldKeys[10] = {false};

    sf::Clock dasClock, arrClock, lockClock;

    sf::Vector2i touchStartPos;
    sf::Vector2i lastMovePos;
    bool isSwiping = false;
    const float swipeDist = 40.0f;

    sf::Font font;
    std::unique_ptr<sf::Text> gameOverText;
};
