#include "menu_livelli.h"

void print_livelli(plist m) {
    if (m != NULL) {
        cout << "Livello " << m->l.numero << ", difficolta': " << m->l.difficolta << endl;
        print_livelli(m->next);
    }
}

plist insert_livello(plist m, livello liv) {
    if (m == NULL) {
        plist new_element = new menu;
        new_element->l.numero = liv.numero;
        new_element->l.difficolta = liv.difficolta;
        new_element->prec = NULL;
        new_element->next = NULL;
        return new_element;
    }
    if (m->l.numero < liv.numero) {
        m->next = insert_livello(m->next, liv);
        return m;
    }
    plist new_element = new menu;
    new_element->l.numero = liv.numero;
    new_element->l.difficolta = liv.difficolta;
    new_element->prec = m;
    new_element->next = m->next;
    return new_element;
}

