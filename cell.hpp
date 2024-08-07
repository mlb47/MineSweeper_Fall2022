#ifndef CELL_H
#define CELL_H
#include <string>
class Cell{
    public:
        Cell();
        Cell(bool mine);
        bool hasMine();
        void toggleFlag();
        bool click();
        void setAdjacentMineCount(int count);
        std::string str();
        static const std::string MINE;
        static const std::string FLAG;
        static const std::string NO_ADJACENT_MINES;
        static const std::string UNKNOWN;
    private:
        std::string status;
        int count;
        bool mine;
};
#endif