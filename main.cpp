/*
 * Il gioco deve quindi prevedere un menù iniziale con le seguenti opzioni:
 *  o Nuova partita
 *  o Visualizza classifica ordinata in modo decrescente
 *      (punteggi delle partite terminate)
 *
 *  TODO: creare una classe Classifica per tenere traccia dei suoi
 *      tipi di dato, numero di partite giocate e metodi come
 *      l'aggiunta di una partita, lettura della classifica
 */
#include "menu.h"

int main() {
    const char* voices[2] = {"Nuova partita", "Visualizza classifica"};
    Menu menu_generale = Menu(voices, 2);
    char titolo[50] = "- MENU (seleziona una voce e premi invio) -";
    menu_generale.display(titolo);

    return 0;
}