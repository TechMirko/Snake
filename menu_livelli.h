#ifndef MENU_LIVELLI_H
#define MENU_LIVELLI_H

#include <ncurses/ncurses.h>
#include <iostream>
using namespace std;

struct livello {
    int numero;
    char difficolta;
};

struct menu {
    livello l;
    menu* prec;
    menu* next;
};
typedef menu* plist;

plist insert_livello(plist m, livello liv);
void print_livelli(plist l);

#endif //MENU_LIVELLI_H
