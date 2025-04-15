#ifndef PAUSEEXIT_H
#define PAUSEEXIT_H

#include <iostream>
using namespace std;
#include <ncurses.h>
#include <string>
#include "default_functions.hpp"
#include "Constant.hpp"
#include "WindowScelta.hpp"

class PauseExit : public WindowScelta {
protected:
    string pauseOption[pauseOptions];
public:
    bool endGame, aggPunteggio;
    PauseExit();
    int display(int punteggio);
};


#endif //PAUSEEXIT_H
