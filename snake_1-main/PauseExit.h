#ifndef PAUSEEXIT_H
#define PAUSEEXIT_H

#include <iostream>
using namespace std;
#include <ncurses/ncurses.h>
#include <string>
#include "default_functions.h"
#include "Constant.h"
#include "WindowScelta.h"

class PauseExit : public WindowScelta {
protected:
    string pauseOption[pauseOptions];
public:
    bool endGame, aggPunteggio;
    PauseExit();
    int display(int punteggio);
};


#endif //PAUSEEXIT_H
