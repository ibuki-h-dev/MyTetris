cmake_minimum_required(VERSION 3.10)
project(TetrisWasm)

if(EMSCRIPTEN)
    # --- ここが重要：SFMLの判定を力技で「Web」にする ---
    set(SFML_OS_EMSCRIPTEN ON CACHE BOOL "" FORCE)
    set(EMSCRIPTEN ON CACHE BOOL "" FORCE)
    # SFML 3.0の内部でチェックされている可能性のあるフラグを網羅
    set(CMAKE_SYSTEM_NAME "Emscripten" CACHE STRING "" FORCE)
    
    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
    )

    # 依存ライブラリをSFMLに自前でビルドさせる
    set(SFML_USE_SYSTEM_DEPS OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(SFML)
else()
    # PC版
    find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)
endif()

# 実行ファイル設定
add_executable(index src/main.cpp src/Board.cpp src/Piece.cpp src/Game.cpp)

if(EMSCRIPTEN)
    # SFML 3.0 FetchContent版のライブラリ名
    target_link_libraries(index PRIVATE sfml-graphics sfml-window sfml-system)
    
    set_target_properties(index PROPERTIES SUFFIX ".html")
    target_link_options(index PRIVATE 
        "-sALLOW_MEMORY_GROWTH=1"
        "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/src/assets@assets"
        "-sSINGLE_FILE=1"
        "-sUSE_GLFW=3" 
    )
else()
    target_link_libraries(index PRIVATE SFML::Graphics SFML::Window SFML::System)
    # (ここにassetsコピーのコマンド)
endif()