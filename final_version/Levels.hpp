/*
    TODO: controllare con gra il numero del livello all'interno della board di gioco 
*/
#ifndef LEVELS_H
#define LEVELS_H

#include <iostream>

struct Livello {
    int numero;
    int velocita;
    int valore_mela; 
    double bonus;
};
struct Bilist {
    Livello liv;
    Bilist* prec;
    Bilist* next;
};
typedef Bilist* plist;

class Levels {
protected:
    plist ordered_insert(plist bilista, Livello l);
    plist crea_blista(plist bilista);
    int livello_scelto;
public:
    Levels();
    double get_bonus(int livello);
    int get_velocita(int livello);
    int get_valore_mela(int livello);
    int get_livello_scelto();
    void set_livello_selezionato(int livello);
};

extern Levels lvs;

#endif //LEVELS_H