#ifndef BOARD_H
#define BOARD_H
#include "cell.hpp"
class Board{
    public:
    Board();
    ~Board();
    bool load(const std::string &file);
    bool click(int x, int y);
    bool inRange(int x, int y);
    int clickHelper(int x, int y);
    bool flag(int x, int y);
    bool winGame();
    bool loseGame(int x, int y);
    std::string str();

    private:
    Cell **field;
    int x,y;
    std::string board;
};
#endif