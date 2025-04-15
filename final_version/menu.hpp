#ifndef MENU_H
#define MENU_H

/**
 * Controllo su che sistema operativo viene eseguito il programma e,
 * in base all'esito, cambio l'import della libreria per adattarsi a
 * MINGW, WSL, UNIX (Linux e MacOS)
*/

#ifdef _WIN32
    #ifdef __MINGW32__
        #include <ncurses/ncurses.h> // Windows con MinGW
    #else
        #include <ncurses.h>         // Windows con WSL
    #endif
#else
    #include <ncurses.h>             // Linux e macOS
#endif

// Librerie necessarie in tutto il programma
#include "Constant.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include "Levels.hpp"

using namespace std;

/* ----- DICHIARAZIONE DELLA CLASSE MENU ----- */
class Menu {
protected:
    int voci_totali = 0;
    const char* voci[MAX_VOCI];

    /**
     * @param win finestra di gioco con parametri sempre uguali
     * @param highlight elemento selezionato
     */
    void check_scelta(WINDOW* win, int highlight);

    /**
     * @param win finestra di gioco con parametri sempre uguali
     */
    void scelta_classifica(WINDOW* win);
    void scelta_partita();
    void prova_per_livello(int livello, WINDOW *win);
public:
    bool classificaOpen, endGame;
    /**
     * @param v array delle voci del menu
     * @param n_voci numero delle voci presenti nel menu
     */
    Menu(const char* v[], int n_voci = 0);

    /**
     * @param title titolo della finestra da visualizzare
     */
    void display(char title[]);

    /**
     * @param level array nel quale si vuole copiare il NOME del livello
     * @param index indice dell'array da cui proviene
     */
    void get_voce(char level[], int index);
};

/* ----- DICHIARAZIONE FUNZIONI AUSILIARIE ----- */

/**
* @param punteggio punteggio totalizzato durante la paratita
*/
void update_file(int punteggio, time_t data);

/**
 * @param w finestra di gioco con parametri sempre uguali
 * @param file_name nome del file da cui deve andare a leggere la classifica
 */
void print_from_file(WINDOW* w, char file_name[]);

/**
 * @param w finestra di gioco con parametri sempre uguali
 * @param list lista con i livelli da selezionare
 * @param rows numero di righe da stampare (serve per le dimensione della box)
 */
void print_from_list(WINDOW* w, plist list, int rowss);

/* ----- LISTA PER AGGIORNARE FILE ----- */
struct ClassificaNode {
    int punteggio;
    time_t data;
    ClassificaNode* next;
};
typedef ClassificaNode* clist;

/**
 * @param nome_file nome del file della classifica
 * @param lista lista nella quale vogliamo mettere i livelli
 * @return lista aggiornata (completa)
 */
clist crea_lista(char nome_file[], clist lista);

/**
 * @param lista lista alla quale aggiungere un elemento
 * @param punteggio totale del punteggio realizzato
 * @return lista aggiornata in modo ordinato
 */
clist ordered_insert(clist lista, int punteggio, time_t data);

/**
 * Funzione necessaria per il parsing della data per la stampa della classifica
 * con anche la data nella quale si è ottenuto il punteggio
 * @param mese viene passato il mese nel formato "Jan" o "Dec"
 * @return numero del mese: 0 = gennaio, ... , 11 = dicembre
 */
int mese_da_nome(const char* mese);
#endif //MENU_H