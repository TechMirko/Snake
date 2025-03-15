// TODO: endgame menu
#include "menu.h"

plist lista_livelli = NULL;

/* ----- IMPLEMENTAZIONE FUNZIONI LISTA BIDIREZIONALE ----- */

/**
 * @param bilista lista bidirezionale dei livelli
 * @param l livello da aggiungere
 * @return lista aggiornata
 */
plist ordered_insert(plist bilista, const Livello l) {
    // Caso base: lista vuota, crea il primo nodo
    if (bilista == NULL) {
        plist new_element = new Bilist;
        new_element->liv = l;
        new_element->next = NULL;
        new_element->prec = NULL;
        return new_element;
    }

    // Se il nuovo livello ha numero maggiore, prosegui ricorsivamente
    if (bilista->liv.numero < l.numero) {
        bilista->next = ordered_insert(bilista->next, l);
        if (bilista->next) // Aggiorna il puntatore prec del nuovo nodo
            bilista->next->prec = bilista;
        return bilista;
    }

    // Creazione nuovo nodo prima di bilista
    plist new_element = new Bilist;
    new_element->liv = l;
    new_element->next = bilista;
    new_element->prec = bilista->prec; // Mantieni il precedente attuale

    // Aggiorna il precedente del nodo attuale
    bilista->prec = new_element;

    return new_element; // Nuovo nodo diventa la nuova testa della lista
}

/**
 * @param bilista lista bidirezionale dei livelli
 * @return lista aggiornata completa dei livelli
 */
plist crea_blista(plist bilista) {
    const int livelli[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        Livello l = {livelli[i]};
        bilista = ordered_insert(bilista, l);
    }
    return bilista;
}

/* ----- IMPLEMENTAZIONE FUNZIONI AUSILIARIE ----- */

/**
 * @param win finestra di gioco con parametri sempre uguali
 * @param file_name nome del file da cui deve andare a leggere la classifica
 */
void print_from_file(WINDOW* win, char file_name[]) {
    initscr();
    noecho();
    wattroff(win, A_REVERSE); // disattiva stili
    std::fstream file; // apertura file da leggere
    file.open(file_name);
    char ch[256];
    int riga = 3;

    // l'altezza è: numero righe + 2
    werase(win); // ripulisco finestra

    // stampa della finestra
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "Classifica:");
    refresh();
    wrefresh(win);

    while (file.getline(ch, sizeof(ch))) { // scrivo riga per riga della classifica
        mvwprintw(win, riga, 1, "%s", ch);
        refresh();
        wrefresh(win);
        riga++;
    }
    getch();
    file.close();
}

/**
 * @param win finestra di gioco con parametri sempre uguali
 * @param list lista con i livelli da selezionare
 * @param rows numero di righe da stampare (serve per le dimensione della box)
 */
void print_from_list(WINDOW* win, plist list, const int rows) {
    // preparazione della stampa del menu dei livelli
    plist tmp = list;
    int levels[rows], counter = 0;
    for (int i = 0; i < rows; i++) levels[i] = 0;
    while (tmp != NULL) {
        levels[counter] = tmp->liv.numero;
        tmp = tmp->next;
    }

    initscr();
    noecho();
    wattroff(win, A_REVERSE); // disattiva stili
    char ch[256];
    int riga = 3;

    // l'altezza è: numero righe + 2
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "Seleziona livello:");
    refresh();
    wrefresh(win);

    // stampa delle voci del menu
    for (int i = 0; i < rows; i++) {
        mvwprintw(win, riga, 1, "Livello %d", i + 1);
        riga++;
        refresh();
        wrefresh(win);
    }
    getch();
}

/* ----- IMPLEMENTAZIONE CLASSE ----- */

/**
 * @param v array delle voci del menu
 * @param n_voci numero delle voci presenti nel menu
 */
Menu::Menu(const char* v[], int n_voci) {
    lista_livelli = crea_blista(lista_livelli); // crea la lisra dei livelli
    for (int i = 0; i < n_voci; i++) { // colleziona le voci del menu
        voci[i] = v[i];
        voci_totali++;
    }
}

/**
 * @param level array nel quale si vuole copiare il NOME del livello
 * @param index indice dell'array da cui proviene
 */
void Menu::get_voce(char level[], const int index) {
    strcpy(level, voci[index]);
}

/**
 * @param win finestra di gioco con parametri sempre uguali
 */
void Menu::scelta_classifica(WINDOW* win) {
    // se si sceglie di aprire la classifica, chiamo la funzione apposita
    char nome_file[40] = "classifica.txt";
    print_from_file(win, nome_file);
}

/**
 * Funzioni di appoggio per leggere il contenuto della classifica e, successivamente,
 * inserire in maniera ordinata il nuovo punteggio.
 *
 * @param lista lista alla quale aggiungere un elemento
 * @param punteggio totale del punteggio realizzato
 * @return lista aggiornata in modo ordinato
 */
clist ordered_insert(clist lista, int punteggio) {
    if (lista == NULL) {
        clist n = new ClassificaNode;
        n->punteggio = punteggio;
        n->next = NULL;
        return n;
    }

    // Correzione: Se il nuovo punteggio è maggiore, lo inserisco prima
    if (punteggio > lista->punteggio) {
        clist new_element = new ClassificaNode;
        new_element->punteggio = punteggio;
        new_element->next = lista;
        return new_element;  // Il nuovo elemento diventa la nuova testa
    }

    // Se il nuovo punteggio è minore, proseguo ricorsivamente
    lista->next = ordered_insert(lista->next, punteggio);
    return lista;
}

