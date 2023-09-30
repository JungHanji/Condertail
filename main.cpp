#include <GameEngine/Game.hpp>

int main(){
    system("cls");
    init();
    App app({150, 35}, stringToWstring(pixel({0, 0, 0})));
    Game game;
    app.run(game);
}