//
// Created by graziacomp on 3/15/25.
//

#include "GameOver.hpp"

GameOver :: GameOver() : WindowScelta(gameoverOptions, "Game Over") {

  endGame = false;
  ricomincia = false;

  overOption[0]="Riprova";
  overOption[1]="Torna al Menu";
  overOption[2]="Esci";
};

void GameOver::display(int punteggio){
  int i=WindowScelta::windowDisplay(overOption, gameoverOptions, punteggio);
  if (i==2) endGame = true;
  else {
    endGame = false;
    if (i==0) ricomincia = true;
  }
};