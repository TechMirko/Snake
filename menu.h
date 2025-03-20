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
#include "costanti.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>

using namespace std;


/* ----- DICHIARAZIONI E FUNZIONI PER LA LISTA DEI LIVELLI ----- */
struct Livello {
    int numero;
    int velocita;
};
struct Bilist {
    Livello liv;
    Bilist* prec;
    Bilist* next;
};
typedef Bilist* plist;

/**
 * @param bilista lista bidirezionale dei livelli
 * @param l livello da aggiungere
 * @return lista aggiornata
 */
plist ordered_insert(plist bilista, Livello l);

/**
 * @param bilista lista bidirezionale dei livelli
 * @return lista aggiornata completa dei livelli
 */
plist crea_blista(plist bilista);

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
    void prova_per_livello(int livello);
public:
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

    /**
     * @param punteggio punteggio totalizzato durante la paratita
     */
    void update_file(int punteggio);
};

/* ----- DICHIARAZIONE FUNZIONI AUSILIARIE ----- */
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
void print_from_list(WINDOW* w, plist list, int rows);

/* ----- LISTA PER AGGIORNARE FILE ----- */
struct ClassificaNode {
    int punteggio;
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
clist ordered_insert(clist lista, int punteggio);

#endif //MENU_H
