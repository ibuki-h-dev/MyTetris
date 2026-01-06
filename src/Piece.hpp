#pragma once
#include <SFML/Graphics.hpp>
#include"Board.hpp"
#include"Config.hpp"

class Piece{
private:
    static const int shapes[7][4][2];
    int pieceID;
    int x; 
    int y;
public:
    int body[4][2];
    Piece(int t);
    int getID()const;
    sf::Color getColor()const;
    int getX(int index)const;
    int getY(int index)const;
    bool isPossible(const Board& board, int px, int py, const int tempBody[4][2]) const;
    bool move(const Board& board, int dx, int dy);
    bool rotate(const Board& board, bool rd);
    void draw(sf::RenderWindow& window, bool shadowmode);
    void drawAt(sf::RenderWindow& window, float x, float y, bool isSmall)const;
};