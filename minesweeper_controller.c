#include  <nusys.h>
#include "localdef.h"
#include "minesweeper_main.h"
#include "minesweeper_controller.h"
#include <malloc.h>
#include <nualstl_n.h>
#include "assets/sounds/n64st1.h"

NUContData contData[4];

char konami[10] = "UUDDLRLRBA";
int konami_pos = 0;

void externalDevicesInit() {
	s32 ret;
	int controller_number = 0; // one player so we only check for player one's controller, otherwise loop from 0 to MAXCONTROLLERS
	
	ret = nuContRmbCheck(controller_number);
	if (!ret) {
		gamestate.rumble = True;
		nuContRmbModeSet(controller_number, NU_CONT_RMB_MODE_ENABLE);
		nuContRmbStart(controller_number, 128, 10);
	}
}

void controllerInGame() {
	short dPad = 0;
	int x, y;
	if (gamestate.menu == GAME_MENU_NONE)  {
		/* dealing with joystick */
		if (contData[0].stick_x > 16)
			gamestate.cursorX += contData[0].stick_x / 24;
		if (contData[0].stick_x < -16)
			gamestate.cursorX += contData[0].stick_x / 24;
		if (contData[0].stick_y > 16)
			gamestate.cursorY -= contData[0].stick_y / 24;
		if (contData[0].stick_y < -16)
			gamestate.cursorY -= contData[0].stick_y / 24;
		// compute which panel the cursor is targeting
		gamestate.caseX = (int)((float)gamestate.cursorX / 16.0 - (40.0 - (float)gamestate.board.width) / 2.0); // 40 is the maximum of 16px panels on a 640 screen width
		gamestate.caseY = (int)((float)gamestate.cursorY / 16.0 - (30.0 - (float)gamestate.board.height) /2.0); // 30 is the maximum of 16px panels on a 480 screen height
		//reveal a panel if not flagged
		if(contData[0].trigger & A_BUTTON && !gamestate.board.items[gamestate.caseY][gamestate.caseX].isFlagged) {
			if (!gamestate.cheat || (gamestate.cheat && !gamestate.board.items[gamestate.caseY][gamestate.caseX].isBomb)) { // you can't lose if you cheat
				if (memory_size == 0x00800000 && !gamestate.board.items[gamestate.caseY][gamestate.caseX].isRevealed )
					sndHandle = nuAuStlSndPlayerPlay(FX_FLAG);
				revealPanel(gamestate.caseX, gamestate.caseY);
			}
		}
		// flag / unflag a panel
		if(contData[0].trigger & B_BUTTON) {
			if (memory_size == 0x00800000)
				sndHandle = nuAuStlSndPlayerPlay(FX_UNFLAG);
			if (!gamestate.board.items[gamestate.caseY][gamestate.caseX].isFlagged) 
				gamestate.board.items[gamestate.caseY][gamestate.caseX].isFlagged = 1;
			else
				gamestate.board.items[gamestate.caseY][gamestate.caseX].isFlagged = 0;
		}
		/* dealing with dpad */
		if (contData[0].trigger & R_JPAD) {
			gamestate.caseX++;
			dPad = 1;
		}
		if (contData[0].trigger & L_JPAD) {
			gamestate.caseX--;
			dPad = 1;
		}
		if (contData[0].trigger & D_JPAD) {
			gamestate.caseY++;
			dPad = 1;
		}
		if (contData[0].trigger & U_JPAD) {
			gamestate.caseY--;
			dPad = 1;
		}
		if (gamestate.caseX < 0)
			gamestate.caseX = 0;
		if (gamestate.caseX > gamestate.board.width-1)
			gamestate.caseX = gamestate.board.width-1;
		if (gamestate.caseY < 0)
			gamestate.caseY = 0;
		if (gamestate.caseY > gamestate.board.height-1)
			gamestate.caseY = gamestate.board.height-1;
		if (dPad) {
			gamestate.cursorX = (40-gamestate.board.width) * 8 + 7 + gamestate.caseX * 16;
			gamestate.cursorY = (30-gamestate.board.height) * 8 + 7 + gamestate.caseY * 16;
		}
		// check the cursor and case are within boundaries
		if (gamestate.cursorX < (40-gamestate.board.width) * 8)
			gamestate.cursorX = (40-gamestate.board.width) * 8;
		if (gamestate.cursorX > (40-gamestate.board.width) * 8 + (gamestate.board.width) * 16 - 1) 
			gamestate.cursorX = (40-gamestate.board.width) * 8 + (gamestate.board.width) * 16 - 1;
		if (gamestate.cursorY < (30-gamestate.board.height) * 8)
			gamestate.cursorY = (30-gamestate.board.height) * 8;
		if (gamestate.cursorY > (30-gamestate.board.height) * 8 + (gamestate.board.height) * 16 - 1) 
			gamestate.cursorY = (30-gamestate.board.height) * 8 + (gamestate.board.height) * 16 - 1;
		if(contData[0].trigger & START_BUTTON) {
			gamestate.menu = GAME_MENU_PAUSE;
			gamestate.caseY = 0;
		}
	}
	else if (gamestate.menu == GAME_MENU_PAUSE) {
		controllerPause();
	}
	else if (gamestate.menu == GAME_MENU_NEW) 
		if(contData[0].trigger & B_BUTTON || contData[0].trigger & START_BUTTON) {
			gamestate.menu = GAME_MENU_PAUSE;
			gamestate.caseY = 1;
			gamestate.caseX = 0;
		}
		else
			controllerNewGame();
	else if (gamestate.menu == GAME_MENU_CREDITS)
		controllerCredits();
}

