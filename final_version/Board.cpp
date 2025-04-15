#include <iostream>
using namespace std;
#include <cmath>
#include <ctime>
#include <ncurses.h>
#include "Board.hpp"
#include "Constant.hpp"
#include "PauseExit.hpp"

Board::Board(): Snake::Snake(){  // costruttore
  Board::coordApple[0][0] = 0;
  Board::coordApple[0][1] = 0;
  generateApple();  // generatore casuale delle coordinate della mela
  gameOver = false;
  exitFromGame = false;
  // creazione delle finestre
  sfondo = newwin(rows+8+1, cols+8, xPosCenter-3, yPosCenter-3);
  win = newwin(rows+2, cols+2, xPosCenter, yPosCenter);
  keypad(win, true);
  // COLORI:
  init_pair(1, COLOR_RED, COLOR_BLACK);		// colore mela
  init_pair(2, COLOR_BLUE, COLOR_BLACK);	// colore scritte e serpente
  init_pair(3, COLOR_GREEN, COLOR_GREEN);	// colore sfondo
  init_pair(4, COLOR_WHITE, COLOR_BLACK);	// colore valori
  start_color();
  srand(time(0));
  duration=timeGame;
  wattroff(win, A_REVERSE);
  wattroff(sfondo, A_REVERSE);
  before = 0.0;
  timer = 0.0;
}

// cast del tempo e print
void Board::printTime(){
  mvwprintw(sfondo, 2, 9, "              ");
  wattron(sfondo,A_BOLD);
  wattron(sfondo,COLOR_PAIR(2));
  int min=((float)(timer)/CLOCKS_PER_SEC)*100/60;
  mvwprintw(sfondo, 2, 10, "%d min %d sec", min, (int)((float)(timer)/CLOCKS_PER_SEC*100)-60*min);
  wattroff(sfondo,COLOR_PAIR(2));
  wattroff(sfondo,A_BOLD);
}

// stampa della finestra di sfondo
void Board::backgroundPrint(){
  curs_set(0);
  char ch=' ';
  init_pair(3, COLOR_GREEN, COLOR_GREEN);     // colore dello sfondo
  wattron(sfondo, A_REVERSE);
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
  wattroff(sfondo, A_REVERSE);

  wattron(sfondo,COLOR_PAIR(1));
  mvwprintw(sfondo, 2, 4, " time: ");
  wattroff(sfondo,COLOR_PAIR(1));
}

// stampa dei dati del livello, punteggio aggiornato e velocità del serpente
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

// genera casualmente la posizione della mela
void Board::generateApple() {
    bool validPosition = false;

    // Verifica se la mela non si sovrappone al corpo del serpente
    while (!validPosition) {
        Board::coordApple[0][0] = rand() % rows;
        Board::coordApple[0][1] = rand() % cols;

        validPosition = !(matrix[coordApple[0][0]][coordApple[0][1]] == 1);
    }
}


// fa il display della mela
void Board::displayApple(){
  curs_set(0);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  wattron(win,COLOR_PAIR(1));
  mvwprintw(win, coordApple[0][0]+1, coordApple[0][1]+1, "$");
  wattroff(win,COLOR_PAIR(1));

}

// stampa l'area di gioco : serpente e mela
void Board::displayBoard(int& punteggio, int speed, int level, int valMela){
    curs_set(0);
    box(sfondo, 0, 0);
    box(win, 0, 0);
    printDati(level, punteggio, speed);

    char ch;
    bool found=false;
    // stampa del serpente e della mela controllando i dati della matrice
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
                  punteggio= punteggio + valMela;
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
            // stampa del carattere a seconda dei valori in matrice
            init_pair(2, COLOR_BLUE, COLOR_BLACK);
            wattron(win, A_BOLD);
            wattron(win,COLOR_PAIR(2));
            mvwprintw(win, i+1, j+1, "%c", ch);
            wattroff(win, COLOR_PAIR(2));
            wattroff(win, A_REVERSE);
            wattroff(win, A_BOLD);
        }
    }
    // se la mela non è stata mangiata viene stampata (se no sovrapporrebbe al serpente)
    if (!found) Board::displayApple();
    wrefresh(sfondo);
    wrefresh(win);
}

// avvia il gioco con risposta ai movimenti dati dall'utente
// vengono presi in input velocità, num livello e il valore della mela
int Board::displaySnake(int vel, int level, int valMela){
    curs_set(0);
    halfdelay(vel);
    int direction = 2;
    bool end = false, timeFinish=false;
    int ch, punteggio=0, sceltaPausa=0;

    // print dello sfondo
    backgroundPrint();
    before=clock();   // inizio del conto del tempo di gioco
    while (!end && !timeFinish) {
        ch = wgetch(win);
        refresh();
        if (Position::Dups() == true) {
          //serpente morto
          end = true;
          gameOver = true;
          refresh();
        } else if (ch == 16) {    
          // ctrl P che mette in pausa
          PauseExit pause = PauseExit();
          sceltaPausa=pause.display(punteggio);

          if (sceltaPausa==0 || sceltaPausa==1) {		// scelta della finestra pausa
            //Riprendi
            end = false;
            //Ricomincia
            if (sceltaPausa==1) {
              before=clock();   // ricomincia il tempo
              generateApple();  // si generano nuove coordinate
              punteggio=0;      // si azzera il punteggio
            }
          }else{
            // Torna a Menu
            end = true;
            punteggio=0;  // non si salva in classifica
            // Esci
            if (sceltaPausa==3) exitFromGame = true;
          }
          refresh();
        } else {
            if (ch != ERR) {
                switch (ch) {     // controllo che il serpente non colpisca la sua coda
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
            }   // movimento a seconda della chiave data in tastiera
            if (direction == 1){
                Snake::moveup();    // movimenti gestiti in Snake.hpp
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
        // stampa aggiornata del movimento effettuato
        displayBoard(punteggio, vel, level, valMela);
        napms(200);
        timer = clock() - before;
        if ( (float)timer/CLOCKS_PER_SEC > duration ) {
          timeFinish=true;
          gameOver=true;
        }
        // stampa aggiornata del tempo
        printTime();
    }
    cbreak();
    return punteggio;
}