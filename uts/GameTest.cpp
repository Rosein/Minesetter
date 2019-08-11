#include "gtest/gtest.h"
#include "../inc/Game.hpp"

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