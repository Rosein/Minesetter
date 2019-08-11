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
    EXPECT_TRUE( game.checkFieldAt( 0, 0 ) );
    game.SetBombAt( 0, 0 );
    EXPECT_EQ( game.getFieldStateAt( 0, 0 ), FieldState::Bomb );
}


TEST_F( PrepareBoard, CheckFieldAroundBomb )
{
    game.SetBombAt( 0, 0 );
    EXPECT_TRUE( game.checkFieldAt( 0, 1 ) );
    EXPECT_EQ( game.getFieldStateAt( 0, 1 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 0, 1 ), 1 );

    EXPECT_TRUE( game.checkFieldAt( 1, 1 ) );
    EXPECT_EQ( game.getFieldStateAt( 1, 1 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 1, 1 ), 1 );

    EXPECT_TRUE( game.checkFieldAt( 1, 0 ) );
    EXPECT_EQ( game.getFieldStateAt( 1, 0 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 1, 0 ), 1 );

    game.SetBombAt( 2, 2 );

    EXPECT_FALSE( game.checkFieldAt( 1, 1 ) );
    EXPECT_EQ( game.getFieldStateAt( 1, 1 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 1, 1 ), 2 );

    EXPECT_TRUE( game.checkFieldAt( 3, 3 ) );
    EXPECT_EQ( game.getFieldStateAt( 3, 3 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 3, 3 ), 1 );    

}

TEST_F( PrepareBoard, CheckHalfBoardAfterOneClick )
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
    EXPECT_EQ( game.getBombCounterAt( 0, 2 ), 0 );

    EXPECT_FALSE( game.checkFieldAt( 0, 3 ) );
    EXPECT_EQ( game.getFieldStateAt( 0, 3 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 0, 3 ), 0 );

    EXPECT_FALSE( game.checkFieldAt( 5, 6 ) );
    EXPECT_EQ( game.getFieldStateAt( 5, 6 ), FieldState::Free );
    EXPECT_EQ( game.getBombCounterAt( 5, 6 ), 2 );


}