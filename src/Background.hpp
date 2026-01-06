#pragma once
#include"Config.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Background {
    struct Star {
        sf::CircleShape shape; // 点ではなく円にする
        float speed;
    };
    std::vector<Star> stars;

public:
    Background(int count) {
        for (int i = 0; i < count; ++i) {
            Star s;
            // 星の大きさを 1.0〜3.0 ピクセルの間でランダムに設定
            float radius = static_cast<float>(rand() % 3 + 1);
            s.shape.setRadius(radius);
            
            // ランダムな位置
            s.shape.setPosition({(float)(rand() % 1600), (float)(rand() % 800)});
            
            // 色と透明度（遠くの星は暗く）
            s.speed = (float)(rand() % 100 + 50) / 100.0f;
            std::uint8_t alpha = s.speed * 100 + 100;
            s.shape.setFillColor(sf::Color(211, 231, 231, alpha));

            stars.push_back(s);
        }
    }

    void update() {
        for (auto& s : stars) {
            auto pos = s.shape.getPosition();
            pos.x -= s.speed*0.6;
            pos.y += s.speed; // 下へ流れる
            if(pos.x < -10) pos.x = Config::ScreenWidth+10;
            if (pos.y > 800) pos.y = -10; // 画面外に出たら上に戻る
            s.shape.setPosition(pos);
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& s : stars) {
            window.draw(s.shape);
        }
    }
};