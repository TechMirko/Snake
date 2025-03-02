#ifndef MENU_H
#define MENU_H

/*
* TODO: iniziare a gestire i file dei livelli
*/
#include <ncurses/ncurses.h>
#include "menu.h"
#include "costanti.h"


/* ----- DICHIARAZIONI E FUNZIONI PER LA LISTA ----- */
struct Livello {
    int numero;
};
struct Bilist {
    Livello liv;
    Bilist* prec;
    Bilist* next;
};
typedef Bilist* plist;

plist ordered_insert(plist bilista, Livello l);
plist crea_blista(plist bilista);

/* ----- DICHIARAZIONE DELLA CLASSE MENU ----- */
class Menu {
protected:
    int voci_totali = 0;
    const char* voci[MAX_VOCI];
    void check_scelta(WINDOW* win, int highlight);
    void scelta_classifica(WINDOW* win);
    void scelta_partita();
    void prova_per_livello(int livello);
public:
    Menu(const char* v[], int n_voci = 0);
    void display(char title[]);
    void get_voce(char level[], int index);
};

/* ----- DICHIARAZIONE FUNZIONI AUSILIARIE ----- */
void print_from_file(WINDOW* w, char file_name[]);
void print_from_list(WINDOW* w, plist list, int rows);

#endif //MENU_H
