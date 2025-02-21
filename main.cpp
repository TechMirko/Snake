#include <iostream>
#include <ncurses/ncurses.h>

// g++ main.cpp -lncurses -o snake

int main() {
    initscr();
    printw("Hello, World!");
    refresh();
    getch();
    endwin();
    return 0;
}