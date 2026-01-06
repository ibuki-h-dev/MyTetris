#pragma once
#include <SFML/Graphics.hpp>
#include "Config.hpp"

// 汎用的な角丸四角形作成関数
inline sf::ConvexShape createRoundedRect(float width, float height,const unsigned int pointsPerCorner, float radius, sf::Color color) {
    sf::ConvexShape shape;
    shape.setPointCount(pointsPerCorner * 4);
    shape.setFillColor(color);

    float w = width;
    float h = height;
    float r = radius;

    // 半径が大きすぎないように調整
    if (r > w / 2) r = w / 2;
    if (r > h / 2) r = h / 2;

    unsigned int index = 0;

    // 右上 -> 右下 -> 左下 -> 左上の順で角を計算
    auto addCorner = [&](float centerX, float centerY, float startAngle) {
        for (unsigned int i = 0; i < pointsPerCorner; ++i) {
            float angle = (startAngle + (i * 90.f / (pointsPerCorner - 1))) * 3.14159f / 180.f;
            shape.setPoint(index++, {centerX + r * std::cos(angle), centerY + r * std::sin(angle)});
        }
    };

    addCorner(w - r, r,     270.f); // 右上
    addCorner(w - r, h - r, 0.f);   // 右下
    addCorner(r,     h - r, 90.f);  // 左下
    addCorner(r,     r,     180.f); // 左上

    return shape;
}
// 虹色を作るための関数
inline sf::Color getRainbowColor(float phase) {
    // phase: 0.0 ~ 1.0 の値
    int r = static_cast<int>(std::sin(phase * 6.28f + 0.0f) * 127 + 128);
    int g = static_cast<int>(std::sin(phase * 6.28f + 2.09f) * 127 + 128);
    int b = static_cast<int>(std::sin(phase * 6.28f + 4.18f) * 127 + 128);
    return sf::Color(r, g, b);
}