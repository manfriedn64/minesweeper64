#include  <nusys.h>
#include "localdef.h"
#include "minesweeper_main.h"
#include "minesweeper_controller.h"
#include <malloc.h>
#include <nualstl_n.h>
#include "assets/sounds/n64st1.h"

NUContData contData[4];

void controllerInGame() {
	short dPad = 0;
	int x, y;
	if (gamestate.menu == GAME_MENU_NONE)  {
		/* dealing with joystick */
		if (contData[0].stick_x > 16)
			gamestate.cursorX += contData[0].stick_x / 4;
		if (contData[0].stick_x < -16)
			gamestate.cursorX += contData[0].stick_x / 4;
		if (contData[0].stick_y > 16)
			gamestate.cursorY -= contData[0].stick_y / 4;
		if (contData[0].stick_y < -16)
			gamestate.cursorY -= contData[0].stick_y / 4;
		// compute which panel the cursor is targeting
		gamestate.caseX = gamestate.cursorX / 16 - (40-gamestate.board.width)/2; // 40 is the maximum of 16px panels on a 640 screen width
		gamestate.caseY = gamestate.cursorY / 16 - (30-gamestate.board.height)/2; // 30 is the maximum of 16px panels on a 480 screen height
		//reveal a panel if not flagged
		if(contData[0].trigger & A_BUTTON && !gamestate.board.items[gamestate.caseY][gamestate.caseX].isFlagged) {
			sndHandle = nuAuStlSndPlayerPlay(FX_FLAG);
			revealPanel(gamestate.caseX, gamestate.caseY);
		}
		// flag / unflag a panel
		if(contData[0].trigger & B_BUTTON) {
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
		if (contData[0].trigger & A_BUTTON) 
			gamestate.menu = GAME_MENU_NONE;
}

void controllerGameOver() {
	if (gamestate.menu == GAME_MENU_NONE) {
		if (contData[0].trigger & START_BUTTON) {
			//gamestate.status = GAME_STATUS_TITLE;
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
	if (contData[0].trigger & START_BUTTON)
		initGame();
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
	/*nuDebConTextPos(0,25,1);
	sprintf(conbuf, "Stick X  : %d    ", contData[0].stick_x);
	nuDebConCPuts(0, conbuf);
	nuDebConTextPos(0,25,2);
	sprintf(conbuf, "Stick Y  : %d    ", contData[0].stick_y);
	nuDebConCPuts(0, conbuf);*/
}
