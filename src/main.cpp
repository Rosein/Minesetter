#include "../inc/Game.hpp"
#include <stdlib.h>

void play_minesweeper( int height, int width, int numb_bombs )
{
    std::srand(std::time(nullptr));
    Game game( height, width );
    game.setBombVector( game.generateRandomBombsN( numb_bombs ) );
    int x, y;
    while( game.getGameState() == GameState::InProgress )
    {
        system("clear");
        game.printBoard();
        std::cout << std::endl;
        std::cin >> x >> y;
        game.checkFieldAt( x, y );
    }        
    if( game.getGameState() == GameState::Lose )
        std::cout << std::endl << "GAME OVER" << std::endl;
    if( game.getGameState() == GameState::Win )
        std::cout << std::endl << "VICTORY" << std::endl;
            
}
int main()
{
    play_minesweeper( 10, 10, 15 );
    return 0;
}