void controllerNewGame() {
	if (contData[0].trigger & D_JPAD || (contData[0].trigger && contData[0].stick_y > 16))
		gamestate.caseY++;
	if (contData[0].trigger & U_JPAD || (contData[0].trigger && contData[0].stick_y < -16))
		gamestate.caseY--;
	if (gamestate.caseY > 3)
		gamestate.caseY = 0;
	if (gamestate.caseY < 0)
		gamestate.caseY = 3;
	
	if (contData[0].trigger & R_JPAD) {
		if (gamestate.caseY == 0)
			gamestate.newWidth++;
		if (gamestate.caseY == 1)
			gamestate.newHeight++;
		if (gamestate.caseY == 2)
			gamestate.newMines++;
	}
	if (contData[0].trigger & L_JPAD) {
		if (gamestate.caseY == 0)
			gamestate.newWidth--;
		if (gamestate.caseY == 1)
			gamestate.newHeight--;
		if (gamestate.caseY == 2)
			gamestate.newMines--;
	}
	if (gamestate.newWidth > BOARD_MAX_WIDTH )
		gamestate.newWidth = BOARD_MAX_WIDTH;
	if (gamestate.newWidth < 5)
		gamestate.newWidth = 5;
	if (gamestate.newHeight > BOARD_MAX_HEIGHT )
		gamestate.newHeight = BOARD_MAX_HEIGHT;
	if (gamestate.newHeight < 5)
		gamestate.newHeight = 5;
	if (gamestate.newMines < 1)
		gamestate.newMines = 1;
	if (gamestate.newMines > gamestate.newHeight * gamestate.newWidth - 1)
		gamestate.newMines = gamestate.newHeight * gamestate.newWidth - 1;
	if ((contData[0].trigger & A_BUTTON && gamestate.caseY == 3) || (contData[0].trigger & START_BUTTON)) {
		gamestate.status = GAME_STATUS_RUNNING;
		gamestate.menu   = GAME_MENU_NONE;
		setBoard();
	}
}

void controllerPause() {
	short x, y;
	if (contData[0].trigger & D_JPAD || (contData[0].trigger && contData[0].stick_y > 16))
		gamestate.caseY++;
	if (contData[0].trigger & U_JPAD || (contData[0].trigger && contData[0].stick_y < -16))
		gamestate.caseY--;
	if (contData[0].trigger & R_JPAD || (contData[0].trigger && contData[0].stick_x > 16))
		gamestate.caseX++;
	if (contData[0].trigger & L_JPAD || (contData[0].trigger && contData[0].stick_x < -16))
		gamestate.caseX--;
	if (gamestate.caseY > 2)
		gamestate.caseY = 0;
	if (gamestate.caseY < 0)
		gamestate.caseY = 2;
	if (gamestate.caseX > 1)
		gamestate.caseX = 0;
	if (gamestate.caseX < 0)
		gamestate.caseX = 1;
	
	if (contData[0].trigger & START_BUTTON) 
		gamestate.menu = GAME_MENU_NONE;
	if (contData[0].trigger & A_BUTTON) {
		// resume
		if (gamestate.caseY == 0 && gamestate.caseX == 0)
			gamestate.menu = GAME_MENU_NONE;
		// new game
		if (gamestate.caseY == 1 && gamestate.caseX == 0) {
			gamestate.menu = GAME_MENU_NEW;
			gamestate.caseY = 0;
			gamestate.caseX = 0;
			gamestate.newWidth = gamestate.board.width;
			gamestate.newHeight = gamestate.board.height;
			gamestate.newMines = gamestate.board.nbrMines;
		}
		// restart
		if (gamestate.caseY == 0 && gamestate.caseX == 1) {
			gamestate.menu = GAME_MENU_NONE;
			for (x = 0; x <  gamestate.board.width; x++)
				for (y = 0; y < gamestate.board.height; y++) {
					gamestate.board.items[y][x].isFlagged = 0;
					gamestate.board.items[y][x].isRevealed = 0;
				}
		}
		// reveal
		if (gamestate.caseY == 1 && gamestate.caseX == 1) {
			gamestate.menu = GAME_MENU_NONE;
			gamestate.status = GAME_STATUS_OVER;
			for (x = 0; x <  gamestate.board.width; x++)
				for (y = 0; y < gamestate.board.height; y++) {
					gamestate.board.items[y][x].isRevealed = 1;
				}
		}
		// credits
		if (gamestate.caseY == 2) {
			textures[6].romStart	= (u32)_creditsSegmentRomStart;
			textures[6].romEnd		= (u32)_creditsSegmentRomEnd;
			nuPiReadRom(textures[6].romStart, textures[6].pointer32, textures[6].romSize);
			gamestate.menu = GAME_MENU_CREDITS;
		}
	}
	
}

