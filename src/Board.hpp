#pragma once
#include<string>
#include<vector>
#include<memory>
#include<SFML/Graphics.hpp>
#include"Config.hpp"
#include"UIUtils.hpp"

class Board{
    private:
        float bWidth;
        float bHeight;
        float colorTimer = 0.0f;
        sf::Font font;
        std::unique_ptr<sf::Text> nextLabel;
        std::unique_ptr<sf::Text> holdLabel;
        sf::ConvexShape plate;
        sf::ConvexShape plateEdge;
        sf::RectangleShape frame;
        sf::ConvexShape nextWindow;
        sf::ConvexShape holdWindow;

        struct LineEffect{
            float y_pos;
            float timer;
        };
        std::vector<LineEffect> activeEffects;
        void drawNextWindow(sf::RenderWindow& window) const;
        void drawHoldWindow(sf::RenderWindow& window) const;
    public:
        static const int WIDTH = 10;
        static const int HEIGHT = 23;
        static const int blank = 3;
        static const unsigned int CELL_SIZE = 30u;
        std::vector<std::vector<int>> grid;
   
        Board();
        ~Board(){}

        bool isOccupied(int x, int y) const;
        void placeBlock(int x, int y, int colorID);
        int clearLines();
        void draw(sf::RenderWindow& window) const;
        void update(float dt);
};
