//
// Created by Gabriele Preti
//

#ifndef DEFAULT_FUNCTIONS_H
#define DEFAULT_FUNCTIONS_H
#include <iostream>
using namespace std;
#include <ncurses.h>

void get_terminal(int &xmax, int &ymax);
WINDOW* centered_win(int h, int w, int xmax, int ymax);
WINDOW* standard_win(int h, int w);

#endif //DEFAULT_FUNCTIONS_H
