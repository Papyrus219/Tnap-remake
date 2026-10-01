#include <iostream>
#include <Meme/game.hpp>

int main()
{
    meme::Game game{};
    game.Init();
    game.Run();

    return 0;
}
