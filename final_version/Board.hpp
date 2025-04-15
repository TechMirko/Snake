#ifndef BOARD_H
#define BOARD_H

#include "Snake.hpp"
#include <ncurses.h>

class Board: public Snake {
protected:
  WINDOW *sfondo;
  WINDOW *win;

  clock_t before;
  clock_t timer;

  int coordApple[1][2];
  float duration;

public:
  bool gameOver;
  bool exitFromGame;
  Board();

  void backgroundPrint();
  void printDati(int level, int score, int speed);

  void generateApple();
  void displayApple();
  void displayBoard(int& punteggio, int speed, int level, int valMela);
  int displaySnake(int vel, int level, int valMela);

  void printTime();

};



#endif //BOARD_H