/**
 * Crea la lista leggendo i valori e chiamando la funzione di inserimento ordinato
 *
 * @param nome_file nome del file della classifica
 * @param lista lista nella quale vogliamo mettere i livelli
 * @return lista aggiornata (completa)
 */
clist crea_lista(char nome_file[], clist lista) {
    // creo una lista di appoggio per inserire correttamente il nuovo punteggio
    // leggendo prima i punteggi precedenti salvati nel file
    ifstream file_classifica(nome_file);
    if (!file_classifica) {
        cerr << "Errore: impossibile aprire il file " << nome_file << endl;
        return lista; // Ritorna la lista vuota se il file non esiste
    }

    // creo la lista con ogni elemento del file
    int punto;
    while (file_classifica >> punto) {
        lista = ordered_insert(lista, punto);
    }
    file_classifica.close();
    return lista;
}

/**
 * Funzione che viene chiamata dopo aver giocato un livello ed aggiorna
 * il file con la classifica dei punteggi
 *
 * @param punteggio punteggio totalizzato durante la paratita
 */
void Menu::update_file(const int punteggio) {
    // lettura del file ed inserimento dei livelli all'interno di una lista
    char nome_file[50] = "classifica.txt";
    clist lista = crea_lista(nome_file, NULL);
    lista = ordered_insert(lista, punteggio);

    // riscrittura del file
    ofstream file(nome_file, ios::trunc); // Svuota e riscrive
    if (!file) {
        cerr << "Errore: impossibile aprire il file!" << endl;
        return;
    }
    while (lista != NULL) {
        file << lista->punteggio << endl;
        lista = lista->next;
    }
    file.close();
}

void Menu::scelta_partita() {
    // costruisco il menu dei livelli se si sceglie di iniziare una nuova partita
    const char* voci[MAX_LIVELLI] = {"Livello 1", "Livello 2", "Livello 3", "Livello 4", "Livello 5"};
    char titolo[50] = "- MENU LIVELLI (seleziona e premi invio) -";
    Menu menu_livelli = Menu(voci, MAX_LIVELLI);
    menu_livelli.display(titolo);
}

void Menu::prova_per_livello(const int livello) {
    initscr();
    noecho();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // newwin(altezza, larghezza, inizio_Y, inizio_X)
    WINDOW *menu = newwin(10, xMax/2, yMax/4, xMax/4);
    werase(menu);
    box(menu, 0, 0);
    refresh();
    wrefresh(menu);
    mvwprintw(menu, 1, 8, "- LIVELLO %d", livello);
    refresh();
    wrefresh(menu);
    getch();
    // aggiorno il file con l'ultimo punteggio ottenuto
    srand(time(NULL));
    update_file(1 + rand() % 500);
    endwin();
}

/**
 * Funzione generica che serve sia per il menu della classifica che per
 * il menu della scelta dei livelli.
 * @param win finestra di gioco con parametri sempre uguali
 * @param highlight elemento selezionato
 */
void Menu::check_scelta(WINDOW* win, const int highlight) {
    // salvo in "selected" la voce scelta da qualsiasi menu
    char selected[30];
    get_voce(selected, highlight);
    if (strcmp(selected, VOCE_CLASSIFICA) == 0) { // visualizzazione classifica
        scelta_classifica(win);
    } else if (strcmp(selected, VOCE_NUOVA_PARTITA) == 0) { // nuova partita
        scelta_partita();
    } else if (strcmp(selected, LIVELLO_1) == 0 || strcmp(selected, LIVELLO_2) == 0 ||
        strcmp(selected, LIVELLO_3) == 0 || strcmp(selected, LIVELLO_4) == 0 ||
            strcmp(selected, LIVELLO_5) == 0) { // controllo la scelta del livello
        prova_per_livello(highlight + 1);
    }
}

/**
 * @param title titolo della finestra da visualizzare
 */
void Menu::display(char title[]) {
    initscr();
    noecho();

    // raccoglie informazioni dello schermo utili nella creazione della finestra
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // newwin(altezza, larghezza, inizio_Y, inizio_X)
    // crea una finestra centrata nello schermo
    WINDOW *menu = newwin(10, xMax/2, yMax/4, xMax/4);
    box(menu, 0, 0);
    refresh();
    wrefresh(menu);
    mvwprintw(menu, 1, 8, title);

    keypad(menu, true);
    int highlight = 0;
    bool exit = false;
    while (!exit) {
        for (int i = 0; i < voci_totali; i++) {
            char voce[50];
            wattroff(menu, A_REVERSE); // disattiva stili
            if (i == highlight) // se l'elemento è selezionato, evidenzialo
                wattron(menu, A_REVERSE);
            get_voce(voce, i);
            mvwprintw(menu, i+3, 1, voce);
            wattron(menu, A_REVERSE);
        }
        const int choice = wgetch(menu); // controllo se e cosa viene premuto
        switch (choice) {
            case KEY_UP:
                if (highlight > 0)
                    highlight--;
            break;
            case KEY_DOWN:
                if (highlight < voci_totali - 1)
                    highlight++;
            break;
            case 10:
                exit = true;
            break;
            default:
                break;
        }
        if (choice == 10) exit = true;
    }
    check_scelta(menu, highlight); // controllo la scelta effettuata
    endwin();
}


