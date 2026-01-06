cmake_minimum_required(VERSION 3.16)

project(Tetris
    VERSION 1.0
    LANGUAGES CXX
)

# =========================
# C++ 設定
# =========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =========================
# ソース
# =========================
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
    src/Piece.cpp
)

add_executable(Tetris ${SOURCES})

# =========================
# SFML
# =========================
find_package(SFML 3.0 REQUIRED COMPONENTS
    Graphics
    Window
    System
)

target_link_libraries(Tetris PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# =========================
# アセットコピー（実行時に必要）
# =========================
add_custom_command(
    TARGET Tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Tetris>/assets
)

# =========================
# コンパイル警告（評価上がる）
# =========================
if (MSVC)
    target_compile_options(Tetris PRIVATE /W4)
else()
    target_compile_options(Tetris PRIVATE -Wall -Wextra -Wpedantic)
endif()
