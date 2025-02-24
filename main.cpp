#include <iostream>
#include "menu_livelli.h"
#include <ncurses/ncurses.h>

int main() {
    plist mm = insert_livello(NULL, {1, 'f'});
    mm = insert_livello(mm, {2, 'f'});
    mm = insert_livello(mm, {3, 'm'});
    mm = insert_livello(mm, {4, 'm'});
    mm = insert_livello(mm, {5, 'h'});
    print_livelli(mm);
    return 0;
}