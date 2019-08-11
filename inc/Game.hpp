#include <vector>
#include <utility>

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

class Game
{
public:
    bool checkFieldAt( int x, int y );
    FieldState getFieldStateAt( int x, int y );
    int getBombCounterAt( int x, int y );
    void SetBombAt( int x, int y );
    Game( int x = 10, int y = 10 );
private:
    std::vector<std::vector<Field>> board;
private:
    void increaseBombCountersAround( int x, int y );
    bool isInBoard( int x, int y );
};