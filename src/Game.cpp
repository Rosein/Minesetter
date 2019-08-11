#include "../inc/Game.hpp"

bool Game::checkFieldAt( int x, int y )
{
    if( board[ x ][ y ].second == IsChecked::No )
    {
        board[ x ][ y ].second = IsChecked::Yes;
        return true;
    }
    return false;
}


FieldState Game::getFieldStateAt( int x, int y )
{
    return board[ x ][ y ].first;
}

int Game::getBombCounterAt( int x, int y )
{
    return board[ x ][ y ].third;
}

void Game::SetBombAt( int x, int y )
{
    board[ x ][ y ].first = FieldState::Bomb;
    increaseBombCountersAround( x, y );
}


Game::Game( int x, int y )
    : board( x, std::vector<Field>( y, { FieldState::Free, IsChecked::No } ) )
{
    
}

void Game::increaseBombCountersAround( int x, int y )
{
    for( int i = -1 ; i < 2; ++i )
        for( int j = -1 ; j < 2; ++j )
            if( isInBoard( x + i, y + j ) && ( i != 0 || j != 0 ) )
                if( board[ x + i ][ y + j ].first == FieldState::Free )
                    board[ x + i ][ y + j ].third++;
}

bool Game::isInBoard( int x, int y )
{
    return 0 <= x && x < board.size()
        && 0 <= y && y < board[ 0 ].size();
}