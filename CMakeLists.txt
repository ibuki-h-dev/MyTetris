cmake_minimum_required(VERSION 3.10)
project(TetrisWasm)

if(EMSCRIPTEN)
    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0 # 確実に3.0を使用
    )
    # Webビルド用の強制設定
    set(SFML_OS_EMSCRIPTEN ON CACHE BOOL "" FORCE)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(SFML)
else()
    # PC版（vcpkgで入れたSFML 3.0）
    find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)
endif()

# 実行ファイル作成（ここからは共通）
add_executable(index src/main.cpp src/Board.cpp src/Piece.cpp src/Game.cpp)

if(EMSCRIPTEN)
    # SFML 3.0 はターゲット名が少し変わる場合があるため、
    # FetchContentで生成されるターゲットを直接指定
    target_link_libraries(index PRIVATE sfml-graphics sfml-window sfml-system)
    
    set_target_properties(index PROPERTIES SUFFIX ".html")
    target_link_options(index PRIVATE 
        "-sALLOW_MEMORY_GROWTH=1"
        "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/src/assets@assets"
        "-sSINGLE_FILE=1"
    )
else()
    target_link_libraries(index PRIVATE SFML::Graphics SFML::Window SFML::System)
    # assetsコピーのカスタムコマンド（以前と同じ）
endif()