#include "Piece.hpp"

const int Piece::shapes[7][4][2]={
        //Iミノ
        {{ 0, 0}, {-1, 0}, { 1, 0}, { 2, 0}},
        //Oミノ
        {{ 0, 0}, { 1, 0}, { 0,-1}, { 1,-1}},
        //S
        {{ 0, 0}, {-1, 0}, { 0,-1}, { 1,-1}},
        //Z
        {{ 0, 0}, { 1, 0}, { 0,-1}, {-1,-1}},
        //J
        {{ 0, 0}, { 1, 0}, {-1, 0}, {-1,-1}},
        //L
        {{ 0, 0}, {-1, 0}, { 1, 0}, { 1,-1}},
        //T
        {{ 0, 0}, { 1, 0}, {-1, 0}, { 0,-1}}
};

Piece::Piece(int t) : pieceID(t), x(5), y(Board::blank-1){
    for(int i=0; i<4; ++i){
        body[i][0] = shapes[pieceID][i][0];
        body[i][1] = shapes[pieceID][i][1];
    }
}

int Piece::getID()const{
    return pieceID;
}
sf::Color Piece::getColor()const{
    switch(pieceID){
        case 0: return sf::Color::Cyan; break;
        case 1: return sf::Color::Yellow; break;
        case 2: return sf::Color::Green; break;
        case 3: return sf::Color::Red; break;
        case 4: return sf::Color::Blue; break;
        case 5: return sf::Color(255, 165, 0); break;
        case 6: return sf::Color(128, 0, 128); break;
        default: return sf::Color::White; break;
    }
}
int Piece::getX(int index)const{
    return x + body[index][0];
}

int Piece::getY(int index)const{
    return y + body[index][1];
}

bool Piece::isPossible(const Board& board, int px, int py, const int tempBody[4][2]) const {
    for (int i = 0; i < 4; ++i) {
        if (board.isOccupied(px + tempBody[i][0], py + tempBody[i][1])) {
            return false;
        }
    }
    return true;
}

bool Piece::move(const Board& board, int dx, int dy){
    if(!isPossible(board, x+dx, y+dy, body)) return false;
    x += dx;
    y += dy;
    return true;
}
bool Piece::rotate(const Board& board, bool rd){
    if(pieceID == 1) return true;
    int nextBody[4][2];
    int rotdir = rd ? 1 :-1;
    for(int i=0; i<4; ++i){
        nextBody[i][0] = -rotdir*body[i][1];
        nextBody[i][1] = rotdir*body[i][0];
    }

    if(!isPossible(board, x, y, nextBody))return false;

    for(int i=0; i<4; ++i){
        body[i][0] = nextBody[i][0];
        body[i][1] = nextBody[i][1];
    }
    return true;
}

void Piece::draw(sf::RenderWindow& window, bool shadowmode){
    sf::RectangleShape block(sf::Vector2f(29.5f, 29.5f)); // CELL_SIZE - 1
    if(!shadowmode){
        switch(pieceID){
                case 0: block.setFillColor(sf::Color::Cyan); break;
                case 1: block.setFillColor(sf::Color::Yellow); break;
                case 2: block.setFillColor(sf::Color::Green); break;
                case 3: block.setFillColor(sf::Color::Red); break;
                case 4: block.setFillColor(sf::Color::Blue); break;
                case 5: block.setFillColor(sf::Color(255, 165, 0)); break;
                case 6: block.setFillColor(sf::Color(128, 0, 128)); break;
                default: block.setFillColor(sf::Color::White); break;
        }
        block.setOutlineThickness(0.5f);
        block.setOutlineColor(sf::Color::White);
    }else{
        block.setFillColor(sf::Color::Transparent);
        block.setOutlineThickness(1.5f);
        switch(pieceID){
                case 0: block.setOutlineColor(sf::Color::Cyan); break;
                case 1: block.setOutlineColor(sf::Color::Yellow); break;
                case 2: block.setOutlineColor(sf::Color::Green); break;
                case 3: block.setOutlineColor(sf::Color::Red); break;
                case 4: block.setOutlineColor(sf::Color::Blue); break;
                case 5: block.setOutlineColor(sf::Color(255, 165, 0)); break;
                case 6: block.setOutlineColor(sf::Color(128, 0, 128)); break;
                default: block.setOutlineColor(sf::Color::White); break;
        }
    }

    for (int i = 0; i < 4; ++i) {
        // getX(), getY() を利用して描画位置を決める
        block.setPosition({static_cast<float>(Config::Board_X)+getX(i) * Board::CELL_SIZE, static_cast<float>(Config::Board_Y)+(getY(i)-Board::blank)*Board::CELL_SIZE});
        window.draw(block);
    }
}

void Piece::drawAt(sf::RenderWindow& window, float x, float y, bool isSmall) const {
    sf::RectangleShape block(sf::Vector2f(Config::CellSize - 1, Config::CellSize - 1));
    block.setFillColor(getColor()); // 既存の色取得関数
    block.setOutlineThickness(1.0f);
    block.setOutlineColor(sf::Color(255, 255, 255, 100));
    if (isSmall) block.setScale({0.7f, 0.7f}); // Next用などに少し小さくする場合

    for (int i = 0; i < 4; i++) {
        // blockPosition[i] はテトリミノの形状データ (0,0基準)
        block.setPosition({
            x + body[i][0] * (Config::CellSize * (isSmall ? 0.7f : 1.0f)),
            y + body[i][1] * (Config::CellSize * (isSmall ? 0.7f : 1.0f))
        });
        window.draw(block);
    }
}