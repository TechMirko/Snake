//
// Costanti generali del gioco usate da tutte le classi
//

#ifndef CONSTANT_H
#define CONSTANT_H

#ifdef _WIN32
    #ifdef __MINGW32__
        #include <ncurses/ncurses.h> // Windows con MinGW
    #else
        #include <ncurses.h>         // Windows con WSL
    #endif
#else
    #include <ncurses.h>             // Linux e macOS
#endif

// dimensioni finestra di gioco
#define rows 30
#define cols 120
// lunghezza del serpente
#define snake_length 6
// posizioni centrate per la finestra di gioco
#define xPosCenter (LINES/2) - rows/2 -1
#define yPosCenter (COLS/2) - cols/2 -1

// numero di opzioni per finestre di pausa, game over e menu
#define pauseOptions 4
#define gameoverOptions 3
#define menu_options 3

// TEMPO DI GIOCO:
#define timeGame 0.7

// dimensioni e posizioni finestra del menu
#define rowMenu 10
#define colMenu 120
#define xP_menu (LINES/2) - rowMenu/2 -1
#define yP_menu (COLS/2) - colMenu/2 -1

// massimo delle voci possibili in un menù
#define MAX_VOCI 10

// costanti necessarie alla verifica della selezione nel menù
#define VOCE_CLASSIFICA "Visualizza classifica"
#define VOCE_NUOVA_PARTITA "Nuova partita"
#define VOCE_ESCI "Esci"

// costanti necessarie alla verifica della scelta del livello
#define MAX_LIVELLI 5
#define LIVELLO_1 "Livello 1"
#define LIVELLO_2 "Livello 2"
#define LIVELLO_3 "Livello 3"
#define LIVELLO_4 "Livello 4"
#define LIVELLO_5 "Livello 5"

#endif //CONSTANT_H
