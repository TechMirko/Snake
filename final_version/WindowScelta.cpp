//
// Created by graziacomp on 3/15/25.
//
#include <iostream>
using namespace std;
#include "WindowScelta.hpp"
#include <ncurses.h>
#include "default_functions.hpp"

WindowScelta::WindowScelta(int n, string Name) {
  name=Name;
  numChoices = n;
  y=10;
  x=20;
  win = standard_win(y, x);
  keypad(win, true);
  box(win, 0, 0);
  wrefresh(win);

  pointing = 0;
};

// window che fa il display a seconda del numero delle opzioni
int WindowScelta::windowDisplay(string Op[], int length, int punteggio){
  curs_set(0);
  wclear(win);
  //wrefresh(stdscr);
  box(win, 0, 0);
  int end_loop = false;
  while (end_loop != true) {
    mvwprintw(win, 0, 0, "%s", name.c_str());
    mvwprintw(win, 8, 2, "Punteggio: %d", punteggio);
    for (int i = 0; i < length; i++) {
      wattroff(win, A_REVERSE); // disattiva stili
      if (i == pointing) {
        wattron(win, A_REVERSE);
      }
      mvwprintw(win, i + 1, 2, "%s", Op[i].c_str());
      wattroff(win,A_REVERSE);
    }
    wrefresh(win);
    int ch = wgetch(win);
    switch (ch) {
      case KEY_UP:
        pointing--;
      if (pointing == -1) {
        pointing = length - 1;
      }
      break;
      case KEY_DOWN:
        pointing++;
      if (pointing >= length) {
        pointing = 0;
      }
      break;
      default:
        break;
    }

    if (ch == 10) { //invio premuto -> uscita ciclo
      end_loop = true;
    }

  }
  wclear(win);
  wrefresh(win);
  return pointing;
};