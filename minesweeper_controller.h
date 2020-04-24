#ifndef _MINESWEEPER_CONTROLLER_
#define _MINESWEEPER_CONTROLLER_

void controllerInGame() ;
void controllerNewGame();
void controllerPause() ;
void controllerCredits();
void controllerTitle() ;
void controllerGameOver();
void controllerExpansionPak();
void readController();

void externalDevicesInit();


char konami[10];
int konami_pos;

#endif /* _MINESWEEPER_CONTROLLER_ */