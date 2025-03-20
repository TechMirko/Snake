#ifndef BOARD_H
#define BOARD_H

#include "Snake.h"
#include <ncurses/ncurses.h>

class Board: public Snake {
protected:
  WINDOW *sfondo;
  WINDOW *win;

  int coordApple[1][2];

public:
  bool gameOver;
  bool exitFromGame;
  Board();

  void backgroundPrint();
  void printDati(int level, int score, int speed);

  void generateApple();
  void displayApple();
  void displayBoard(int& punteggio, int speed, int level);
  int displaySnake(int vel, int level);


};



#endif //BOARD_H
