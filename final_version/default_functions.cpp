//
// Created by Gabriele Preti
//

#include <iostream>
using namespace std;
#include <ncurses.h>

void get_terminal(int &xmax, int &ymax) { //ottiene le massime dimensioni della finestra
    getmaxyx(stdscr, ymax, xmax);
}

WINDOW* centered_win(int h, int w, int xmax, int ymax) { //crea finestra centrata
    WINDOW *boardwin = newwin(h, w, (ymax/2)-(h/2), (xmax/2)-(w/2));
    return boardwin;
}

WINDOW* standard_win(int h, int w) { //crea finestra con altezza e larghezza date
    int xmax;
    int ymax;
    get_terminal(xmax, ymax);
    WINDOW *boardwin = newwin(h, w, (ymax/2)-(h/2), (xmax/2)-(w/2));
    return boardwin;
}