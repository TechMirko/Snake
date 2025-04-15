#include "Levels.hpp"
#include "Constant.hpp"

plist lista_livelli = NULL;


plist Levels::ordered_insert(plist bilista, const Livello l) {
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

plist Levels::crea_blista(plist bilista) {
    Livello livelli[5];
    for (int i = 0; i < 5; i++)
        livelli[i] = {i + 1, i + 1, 2, 2.5}; // VALORI BONUS E MELA FISSI
    for (int i = 0; i < 5; i++) 
        bilista = ordered_insert(bilista, livelli[i]);
    return bilista;
}

Levels::Levels() {
    livello_scelto = 0;
    lista_livelli = crea_blista(lista_livelli);
}

double Levels::get_bonus(int livello) {
    plist tmp = lista_livelli;
    while (tmp != NULL) {
        if (tmp->liv.numero == livello)
            return tmp->liv.bonus;
        tmp = tmp->next;
    }
    return 0; 
}

int Levels::get_velocita(int livello) {
    plist tmp = lista_livelli;
    while (tmp != NULL) {
        if (tmp->liv.numero == livello) 
            return tmp->liv.velocita;
        tmp = tmp->next;
    }
    return 0;
}

int Levels::get_valore_mela(int livello) {
    plist tmp = lista_livelli;
    while (tmp != NULL) {
        if (tmp->liv.numero == livello) 
            return tmp->liv.valore_mela;
        tmp = tmp->next;
    }
    return 0;
}

int Levels::get_livello_scelto() {
    return livello_scelto;
}

void Levels::set_livello_selezionato(int livello) {
    livello_scelto = livello;
}

// istanza globale
Levels lvs = Levels();