#include "menu.h"
#include <fstream>
#include <cstring>

plist lista_livelli = NULL;

/* ----- IMPLEMENTAZIONE FUNZIONI LISTA BIDIREZIONALE ----- */
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

plist crea_blista(plist bilista) {
    const int livelli[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        Livello l = {livelli[i]};
        bilista = ordered_insert(bilista, l);
    }
    return bilista;
}

/* ----- IMPLEMENTAZIONE FUNZIONI AUSILIARIE ----- */
void print_from_file(WINDOW* win, char file_name[]) {
    initscr();
    noecho();
    wattroff(win, A_REVERSE); // disattiva stili
    std::fstream file;
    file.open(file_name);
    char ch[256];
    int riga = 3;

    // l'altezza è: numero righe + 2
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "Classifica:");
    refresh();
    wrefresh(win);

    while (file.getline(ch, sizeof(ch))) {
        mvwprintw(win, riga, 1, "%s", ch);
        refresh();
        wrefresh(win);
        riga++;
    }
    getch();
    file.close();
}

void print_from_list(WINDOW* win, plist list, const int rows) {
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

    for (int i = 0; i < rows; i++) {
        mvwprintw(win, riga, 1, "Livello %d", i + 1);
        riga++;
        refresh();
        wrefresh(win);
    }
    getch();
}

/* ----- IMPLEMENTAZIONE CLASSE ----- */
Menu::Menu(const char* v[], int n_voci) {
    lista_livelli = crea_blista(lista_livelli);
    for (int i = 0; i < n_voci; i++) {
        voci[i] = v[i];
        voci_totali++;
    }
}

void Menu::get_voce(char level[], const int index) {
    strcpy(level, voci[index]);
}

void Menu::scelta_classifica(WINDOW* win) {
    char nome_file[40] = "test.txt";
    print_from_file(win, nome_file);
}

void Menu::scelta_partita() {
    // costruisco il menu dei livelli
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
    endwin();
}

void Menu::check_scelta(WINDOW* win, const int highlight) {
    char selected[30];
    get_voce(selected, highlight);
    if (strcmp(selected, VOCE_CLASSIFICA) == 0) {
        scelta_classifica(win);
    } else if (strcmp(selected, VOCE_NUOVA_PARTITA) == 0) {
        scelta_partita();
    } else if (strcmp(selected, LIVELLO_1) == 0 || strcmp(selected, LIVELLO_2) == 0 ||
        strcmp(selected, LIVELLO_3) == 0 || strcmp(selected, LIVELLO_4) == 0 ||
            strcmp(selected, LIVELLO_5) == 0) {
        prova_per_livello(highlight + 1);
    }
}

void Menu::display(char title[]) {
    initscr();
    noecho();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // newwin(altezza, larghezza, inizio_Y, inizio_X)
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
    check_scelta(menu, highlight);
    endwin();
}


