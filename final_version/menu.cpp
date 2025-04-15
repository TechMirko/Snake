#include "menu.hpp"
#include "Levels.hpp"

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
    while (file.getline(ch, sizeof(ch))) {      
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
void print_from_list(WINDOW* win, plist list, const int rowss) {
    // preparazione della stampa del menu dei livelli
    plist tmp = list;
    int levels[rowss], counter = 0;
    for (int i = 0; i < rowss; i++) levels[i] = 0;
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
    for (int i = 0; i < rowss; i++) {
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
    for (int i = 0; i < n_voci; i++) { // colleziona le voci del menu
        voci[i] = v[i];
        voci_totali++;
    }

    classificaOpen = false;
    endGame = false;
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
    classificaOpen = true;
}

/**
 * Funzioni di appoggio per leggere il contenuto della classifica e, successivamente,
 * inserire in maniera ordinata il nuovo punteggio.
 *
 * @param lista lista alla quale aggiungere un elemento
 * @param punteggio totale del punteggio realizzato
 * @return lista aggiornata in modo ordinato
 */
clist ordered_insert(clist lista, int punteggio, time_t data) {
    if (lista == NULL) {
        clist n = new ClassificaNode;
        n->punteggio = punteggio;
        n->data = data;
        n->next = NULL;
        return n;
    }

    // Correzione: Se il nuovo punteggio è maggiore, lo inserisco prima
    if (punteggio > lista->punteggio) {
        clist new_element = new ClassificaNode;
        new_element->punteggio = punteggio;
        new_element->data = data;
        new_element->next = lista;
        return new_element;  // Il nuovo elemento diventa la nuova testa
    }

    // Se il nuovo punteggio è minore, proseguo ricorsivamente
    lista->next = ordered_insert(lista->next, punteggio, data);
    return lista;
}

// Funzione di supporto per convertire il nome del mese in numero (0 = Gennaio, ..., 11 = Dicembre)
int mese_da_nome(const char* mese) {
    const char* mesi[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    for (int i = 0; i < 12; ++i) {
        if (strcmp(mesi[i], mese) == 0)
            return i; // ritorna il numero del mese
    }
    return -1; // errore: mese non trovato
}

/**
 * Crea la lista leggendo i valori e chiamando la funzione di inserimento ordinato
 *
 * @param nome_file nome del file della classifica
 * @param lista lista nella quale vogliamo mettere i livelli
 * @return lista aggiornata (completa)
 */
clist crea_lista(char nome_file[], clist lista) {
    ifstream file_classifica(nome_file); // apre il file in lettura
    if (!file_classifica) {
        cerr << "Errore: impossibile aprire il file " << nome_file << endl;
        return lista; // se non esiste, ritorna la lista vuota
    }

    int punteggio; // per il punteggio
    char dash; // per il trattino "-"
    char giorno_sett[4]; // giorno della settimana (es. "Wed")
    char mese_str[4]; // mese (es. "Apr")
    int giorno; // giorno del mese
    int ore, minuti, secondi; // orario
    int anno; // anno

    // Cicla su ogni riga del file
    while (file_classifica >> punteggio >> dash) {
        file_classifica.get(); // salta lo spazio dopo il trattino
        
        // ----- LETTURA RIGA ----- //
        // Esempio riga: 4 - Wed Apr 09 10:01:26 2025
        // Estrae i componenti della data uno alla volta
        file_classifica >> giorno_sett >> mese_str >> giorno;
        file_classifica.ignore(); // salta spazio
        file_classifica >> ore; // ore
        file_classifica.ignore(); // salta ":"
        file_classifica >> minuti; // minuti
        file_classifica.ignore(); // salta ":"
        file_classifica >> secondi; // secondi
        file_classifica >> anno; // anno

        // Costruisce la struttura tm con i valori letti
        // tm è sempre una variabile per il tempo, ma a differenza di time_t che salva
        // il numero di millisecondi trascorsi da 01/01/1970, salva la data
        // in un formato leggibile e comprensibile
        struct tm tm_data = {};
        memset(&tm_data, 0, sizeof(tm_data));
        tm_data.tm_year = anno - 1900; // anno: 2025 -> 125
        tm_data.tm_mon = mese_da_nome(mese_str); // mese: "Apr" -> 3
        tm_data.tm_mday = giorno;
        tm_data.tm_hour = ore;
        tm_data.tm_min = minuti;
        tm_data.tm_sec = secondi;

        // Converte tm in time_t
        //time_t data = timegm(&tm_data); //per MAC/Linux/WSL
        time_t data = mktime(&tm_data);
        // Inserisce ordinatamente nella lista
        lista = ordered_insert(lista, punteggio, data);
    }

    file_classifica.close(); // chiude il file
    return lista;
}

/**
 * Funzione che viene chiamata dopo aver giocato un livello ed aggiorna
 * il file con la classifica dei punteggi
 *
 * @param punteggio punteggio totalizzato durante la paratita
 */
void update_file(const int punteggio, time_t data) {
    // lettura del file ed inserimento dei livelli all'interno di una lista
    char nome_file[50] = "classifica.txt";
    clist lista = crea_lista(nome_file, NULL);
    lista = ordered_insert(lista, punteggio, data);

    // riscrittura del file
    ofstream file(nome_file, ios::trunc); // Svuota e riscrive
    if (!file) {
        cerr << "Errore: impossibile aprire il file!" << endl;
        return;
    }
    while (lista != NULL) {
        file << lista->punteggio << " - " << asctime(localtime(&lista->data)) << endl;
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

void Menu::prova_per_livello(const int livello, WINDOW *win) {
    initscr();
    noecho();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // costruisco classe livelli

    lvs.set_livello_selezionato(livello); // PARAMETRO DA VEDERE NELL'altro file

    // newwin(altezza, larghezza, inizio_Y, inizio_X)
    werase(win);
    wattroff(win, A_REVERSE);
    box(win, 0, 0);
    refresh();
    wrefresh(win);
    mvwprintw(win, rows/4, cols/8, "LIVELLO SCELTO: %d, PREMI INVIO E BUONA FORTUNA!", livello);
    refresh();
    wrefresh(win);
    getch();
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
        prova_per_livello(highlight + 1, win);
    } else if (strcmp(selected, VOCE_ESCI) == 0)
      endGame = true;
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
    WINDOW *menu = newwin(rows/2, (cols/3)*2, (LINES/2)-(rows/4)-1, (COLS/2)-((cols/6)*2)-1);
    box(menu, 0, 0);
    refresh();
    wrefresh(menu);
    mvwprintw(menu, 1, 8, "%s", title);

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
            mvwprintw(menu, i+3, 1, "%s", voce);
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