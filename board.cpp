#include "board.hpp"
#include <fstream>
Board::Board(){
    field = new Cell*[50];
    for(int i = 0; i < 50; ++i)
        field[i] = new Cell[50];
}

Board::~Board(){
    for(int i = 0; i < 50; ++i)
        delete[] field[i];
    delete[] field;
}

bool Board::load(const std::string &file){
    std::ifstream inFile;
    std::string getSize;
    std::string getData;
    int rows = 0;
    int cols = 0;
    inFile.open(file);
    if(!inFile.is_open()) return false;
    while(true){
        if(getline(inFile,getSize,' ')) rows++;
        if(getline(inFile,getSize,'\n')) cols++;
        if(inFile.eof()) break;
    }
    this->x = rows;
    this->y = cols;
    inFile.close();
    inFile.open(file);
    if(!inFile.is_open()) return false;
    char data;
    for(int i = 0; i < rows; ++i){
        getline(inFile,getData,'\n');
        for(int j = 0; j < cols; ++j){
            data = getData[j];
            if(data == '*'){
                field[i][j] =  Cell(true);
            }
            else field[i][j] =  Cell(false);
        }
    }
    inFile.close();
    return true;
}

bool Board::click(int x, int y){
    int mineCount = 0;
    if(!inRange(x,y)) return false;
    if(field[x][y].str()!= " ") return false; //cell is known
    mineCount = clickHelper(x,y);
    if(mineCount>0){
        field[x][y].setAdjacentMineCount(mineCount);
        return true;
    }
    else if (mineCount == 0){
        field[x][y].click();
        click(x+1,y);
        click(x-1,y);
        click(x,y+1);
        click(x,y-1);
        click(x+1,y+1);
        click(x-1,y-1);
        click(x+1,y-1);
        click(x-1,y+1);
    }
    else if (mineCount == -1){
        for(int i = 0; i < this->x; ++i){
            for(int j = 0; j < this->y; ++j){
                if(field[i][j].hasMine()) field[i][j].click();
            }
        }
    }
    return true;
}
int Board::clickHelper(int i, int j){ //Get adjacent mine count
    int count = 0;
    if(inRange(i,j))
        if(field[i][j].hasMine()) return -1;
    if(inRange(i+1,j))    
        if(field[i+1][j].hasMine()) count++;
    if(inRange(i,j+1))    
        if(field[i][j+1].hasMine()) count++;
    if(inRange(i-1,j)) 
        if(field[i-1][j].hasMine()) count++;
    if(inRange(i,j-1)) 
        if(field[i][j-1].hasMine()) count++;
    if(inRange(i+1,j+1)) 
        if(field[i+1][j+1].hasMine()) count++;
    if(inRange(i-1,j-1)) 
        if(field[i-1][j-1].hasMine()) count++;
    if(inRange(i-1,j+1)) 
        if(field[i-1][j+1].hasMine()) count++;
    if(inRange(i+1,j-1)) 
        if(field[i+1][j-1].hasMine()) count++;
    return count;
}

bool Board::inRange(int x, int y){
    if(x >= this->x || x < 0) return false; //out of x bounds
    if(y >= this->y || y < 0) return false; //out of y bounds
    return true;
}

bool Board::flag(int x, int y){
    if(!inRange(x,y)) return false;
    field[x][y].toggleFlag();
    return true;
}

bool Board::winGame(){
    int cells = this->x * this->y;
    int n = 0;
    for(int i = 0; i < this->x; ++i){
        for(int j = 0; j < this->y; ++j){
            if(field[i][j].str() != " ") n++;
            if(field[i][j].str() == " " && field[i][j].hasMine()) n++;
        }
    }
    if(n==cells){
        for(int i = 0; i < this->x; ++i){
            for(int j = 0; j < this->y; ++j){
                if(field[i][j].hasMine() && field[i][j].str() == " "){
                    field[i][j].click();
                }
            }
        }
            return true;
    }
    return false;
}

bool Board::loseGame(int x, int y){
    if(field[x][y].str() == "*")
        return true;
    return false;
}
std::string Board::str(){
    board = "    ";
    for(int n = 0; n < x; ++n)
        board += "  " + std::to_string(n) + " ";
    board += "\n";
    for(int i = 0; i <= x; ++i){
        for(int j = 0; j < y; ++j){
            if(j==0) board += "    ";
            board += "+---";
            if(j==x-1) board += "+\n";
        }
        if(i<this->x)board += "  " + std::to_string(i) + " ";
        for(int k = 0; k < y; ++k){
            if(i==x) break;
            board += "| " + field[i][k].str() + " ";
            if(k == y-1) board += "|\n";
        }
    }
    return board;
}