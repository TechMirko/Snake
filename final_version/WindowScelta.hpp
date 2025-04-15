//
// Created by graziacomp on 3/15/25.
//

#ifndef WINDOWSCELTA_H
#define WINDOWSCELTA_H

#include <iostream>
using namespace std;
#include "Constant.hpp"
#include <ncurses.h>

// classe suprema per le finestre
class WindowScelta {

  protected:
    int numChoices;
    WINDOW *win;
    int pointing;
    string name;
    int x, y;

  public:
    WindowScelta(int n, string name);

    int windowDisplay(string Op[], int length, int punteggio);  // rimanda l'indice delle opzioni che ha a disposizione
};



#endif //WINDOWSCELTA_H
