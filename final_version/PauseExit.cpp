#include "PauseExit.hpp"

PauseExit::PauseExit() : WindowScelta(pauseOptions, "Pausa"){

    pauseOption[0] = "Riprendi";
    pauseOption[1] = "Ricomincia";
    pauseOption[2] = "Torna al Menu";
    pauseOption[3] = "Esci";
}

int PauseExit::display(int punteggio) {
    int i=WindowScelta::windowDisplay(pauseOption, pauseOptions, punteggio);
	return i;
}

