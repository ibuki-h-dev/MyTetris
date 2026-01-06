cmake_minimum_required(VERSION 3.10)
project(TetrisWasm)

if(EMSCRIPTEN)
    include(FetchContent)
    FetchContent_Declare(
        SFML
        # URLを以下のように修正してみてください
        GIT_REPOSITORY "https://github.com/Blaatand213/sfml-wasm.git"
        GIT_TAG master
    )
    
    set(SFML_OS_EMSCRIPTEN TRUE CACHE BOOL "" FORCE)
    set(SFML_BUILD_AUDIO FALSE CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK FALSE CACHE BOOL "" FORCE)
    set(SFML_BUILD_EXAMPLES FALSE CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(SFML)
else()
    find_package(SFML 3.0.2 COMPONENTS Graphics Window System REQUIRED)
endif()

# 以下は前回と同じです
add_executable(index 
    src/main.cpp 
    src/Board.cpp 
    src/Piece.cpp 
    src/Game.cpp
)

if(EMSCRIPTEN)
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

# 1. PC（Windows等）でビルドする時だけ実行する設定
if(NOT EMSCRIPTEN)
    add_custom_command(
        TARGET index POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/src/assets"  # コピー元（ソース）
        "$<TARGET_FILE_DIR:index>/assets"         # コピー先（.exeと同じ場所）
        COMMENT "Copying assets to build directory..."
    )
endif()