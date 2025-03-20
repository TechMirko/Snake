#include <iostream>
using namespace std;
#include <cmath>
#include <ctime>
#include <ncurses/ncurses.h>
#include "Board.h"
#include "Constant.h"
#include "PauseExit.h"

Board::Board(): Snake::Snake(){  // >>
  Board::coordApple[0][0] = 0;
  Board::coordApple[0][1] = 0;
  generateApple();
  gameOver = false;
  exitFromGame = false;
  sfondo = newwin(rows+8+1, cols+8, xPosCenter-3, yPosCenter-3);
  win = newwin(rows+2, cols+2, xPosCenter, yPosCenter);
  keypad(win, true);
  init_pair(1, COLOR_RED, COLOR_BLACK);		// colore mela
  init_pair(2, COLOR_BLUE, COLOR_BLACK);	// colore scritte e serpente
  init_pair(3, COLOR_BLACK, COLOR_WHITE);	// colore sfondo
  init_pair(4, COLOR_WHITE, COLOR_BLACK);	// colore valori
  start_color();
  srand(time(0));
}

// stampa della finestra di sfondo
void Board::backgroundPrint(){
  char ch=' ';
  wattron(sfondo,A_REVERSE);
  wattron(sfondo,A_BOLD);
  wattron(sfondo,COLOR_PAIR(3));
  // stampa righe sopra e sotto
  for (int i = 0; i < cols+6; i++) {
    for (int j = 0; j < 2; j++) {
      mvwprintw(sfondo, j+1, i+1, "%c", ch);
      mvwprintw(sfondo, rows+4+j+1, i+1, "%c", ch);
    }
  }
  // stampa colonne laterali
  for (int i = 0; i < rows+6; i++) {
    for (int j = 0; j < 2; j++) {
      mvwprintw(sfondo, i+1, j+1, "%c", ch);
      mvwprintw(sfondo, i+1, cols+4+j+1, "%c", ch);
    }
  }
  wattroff(sfondo,COLOR_PAIR(3));
  wattroff(sfondo,A_BOLD);
  wattroff(sfondo,A_REVERSE);
}

void Board::printDati(int level, int score, int speed){
  wattron(sfondo,COLOR_PAIR(2));
  wattron(sfondo,A_BOLD);
  mvwprintw(sfondo, rows+7, 3, "Level: ");
  mvwprintw(sfondo, rows+7, cols/2-2, "Score: ");
  mvwprintw(sfondo, rows+7, cols-11, "Speed: ");
  wattroff(sfondo,COLOR_PAIR(2));


  wattron(sfondo,COLOR_PAIR(4));
  mvwprintw(sfondo, rows+7, 3+7, "%d", level);
  mvwprintw(sfondo, rows+7, cols/2+10-4, "%d", score);
  mvwprintw(sfondo, rows+7, cols-3, "%d", speed);
  wattroff(sfondo,COLOR_PAIR(4));
  wattroff(sfondo,A_BOLD);
}

// genera casualmente la posizione di $
// modifica alla funzione generateApple
void Board::generateApple() {
    bool validPosition = false;

    while (!validPosition) {
        Board::coordApple[0][0] = rand() % rows;
        Board::coordApple[0][1] = rand() % cols;

        // Verifica se la mela non si sovrappone al corpo del serpente
        validPosition = !(matrix[coordApple[0][0]][coordApple[0][1]] == 1);
    }
}


// fa il display della $
void Board::displayApple(){        // >>
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  wattron(win,COLOR_PAIR(1));
  mvwprintw(win, coordApple[0][0]+1, coordApple[0][1]+1, "$");
  wattroff(win,COLOR_PAIR(1));

}

// stampa l'area di gioco : serpente e mela
void Board::displayBoard(int& punteggio, int speed, int level){        // >>
    box(sfondo, 0, 0);
    box(win, 0, 0);
    //backgroundPrint();
    printDati(level, punteggio, speed);

    char ch;
    bool found=false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          	wattron(win,A_REVERSE);
            if (matrix[i][j] == true) {
              ch='o';
              if (head_row==i && head_col==j){
                ch = '@';
              }
              if (head_row==coordApple[0][0] && head_col==coordApple[0][1]) {
                  // mela trovata
                  Board::generateApple();
                  found=true;

                  // incremento punteggio
                  punteggio++;
              }
            }else{
              wattroff(win, A_REVERSE);
              ch=' ';
            }
			if (!found) {
              // mela trovata
              wattroff(win, A_REVERSE);			// evidenzio il serpente
              found=false;
            }
            init_pair(2, COLOR_BLUE, COLOR_BLACK);
            wattron(win, A_BOLD);
            wattron(win,COLOR_PAIR(2));
            mvwprintw(win, i+1, j+1, "%c", ch);
            wattroff(win, COLOR_PAIR(2));
            wattroff(win, A_REVERSE);
            wattroff(win, A_BOLD);
        }
    }
    if (!found) Board::displayApple(); // se la mela non è stata mangiata (se no sovrapporrebbe al serpente)
    wrefresh(sfondo);
    wrefresh(win);
}

// avvia il gioco con risposta ai movimenti dati dall'utente
int Board::displaySnake(int vel, int level){
    curs_set(0);
    halfdelay(vel);        // ciò che dipende dal livello
    int direction = 2;
    bool end = false;
    int ch, punteggio=0, sceltaPausa=0;
    backgroundPrint();
    while (!end) {
        ch = wgetch(win);
        if (Position::Dups() == true) {        // dups controlla se snake ha colpito se stesso
            end = true;
            //mvprintw(0, 0, "%s", "MORTO! - SERPENTE SI E' MORSO");
            gameOver = true;
            refresh();
        } else if (ch == 16) {    // ctrl P che mette in pausa

            PauseExit pause = PauseExit();
            sceltaPausa=pause.display(punteggio);

            if (sceltaPausa==0 || sceltaPausa==1) {		// >>
              //Riprendi
              end = false;
              //Ricomincia
              if (sceltaPausa==1) {
                //mvprintw(0, 0, "%s", "punteggio a 0");
                generateApple();
                punteggio=0;
              }
            }else{
              // Torna a Menu
              end = true;
              // Esci
              if (sceltaPausa==3) exitFromGame = true;
            }

            refresh();
        } else {
            if (ch != ERR) {
                switch (ch) {
                    case KEY_UP:
                        if (direction != -1){ direction = 1;}
                        end = Position::Dups();
                    break;
                    case KEY_DOWN:
                        if (direction != 1){ direction = -1;}
                        end = Position::Dups();
                    break;
                    case KEY_LEFT:
                        if (direction != 3){ direction = 2;}
                        end = Position::Dups();
                    break;
                    case KEY_RIGHT:
                        if (direction != 2){ direction = 3;}
                        end = Position::Dups();
                    break;
                    default:
                        break;
                }
            }
            if (direction == 1){
                Snake::moveup();

            }
            else if (direction == -1){
                Snake::movedown();
            }
            else if (direction == 2){
                Snake::moveleft();
            }
            else if (direction == 3){
                Snake::moveright();
            }
        }
        mvwprintw(win, 0, 0, "%d", coordApple[0][0]);
        displayBoard(punteggio, vel, level);
        napms(200);
    }
    return punteggio;
}