#include "text-menu-app.hpp"
#include <iostream>
#include<fstream>
using namespace std;
void TextMenuApp::run(){
    b = *new Board();
    prompt = "Welcome to Minesweeper!";
}
bool TextMenuApp::load(const std::string &fileName){
    ifstream inFile;
    prompt = "Please enter a file name with the minefield information: ";
    inFile.open(fileName);
    if(!inFile.is_open()){
        return false;
    }
    b.load(fileName);
    prompt = b.str() + "Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: ";
    inFile.close();
    return true;
}

bool TextMenuApp::move(char move, int x, int y){
    if(move == 'C' || move == 'c'){
        if(b.click(x, y)){
            prompt = b.str() + "Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: ";
            if(b.loseGame(x,y)) prompt = b.str() + "Game Over!";
            else if(b.winGame()) prompt = b.str() + "You Win!";
            return true;
        }
    }        
    if(move == 'F' || move == 'f'){
        if(b.flag(x,y)){
            prompt = b.str() + "Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: ";
            return true;
        }
    }
    prompt = "Invalid move. Please enter your next move: ";
    return false;
}

bool TextMenuApp::gameIsOver(){
    if(prompt == b.str() + "You Win!" || prompt == b.str() + "Game Over!")
        return true;
    else prompt = "Please enter a file name with the minefield information: ";
    return false;
}
std::string TextMenuApp::getPrompt(){
    return prompt;
}