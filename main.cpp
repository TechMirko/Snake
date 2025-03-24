#include <iostream>

#include "PauseExit.h"
using namespace std;
#include <ncurses/ncurses.h>
#include <string>
#include "Snake.h"
#include "Board.h"
#include "menu.h"
#include "Constant.h"
#include "GameOver.h"
#include "default_functions.h"

// stampa della finestra di sfondo
void background(int row, int col) {
  WINDOW *sfondo = newwin(rows+8, cols+8, (LINES/2)-(rows/2)-4, (COLS/2)-(cols/2)-4);
  box(sfondo, 0, 0);
  refresh();
  char ch=' ';
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  wattron(sfondo,A_REVERSE);
  wattron(sfondo,A_BOLD);
  wattron(sfondo,COLOR_PAIR(1));
  // stampa righe sopra e sotto
  for (int i = 0; i < cols+6; i++) {
    for (int j = 0; j < rows+6; j++) {
      mvwprintw(sfondo, j+1, i+1, "%c", ch);
    }
  }
  //wattroff(sfondo,COLOR_PAIR(1));


  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  wattron(sfondo,COLOR_PAIR(1));
  mvwprintw(sfondo, rows/4, cols/2, "Menu");
  wattroff(sfondo,COLOR_PAIR(1));

  //wattroff(sfondo,A_BOLD);
  //wattroff(sfondo,A_REVERSE);

  wrefresh(sfondo);
}

int main(int argc, char *argv[]) {
    initscr();
    refresh();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    int punteggio=0, vel=5, liv=1;
    bool ricomincia=false;
    bool END=false, classific=false;
    const char* voices[3] = {"Nuova partita", "Visualizza classifica", "Esci"};
    char titolo[50] = "- MENU (seleziona una voce e premi invio) -";


    while (!END) {
        wrefresh(stdscr);

      	//menu principale del gioco
        if (!ricomincia){
            background(rows, cols);

            Menu menu_generale = Menu(voices, 3);
      		//Menu menu = Menu();          // << soluzione del non refresh da mirko
    		//menu.display();
            menu_generale.display(titolo);

            // ----- PARTE NUOVA CON CLASSE Levels ----- //
            int liv = lvs.get_livello_scelto();
            std::cout << "Livello scelto: " << liv << ", bonus = " << 
              lvs.get_bonus(liv) << ", velocita' =  " << lvs.get_velocita(liv)
               << ", valore della mela = " << lvs.get_valore_mela(liv);
            classific=menu_generale.classificaOpen;
            END=menu_generale.endGame;

            // aggiornato con utilizzo della classe levels
            mvprintw(0, 0, "%d", liv);
            //liv=lvs.get_bonus(livello_da_giocare);
            vel=lvs.get_velocita(liv);
		}
    	if (!END || classific) {
        	Board board = Board();	// da sistemare con le opzioni del menu di mirko

        	// devo mandargli velocita di gioco
        	punteggio=board.displaySnake(vel, liv);

            if (punteggio!=0) {

              update_file(punteggio);
            }

        	if (board.gameOver){
          		// gameOver
                clear();
                GameOver gameOver = GameOver();
                gameOver.display(punteggio);
                //wrefresh(stdscr);
                END=gameOver.endGame;
                ricomincia=gameOver.ricomincia;

                // salvataggio dati del livello finito
                // azzerare tutti i dati del giocatore

    		}else if (board.exitFromGame) END=true;
            //printw("ultimo punteggio: %d", punteggio);
     	}
        //wrefresh(stdscr);
        wclear(stdscr);
    }



    wrefresh(stdscr);



    getch();
    //delwin(board);
    endwin();
    return 0;
}
