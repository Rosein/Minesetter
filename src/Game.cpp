#include "../inc/Game.hpp"

bool Game::checkFieldAt( int x, int y )
{
    if( board[ x ][ y ].second == IsChecked::No )
    {
        board[ x ][ y ].second = IsChecked::Yes;
        if(  board[ x ][ y ].first == FieldState::Free )
        {
            free_unchecked_field_counter--;
            if( free_unchecked_field_counter == 0 )
                state = GameState::Win;
            if( board[ x ][ y ].third == 0 )
                checkFreeFieldsAround( x, y );
        }
        else
        {
            state = GameState::Lose;
        }
        return true;
    }
    return false;
}

void Game::checkFreeFieldsAround( int x, int y )
{
    for( int i = -1 ; i < 2; ++i )
        for( int j = -1 ; j < 2; ++j )
        {
            // std::cout << "(" << x + i << ", " << y + j << ")" << std::endl;
            if( isInBoard( x + i, y + j ) && ( i != 0 || j != 0 ) )
                if( board[ x + i ][ y + j ].first == FieldState::Free && 
                    board[ x + i ][ y + j ].second == IsChecked::No )
                {
                    board[ x + i ][ y + j ].second = IsChecked::Yes;
                    free_unchecked_field_counter--;
                    // printBoard();
                    if ( board[ x + i ][ y + j ].third == 0 )
                        checkFreeFieldsAround( x + i, y + j );
                }
        }
    if( free_unchecked_field_counter == 0 )
        state = GameState::Win;
}

FieldState Game::getFieldStateAt( int x, int y )
{
    return board[ x ][ y ].first;
}

int Game::getBombCounterAt( int x, int y )
{
    return board[ x ][ y ].third;
}

void Game::setBombAt( int x, int y )
{
    board[ x ][ y ].first = FieldState::Bomb;
    increaseBombCountersAround( x, y );
}

void Game::setBombVector( CoordsOfBombs coords_of_bombs )
{
    for_each( coords_of_bombs.begin(), coords_of_bombs.end(), [&]( std::pair<int,int> coords )
        {
            if( isInBoard( coords.first, coords.second ) && 
                board[ coords.first ][ coords.second ].first == FieldState::Free &&
                board[ coords.first ][ coords.second ].second == IsChecked::No )
            {
                free_unchecked_field_counter--;
                setBombAt( coords.first, coords.second );
            }
        });
}

CoordsOfBombs Game::generateRandomBombsN( int n )
{
    CoordsOfBombs random_coords( n );
    std::for_each( random_coords.begin(), random_coords.end(), [&]( std::pair<int,int> & coords )
                                                                {
                                                                    coords.first = random() % board.size();
                                                                    coords.second = random() % board[ 0 ].size();
                                                                });
    return random_coords;
}

char Game::printField( int x, int y )
{
    if( board[ x ][ y ].second == IsChecked::No )
        return '*';
    else if( board[ x ][ y ].first == FieldState::Bomb )
        return '@';
    else if( board[ x ][ y ].third == 0 )
        return '.';
    else
        return board[ x ][ y ].third + 48;

}

void Game::printBoard()
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    for( int i = 0; i < board.size(); ++i )
    {
        for( int j = 0; j < board[ 0 ].size(); ++j )
            std::cout << std::setw( 2 ) << printField( i , j );
    std::cout << std::endl;
    }
    std::cout << std::endl;
}

Game::Game( int x, int y )
    : board( x, std::vector<Field>( y, { FieldState::Free, IsChecked::No } ) ),
      state( GameState::InProgress ),
      free_unchecked_field_counter( x * y )
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

GameState Game::getGameState()
{
    return state;
}
