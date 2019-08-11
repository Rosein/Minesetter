#include "gtest/gtest.h"
#include "../inc/Game.hpp"
#include <numeric>

class PrepareBoard : public ::testing::Test
{
protected:
    Game game;
};

TEST_F( PrepareBoard, CheckFieldWithBomb )
{
    game.setBombAt( 0, 0 );
    EXPECT_EQ( game.getGameState(), GameState::InProgress );    
    EXPECT_TRUE( game.checkFieldAt( 0, 0 ) );
    EXPECT_EQ( game.getFieldStateAt( 0, 0 ), FieldState::Bomb );
    EXPECT_EQ( game.getGameState(), GameState::Lose );
}


TEST_F( PrepareBoard, CheckFieldAroundBomb )
{
    game.setBombAt( 0, 0 );
    EXPECT_TRUE( game.checkFieldAt( 0, 1 ) );
    EXPECT_EQ( game.getFieldStateAt( 0, 1 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 0, 1 ), 1 );

    EXPECT_TRUE( game.checkFieldAt( 1, 1 ) );
    EXPECT_EQ( game.getFieldStateAt( 1, 1 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 1, 1 ), 1 );

    EXPECT_TRUE( game.checkFieldAt( 1, 0 ) );
    EXPECT_EQ( game.getFieldStateAt( 1, 0 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 1, 0 ), 1 );

    game.setBombAt( 2, 2 );

    EXPECT_FALSE( game.checkFieldAt( 1, 1 ) );
    EXPECT_EQ( game.getFieldStateAt( 1, 1 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 1, 1 ), 2 );

    EXPECT_TRUE( game.checkFieldAt( 3, 3 ) );
    EXPECT_EQ( game.getFieldStateAt( 3, 3 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 3, 3 ), 1 );    

}

class PrepareGameplay : public ::testing::Test
{
protected:
    Game game;
};

TEST_F( PrepareGameplay, CheckHalfBoardAfterOneClick )
{
    std::vector<std::pair<int,int>> coords_of_bombs { 10, { 0, 0 } };
    int i = 0;
    std::for_each( coords_of_bombs.begin(), coords_of_bombs.end(),[ &i ]( std::pair<int,int> & coords )
        {
            coords.first = i;
            coords.second = i;
            i++;
        });

    game.setBombVector( coords_of_bombs );
    
    EXPECT_TRUE( game.checkFieldAt( 0, 1 ) );
    EXPECT_EQ( game.getFieldStateAt( 0, 1 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 0, 1 ), 2 );
    
    EXPECT_TRUE( game.checkFieldAt( 0, 2 ) );
    EXPECT_EQ( game.getFieldStateAt( 0, 2 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 0, 2 ), 1 );

    EXPECT_TRUE( game.checkFieldAt( 0, 5 ) );
    EXPECT_EQ( game.getFieldStateAt( 0, 5 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 0, 5 ), 0 );

    EXPECT_FALSE( game.checkFieldAt( 0, 3 ) );
    EXPECT_EQ( game.getFieldStateAt( 0, 3 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 0, 3 ), 0 );

    EXPECT_FALSE( game.checkFieldAt( 5, 6 ) );
    EXPECT_EQ( game.getFieldStateAt( 5, 6 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 5, 6 ), 2 );

}



TEST_F( PrepareGameplay, WinOnBoardWithBombOnDiagonal )
{
    std::vector<std::pair<int,int>> coords_of_bombs { 10, { 0, 0 } };
    int i = 0;
    std::for_each( coords_of_bombs.begin(), coords_of_bombs.end(),[ &i ]( std::pair<int,int> & coords )
        {
            coords.first = i;
            coords.second = i;
            i++;
        });

    game.setBombVector( coords_of_bombs );
    
    EXPECT_TRUE( game.checkFieldAt( 0, 1 ) );
    EXPECT_EQ  ( game.getFieldStateAt( 0, 1 ), FieldState::Free );
    EXPECT_EQ  ( game.getBombCounterAt( 0, 1 ), 2 );
    
    EXPECT_TRUE( game.checkFieldAt( 1, 0 ) );
    EXPECT_EQ  ( game.getFieldStateAt( 1, 0 ), FieldState::Free );
    EXPECT_EQ  ( game.getBombCounterAt( 1, 0 ), 2 );

    EXPECT_TRUE( game.checkFieldAt( 8, 9 ) );
    EXPECT_EQ  ( game.getFieldStateAt( 8, 9 ), FieldState::Free );
    EXPECT_EQ  ( game.getBombCounterAt( 8, 9 ), 2 );

    EXPECT_TRUE( game.checkFieldAt( 0, 5 ) );
    EXPECT_EQ  ( game.getFieldStateAt( 0, 5 ), FieldState::Free );
    EXPECT_EQ  ( game.getBombCounterAt( 0, 5 ), 0 );

    EXPECT_TRUE( game.checkFieldAt( 9, 0 ) );
    EXPECT_EQ  ( game.getFieldStateAt( 9, 0 ), FieldState::Free );
    EXPECT_EQ  ( game.getBombCounterAt( 9, 0 ), 0 );

    EXPECT_TRUE( game.checkFieldAt( 9, 8 ) );
    EXPECT_EQ  ( game.getFieldStateAt( 9, 8 ), FieldState::Free );
    EXPECT_EQ  ( game.getBombCounterAt( 9, 8 ), 2 );

    EXPECT_EQ  ( game.getGameState(), GameState::Win );
}