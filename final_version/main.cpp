#include <iostream>

#include "PauseExit.hpp"
using namespace std;
#include <ncurses.h>
#include <string>
#include "Snake.hpp"
#include "Board.hpp"
#include "menu.hpp"
#include "Constant.hpp"
#include "GameOver.hpp"
#include "default_functions.hpp"

// stampa della finestra di sfondo
void background(int row, int col) {
  WINDOW *sfondo = newwin(rows+8, cols+8, (LINES/2)-(rows/2)-4, (COLS/2)-(cols/2)-4);
  box(sfondo, 0, 0);
  refresh();

  mvwprintw(sfondo, rows/4, cols/2, "Menu");
  wrefresh(sfondo);
}

int main(int argc, char *argv[]) {
  // inizializzazione di ncurses
  initscr();
  refresh();
  noecho();
  curs_set(0);
  keypad(stdscr, true);
  int punteggio=0, vel=2, level=1, valMela=2, bonus=10;
  bool ricomincia=false;
  bool END=false, classific=false;
  const char* voices[3] = {"Nuova partita", "Visualizza classifica", "Esci"};
  char titolo[50] = "- MENU (seleziona una voce e premi invio) -";

  while (!END) {
    wrefresh(stdscr);

    //menu principale del gioco
    if (!ricomincia){
      // stampa dello sfondo
      background(rows, cols);
      
      //menu
      Menu menu_generale = Menu(voices, 3);
      menu_generale.display(titolo);

      // salvataggio della scelta fatta nel menu
      int liv = lvs.get_livello_scelto();
      classific=menu_generale.classificaOpen;   // true se si è scelta classifica da vedere
      END=menu_generale.endGame;

      // aggiornato con utilizzo della classe levels
      mvprintw(0, 0, "%d", liv);
      level = lvs.get_livello_scelto();
      vel = lvs.get_velocita(liv);
      valMela = lvs.get_valore_mela(liv);
      bonus = lvs.get_bonus(liv);
    }
    if (!END && !classific) {
      // area di gioco
      clear();
      Board board = Board();
      punteggio=board.displaySnake(vel, level, valMela);

      // aggiornamento della classifica
      if (punteggio!=0) {
        punteggio=punteggio*bonus;
        time_t now; time(&now);
        update_file(punteggio, now);
      }
      // schermata di game over chiamata da una scelta in board
      if (board.gameOver){
        // gameOver
        clear();
        GameOver gameOver = GameOver();
        gameOver.display(punteggio);
        END=gameOver.endGame;
        ricomincia=gameOver.ricomincia;
      }else if (board.exitFromGame) END=true;
    }
    wclear(stdscr);
  }
  wrefresh(stdscr);

  getch();
  endwin();
  return 0;
}
