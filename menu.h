#ifndef MENU_H
#define MENU_H

/*
* TODO: iniziare a gestire i file dei livelli
*/
#include <ncurses/ncurses.h>
#include "menu.h"
#include "costanti.h"
#include <iostream>
#include <fstream>
#include <ctime>


/* ----- DICHIARAZIONI E FUNZIONI PER LA LISTA DEI LIVELLI ----- */
struct Livello {
    int numero;
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
 *
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
    //void update_file(double data, int punteggio);
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

#endif //MENU_H