void controllerCredits() {
	if (contData[0].trigger & START_BUTTON || contData[0].trigger & A_BUTTON || contData[0].trigger & B_BUTTON ) {
		textures[6].romStart	= (u32)_menuSegmentRomStart;
		textures[6].romEnd		= (u32)_menuSegmentRomEnd;
		nuPiReadRom(textures[6].romStart, textures[6].pointer32, textures[6].romSize);
		gamestate.menu = GAME_MENU_PAUSE;
	}
}

void controllerTitle() {
	// new game configuration already started
	if (gamestate.menu == GAME_MENU_NEW) 
		controllerNewGame();
	// press start to configure a new game
	else if (gamestate.menu == GAME_MENU_NONE)  {
		if(contData[0].trigger & START_BUTTON) {
			gamestate.menu = GAME_MENU_NEW;
			gamestate.caseY = 0;
			gamestate.caseX = 0;
			gamestate.newWidth = gamestate.board.width;
			gamestate.newHeight = gamestate.board.height;
			gamestate.newMines = gamestate.board.nbrMines;
		}
	}
	else if (gamestate.menu == GAME_ANIMATION) 
		if (contData[0].trigger & START_BUTTON || contData[0].trigger & A_BUTTON)
			gamestate.menu = GAME_MENU_NONE;
}

void controllerGameOver() {
	if (gamestate.menu == GAME_MENU_NONE) {
		if (contData[0].trigger & START_BUTTON) {
			gamestate.menu = GAME_MENU_NEW;
			gamestate.caseX = 0;
			gamestate.newWidth = gamestate.board.width;
			gamestate.newHeight = gamestate.board.height;
			gamestate.newMines = gamestate.board.nbrMines;		
		}
	}
	else if (gamestate.menu == GAME_MENU_NEW)
		controllerNewGame();		
}

void controllerExpansionPak() {
	if (contData[0].trigger & START_BUTTON || contData[0].trigger & A_BUTTON)
		initGame();
}

void checkKonamiCode() {
	char current = NULL;
	if (contData[0].trigger & D_JPAD)
		current = 'D';
	if (contData[0].trigger & U_JPAD)
		current = 'U';
	if (contData[0].trigger & R_JPAD)
		current = 'R';
	if (contData[0].trigger & L_JPAD)
		current = 'L';
	if (contData[0].trigger & A_BUTTON)
		current = 'A';
	if (contData[0].trigger & B_BUTTON)
		current = 'B';
	if (current == konami[konami_pos])
		konami_pos++;
	else
		if (current != NULL)
			konami_pos = 0;
	if (konami_pos > 9) {
		if (!gamestate.cheat)
			gamestate.cheat = True;
		else
			gamestate.cheat = False;
		konami_pos = 0;
	}
}

void readController() {
	/* Read the controller data. */
	nuContDataGetExAll(contData);
	// start a new game
	if (gamestate.status == GAME_STATUS_RUNNING)
		controllerInGame();
	else if (gamestate.status == GAME_STATUS_TITLE)
		controllerTitle();
	else if (gamestate.status == GAME_STATUS_OVER || gamestate.status == GAME_STATUS_WON) 
		controllerGameOver();
	else if (gamestate.status == GAME_STATUS_EXPPAK) 
		controllerExpansionPak();
	// debug mode
	if(contData[0].trigger & Z_TRIG)
		if (gamestate.debug) {
			nuDebConClear(0);
			gamestate.debug = False;
		}
		else
			gamestate.debug = True;
	checkKonamiCode();
}

