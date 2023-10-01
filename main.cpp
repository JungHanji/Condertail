#include <GameEngine/Game.hpp>

int main(){
    system("cls");
    init();
    App app(res, stringToWstring(pixel({0, 0, 0})));
    Game game;
    app.run(game);
}