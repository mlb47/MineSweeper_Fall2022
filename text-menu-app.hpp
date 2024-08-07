#ifndef TEXT_MENU_APP_H
#define TEXT_MENU_APP_H
#include "board.hpp"
#include <iostream>
class TextMenuApp{
    public:
        void run();
        bool load(const std::string &fileName);
        bool move(char move, int x, int y);
        bool gameIsOver();
        std::string getPrompt();
    private:
    Board b;
    std::string prompt;
};
#endif