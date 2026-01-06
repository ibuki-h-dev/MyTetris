cmake_minimum_required(VERSION 3.10)
project(CppTetris)

find_package(SFML 3.0.2 COMPONENTS Graphics Audio Window System REQUIRED)

add_executable(Tetris src/main.cpp src/Board.cpp src/Piece.cpp src/Game.cpp)

if (MSVC)
    # 読み込み(source)と出力(execution)の両方をUTF-8に設定します
    add_compile_options("/utf-8")
endif()

target_link_libraries(Tetris PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)

target_include_directories(Tetris PRIVATE src)

