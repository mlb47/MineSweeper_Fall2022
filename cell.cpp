#include "cell.hpp"
const std::string Cell::MINE = "*";
const std::string Cell::FLAG = "\u2691";
const std::string Cell::NO_ADJACENT_MINES = "\u25A2";
const std::string Cell::UNKNOWN = " ";
Cell::Cell(){
    status = UNKNOWN;
}

Cell::Cell(bool mine){
    this->mine = mine;
    status = UNKNOWN;
}

bool Cell::hasMine(){
    if(mine)
        return true;
    return false;
}

void Cell::toggleFlag(){
    if(status == FLAG){
        status = UNKNOWN;
        return;
    }
    status = FLAG;
}

bool Cell::click(){
    if(status == FLAG) return false;
    if(!mine){
        status = NO_ADJACENT_MINES;
        return false;
    }
    status = MINE;
    return true;
}
void Cell::setAdjacentMineCount(int count){
    status = std::to_string(count);
}
std::string Cell::str(){return status;}