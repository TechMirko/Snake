#include <iostream>
#include <ncurses/ncurses.h>

void greetings() {
    initscr();
    printw("Premi invio per vedere un quadrato potentissimo!");
    refresh();
    getch();
    endwin();
}

void tatona() {
    initscr();

    int height = 10, width = 20, start_x = 10, start_y = 10;
    WINDOW *win = newwin(height, width, start_y, start_x);
    refresh();
    box(win, 0, 0);
    wrefresh(win);

    getch();
    endwin();
}

void prova() {
    initscr();
    move(0, 0);
    printw("L'origine della griglia sta qui :)");
    move(1, 0);
    printw("Sono qui...");
    move(2, 0);
    printw("Adesso sono qui...");
    getch();
    endwin();
}
