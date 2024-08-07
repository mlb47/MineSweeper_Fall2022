#include "text-menu-app.hpp"
#include <iostream>
#include <string>
using namespace std;

int main() {
  int posX,posY;
  char move;
  string fileName;
  TextMenuApp app;
  app.run();

  while(!app.load(fileName)){
    cout << app.getPrompt();
    cin >> fileName;
  }

  cout << app.getPrompt(); 
  do{  
    cin >> move >> posX >> posY;
    app.move(move,posX,posY);
    cout << app.getPrompt(); 
  }while(!app.gameIsOver());

  cout << app.getPrompt();
  return 0;
}