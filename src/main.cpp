#include "Game.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
void game_loop(void* arg){
    Game* game = static_cast<Game*>(arg);

    float dt = game->clock.restart().asSeconds();
    game->processEvent(dt);
    game->update(dt);
    game->render();
}
int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    Game game;
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(game_loop, &game, 0, 1);
#else
    game.run();
#endif
    return 0;
}