#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

enum class FieldState
{
    Bomb,
    Free,
};

enum class IsChecked
{
    Yes,
    No
};

struct Field
{
    FieldState first;
    IsChecked second;
    int third = 0;
};

using CoordsOfBombs = std::vector<std::pair<int,int>>;

class Game
{
public:
    bool checkFieldAt( int x, int y );
    void checkFreeFieldsAround( int x, int y );
    FieldState getFieldStateAt( int x, int y );
    int getBombCounterAt( int x, int y );
    void setBombAt( int x, int y );
    void setBombVector( CoordsOfBombs coords_of_bombs );
    char printField( int x, int y );
    void printBoard();
    Game( int x = 10, int y = 10 );
private:
    std::vector<std::vector<Field>> board;
private:
    void increaseBombCountersAround( int x, int y );
    bool isInBoard( int x, int y );
};