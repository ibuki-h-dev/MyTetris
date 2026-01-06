cmake_minimum_required(VERSION 3.10)
project(TetrisWasm)

if(EMSCRIPTEN)
    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
    )
    
    # SFMLが内部でOS判定を行う前に、Emscriptenであることを強制的に認識させる
    set(SFML_OS_EMSCRIPTEN TRUE CACHE BOOL "" FORCE)
    set(CMAKE_SYSTEM_NAME Emscripten CACHE STRING "" FORCE)

    FetchContent_MakeAvailable(SFML)
else()
    find_package(SFML 3.0.2 COMPONENTS Graphics Window System REQUIRED)
endif()

add_executable(index 
    src/main.cpp 
    src/Board.cpp 
    src/Piece.cpp 
    src/Game.cpp
)

if(EMSCRIPTEN)
    # SFMLの内部ターゲット名を直接指定
    target_link_libraries(index PRIVATE sfml-graphics sfml-window sfml-system)
    
    set_target_properties(index PROPERTIES SUFFIX ".html")
    target_link_options(index PRIVATE 
        "-sALLOW_MEMORY_GROWTH=1"
        "-sUSE_PTHREADS=0"
        "--preload-file" "src/assets@src/assets"
        "-sSINGLE_FILE=1"
    )
else()
    target_link_libraries(index PRIVATE SFML::Graphics SFML::Window SFML::System)
endif()

target_include_directories(index PRIVATE src)