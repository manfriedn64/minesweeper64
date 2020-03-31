#include  <nusys.h>
#include "localdef.h"
#include "minesweeper.h"
#include <malloc.h>

extern Texture textures[20];
extern GameState gamestate;
extern Gfx*	gfxListPtr;
extern Gfx*	objList;
extern Gfx*	gfxListPtr;
NUContData contData[4];

/*
	Initiate graphical elements common within all themes
*/
void initGame() {
	int x, y, i;
	// first, define textures
	textures[0].romStart	= (u32)_title64SegmentRomStart;
	textures[0].romEnd		= (u32)_title64SegmentRomEnd;
	textures[0].pointer32	= (u32*)TITLE64_ADDRESS;
	textures[0].width		= 488;
	textures[0].height		= 285;
	textures[0].malloc		= False;
	
	textures[1].romStart	= (u32)_tiles1SegmentRomStart;
	textures[1].romEnd		= (u32)_tiles1SegmentRomEnd;
	textures[1].width		= 64;
	textures[1].height		= 32;
	textures[1].malloc		= True;

	textures[2].romStart	= (u32)_tiles2SegmentRomStart;
	textures[2].romEnd		= (u32)_tiles2SegmentRomEnd;
	textures[2].width		= 64;
	textures[2].height		= 32;
	textures[2].malloc		= True;
	
	textures[3].romStart	= (u32)_titleNameSegmentRomStart;
	textures[3].romEnd		= (u32)_titleNameSegmentRomEnd;
	textures[3].pointer32	= (u32*)TITLENAME_ADDRESS;
	textures[3].width		= 624;
	textures[3].height		= 72;
	textures[3].malloc		= False;
	
	textures[4].romStart	= (u32)_backgroundSegmentRomStart;
	textures[4].romEnd		= (u32)_backgroundSegmentRomEnd;
	textures[4].pointer32	= (u32*)BACKGROUND_ADDRESS;
	textures[4].width		= 640;
	textures[4].height		= 480;
	textures[4].malloc		= False;
	
	textures[5].romStart	= (u32)_newgamepauseSegmentRomStart;
	textures[5].romEnd		= (u32)_newgamepauseSegmentRomEnd;
	textures[5].width		= 200;
	textures[5].height		= 26;
	textures[5].malloc		= True;
	
	textures[6].romStart	= (u32)_menuSegmentRomStart;
	textures[6].romEnd		= (u32)_menuSegmentRomEnd;
	textures[6].pointer32	= (u32*)MENU_ADDRESS;
	textures[6].width		= 512;
	textures[6].height		= 352;
	textures[6].malloc		= False;
	
	textures[7].romStart	= (u32)_pausetextSegmentRomStart;
	textures[7].romEnd		= (u32)_pausetextSegmentRomEnd;
	textures[7].width		= 456;
	textures[7].height		= 50;
	textures[7].malloc		= True;
	
	textures[8].romStart	= (u32)_menutextSegmentRomStart;
	textures[8].romEnd		= (u32)_menutextSegmentRomEnd;
	textures[8].width		= 216;
	textures[8].height		= 50;
	textures[8].malloc		= True;
	
	textures[9].romStart	= (u32)_numbersSegmentRomStart;
	textures[9].romEnd		= (u32)_numbersSegmentRomEnd;
	textures[9].width		= 128;
	textures[9].height		= 50;
	textures[9].malloc		= True;
	
	textures[10].romStart	= (u32)_buttonSegmentRomStart;
	textures[10].romEnd		= (u32)_buttonSegmentRomEnd;
	textures[10].width		= 152;
	textures[10].height		= 110;
	textures[10].malloc		= True;
	
	textures[11].romStart	= (u32)_smallbuttonsSegmentRomStart;
	textures[11].romEnd		= (u32)_smallbuttonsSegmentRomEnd;
	textures[11].width		= 304;
	textures[11].height		= 136;
	textures[11].malloc		= True;
	
	// now loading from ROM to RAM
	for (i = 0; i <= 14; i++) {
		if (textures[i].malloc)
			textures[i].pointer32	= (u32*) mt_malloc(textures[i].width * textures[i].height * 2 * sizeof(char));
		textures[i].pointer64	= (u64*)textures[i].pointer32;
		textures[i].romSize = textures[i].romEnd - textures[i].romStart;
		nuPiReadRom(textures[i].romStart, textures[i].pointer32, textures[i].romSize);
	}
	
	// set coordinates in textures for tiles
	gamestate.tileBlank		= (Coordinates){ 0,  0, &textures[1], 16, 16};
	gamestate.tileMasked	= (Coordinates){16,  0, &textures[1], 16, 16};
	gamestate.redFlag		= (Coordinates){32,  0, &textures[1], 16, 16};
	gamestate.bomb			= (Coordinates){48,  0, &textures[1], 16, 16};
	gamestate.greenFlag		= (Coordinates){ 0, 16, &textures[1], 16, 16};
	gamestate.numberOne		= (Coordinates){16, 16, &textures[1], 16, 16};
	gamestate.numberTwo		= (Coordinates){32, 16, &textures[1], 16, 16};
	gamestate.numberThree	= (Coordinates){ 0,  0, &textures[2], 16, 16};
	gamestate.numberFour	= (Coordinates){16,  0, &textures[2], 16, 16};
	gamestate.numberFive	= (Coordinates){32,  0, &textures[2], 16, 16};
	gamestate.numberSix		= (Coordinates){48,  0, &textures[2], 16, 16};
	gamestate.numberSeven	= (Coordinates){ 0, 16, &textures[2], 16, 16};
	gamestate.numberHeight	= (Coordinates){16, 16, &textures[2], 16, 16};
	gamestate.target		= (Coordinates){32, 16, &textures[2], 16, 16};
	// set coordinates in textures for text
	gamestate.text[TEXT_WIDTH]		= (Coordinates){  0, 0, &textures[8],  66, 25};
	gamestate.text[TEXT_HEIGHT]		= (Coordinates){ 69, 0, &textures[8],  75, 25};
	gamestate.text[TEXT_MINES]		= (Coordinates){146, 0, &textures[8],  65, 25};
	gamestate.text[TEXT_RESUME]		= (Coordinates){  0, 0, &textures[7],  84, 25};
	gamestate.text[TEXT_RESTART]	= (Coordinates){ 86, 0, &textures[7],  90, 25};
	gamestate.text[TEXT_NEWGAME]	= (Coordinates){178, 0, &textures[7], 106, 25};
	gamestate.text[TEXT_REVEAL]		= (Coordinates){286, 0, &textures[7],  78, 25};
	gamestate.text[TEXT_CREDITS]	= (Coordinates){365, 0, &textures[7],  85, 25};
	gamestate.text[TEXT_MENU_NEW]	= (Coordinates){  0, 0, &textures[5], 124, 26};
	gamestate.text[TEXT_MENU_PAUSE]	= (Coordinates){127, 0, &textures[5],  73, 26};
	// set coordinates in textures for font numbers
	gamestate.numbers[NUMBER_0]	= (Coordinates){  0, 0, &textures[9], 12, 25};
	gamestate.numbers[NUMBER_1]	= (Coordinates){ 13, 0, &textures[9],  8, 25};
	gamestate.numbers[NUMBER_2]	= (Coordinates){ 22, 0, &textures[9], 12, 25};
	gamestate.numbers[NUMBER_3]	= (Coordinates){ 35, 0, &textures[9], 12, 25};
	gamestate.numbers[NUMBER_4]	= (Coordinates){ 48, 0, &textures[9], 13, 25};
	gamestate.numbers[NUMBER_5]	= (Coordinates){ 62, 0, &textures[9], 11, 25};
	gamestate.numbers[NUMBER_6]	= (Coordinates){ 74, 0, &textures[9], 13, 25};
	gamestate.numbers[NUMBER_7]	= (Coordinates){ 88, 0, &textures[9], 12, 25};
	gamestate.numbers[NUMBER_8]	= (Coordinates){101, 0, &textures[9], 12, 25};
	gamestate.numbers[NUMBER_9]	= (Coordinates){114, 0, &textures[9], 11, 25};
	// set coordinates in textures for font numbers
	gamestate.buttons[BUTTON_UP]	= (Coordinates){  0, 0, &textures[11], 67, 68};
	gamestate.buttons[BUTTON_DOWN]	= (Coordinates){ 67, 0, &textures[11], 67, 68};
	gamestate.buttons[BUTTON_CHECK]	= (Coordinates){134, 0, &textures[11], 67, 68};
	gamestate.buttons[BUTTON_EMPTY]	= (Coordinates){201, 0, &textures[11], 67, 68};
	gamestate.buttons[BUTTON_LARGE]	= (Coordinates){  3, 0, &textures[10],145, 55};
	// set coordinates in textures for font letters
	// set game status
	gamestate.backgroundPosition 	= 0;
	gamestate.backgroundColor	= (Rgb){160, 240, 216};
	gamestate.title64		= &textures[0];
	gamestate.titleName		= &textures[3];
	gamestate.background	= &textures[4];
	gamestate.menuTitle		= &textures[5];
	gamestate.menuTexture	= &textures[6];
	gamestate.status = GAME_STATUS_TITLE;
	gamestate.menu = GAME_MENU_NONE; 
	gamestate.cursorX = 1;
	gamestate.cursorY = 1;
	gamestate.currentTextureInTMEM = NULL;
	for (x = 0; x <  BOARD_MAX_WIDTH; x++)
		for (y = 0; y < BOARD_MAX_HEIGHT; y++) 
			gamestate.board.items[y][x] = (Item){0, 0, 0, 0};
	gamestate.allPanels = (Panel *) mt_malloc(BOARD_MAX_WIDTH * BOARD_MAX_HEIGHT * sizeof(Panel));
}


void insertIntoList(List* list, int value) {
	//Panel* panel = (Panel *) mt_malloc(sizeof(Panel));
	Panel* panel = &gamestate.allPanels[list->size];
	panel->next = NULL;
	panel->previous = NULL;
	panel->value = value;
	panel->position = list->size;
	if (list->last) {
		list->last->next = panel;
		panel->previous = list->last;
	}
	list->last = panel;
	if (list->first == NULL)
		list->first = panel;
	list->size++;
}

void removeItemFromList(List* list, Panel* panel) {
	Panel* temp = panel->next;
	if (panel->position != 0)
		panel->previous->next = panel->next;
	else
		list->first = panel->next;
	if (panel->position != list->size-1)
		panel->next->previous = panel->previous;
	
	while(temp) {
		temp->position--;
		temp = temp->next;
	}
	list->size--;
}

Panel* findValueInList(List* list, int position) {
	Panel* current = list->first;
	while (current) {
		if (current->position == position)
			return current;
		current = current->next;
	}
	list->size--;
	return NULL;
}

void incrementNumbers(x, y) {
	int tempX, tempY;
	for (tempY = y -1; tempY <= y +1; tempY++)
		for (tempX = x -1; tempX <= x +1; tempX++)
			if (tempX >= 0 && tempX < gamestate.board.width && tempY >=0 && tempY < gamestate.board.height)
				gamestate.board.items[tempY][tempX].number++;	
}

void createMines() {
	int i, x, y;
	List list;
	Panel* random_panel;
	// first step is to create a list of all panels in the board
	list.size = 0;
	list.first = NULL;
	list.last = NULL;
	for (i = 0; i < gamestate.board.width * gamestate.board.height; i++)
		insertIntoList(&list, i);
	// pick <nbr_mines> randomly in the list
	for (i = 0; i < gamestate.board.nbrMines; i++) {
		random = rand() / 32767.0 * (list.size-1); // pick one of the element in the list;
		random_panel = findValueInList(&list, (int)random);
		//x = random_panel->value % gamestate.board.height;
		//y = random_panel->value / gamestate.board.height;
		y = random_panel->value % gamestate.board.height;
		x = random_panel->value / gamestate.board.height;
		if (y < gamestate.board.height && x < gamestate.board.width) {
			gamestate.board.items[y][x].isBomb = 1;
			removeItemFromList(&list, random_panel);
			incrementNumbers(x, y);
		}
		else // if somehow the x and y found where outside the boundaries so we need to rerun this iteration. I am unsure why but it seems to happen
			i--;
	}
	gamestate.status = GAME_STATUS_RUNNING;
}

void setBoard() {
	int x, y;
	srand(osGetCount() % 10000000);
	random = rand()/32767.0;
	gamestate.board.width = BOARD_MAX_WIDTH;
	gamestate.board.height = BOARD_MAX_HEIGHT;
	gamestate.board.width = gamestate.newWidth;
	gamestate.board.height = gamestate.newHeight;
	gamestate.board.nbrMines = gamestate.newMines;
	gamestate.board.nbrLeftToCheck = gamestate.board.width * gamestate.board.height;
	// set all the board to 0 (no mine)
	for (x = 0; x <  gamestate.board.width; x++)
		for (y = 0; y < gamestate.board.height; y++) {
			gamestate.board.items[y][x].isBomb = 0;
			gamestate.board.items[y][x].isFlagged = 0;
			gamestate.board.items[y][x].isRevealed = 0;
			gamestate.board.items[y][x].number = 0;
		}
	createMines();
	gamestate.cursorX = 320;
	gamestate.cursorY = 240;
}

void revealPanel(short x, short y) {
	short tempX, tempY;
	if (x >= 0 && x < gamestate.board.width && y >= 0 && y < gamestate.board.height)
		if (!gamestate.board.items[y][x].isRevealed) {
			gamestate.board.items[y][x].isRevealed = 1;
			if (gamestate.board.items[y][x].isBomb == 1)
				gamestate.status = GAME_STATUS_OVER;
			gamestate.board.nbrLeftToCheck--;
			tempX = x;
			tempY = y;
			/*if (gamestate.board.items[y][x].number == 0)
				for (tempX = x -1; tempX <= x +1; tempX++)
					for (tempY = y -1; tempY <= y +1; tempY++)
						if (!(tempX = x && tempY == y))
							if (!gamestate.board.items[tempY][tempX].isRevealed)
								if (tempX >= 0 && tempX < gamestate.board.width && tempY >=0 && tempY < gamestate.board.height)
									revealPanel(tempX, tempY);*/
		}
	return;
}

void controllerInGame() {
	short dPad = 0;
	int x, y;
	if (gamestate.menu == GAME_MENU_NONE)  {
		/* dealing with joystick */
		if (contData[0].stick_x > 16)
			gamestate.cursorX++;
		if (contData[0].stick_x < -16)
			gamestate.cursorX--;
		if (contData[0].stick_y > 16)
			gamestate.cursorY--;
		if (contData[0].stick_y < -16)
			gamestate.cursorY++;
		// compute which panel the cursor is targeting
		gamestate.caseX = gamestate.cursorX / 16 - (40-gamestate.board.width)/2; // 40 is the maximum of 16px panels on a 640 screen width
		gamestate.caseY = gamestate.cursorY / 16 - (30-gamestate.board.height)/2; // 30 is the maximum of 16px panels on a 480 screen height
		//reveal a panel if not flagged
		if(contData[0].trigger & A_BUTTON && !gamestate.board.items[gamestate.caseY][gamestate.caseX].isFlagged)
			revealPanel(gamestate.caseX, gamestate.caseY);
		// flag / unflag a panel
		if(contData[0].trigger & B_BUTTON){
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
	else if (gamestate.menu == GAME_MENU_NONE) 
		if(contData[0].trigger & START_BUTTON) {
			gamestate.menu = GAME_MENU_NEW;
			gamestate.caseY = 0;
			gamestate.caseX = 0;
			gamestate.newWidth = gamestate.board.width;
			gamestate.newHeight = gamestate.board.height;
			gamestate.newMines = gamestate.board.nbrMines;
		}
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
	else if(gamestate.menu == GAME_MENU_NEW)
		controllerNewGame();		
}

void readController() {
	/* Read the controller data. */
	nuContDataGetExAll(contData);
	// start a new game
	if (gamestate.status == GAME_STATUS_RUNNING)
		controllerInGame();
	if (gamestate.status == GAME_STATUS_TITLE)
		controllerTitle();
	if (gamestate.status == GAME_STATUS_OVER) 
		controllerGameOver();
}


/*
	sendTexture - NOT IN USE ANYMORE - kept just in case for future stuffs ?
	equivalent to drawSprite with using  gSPTextureRectangle instead of gSPObjRectangle
*/
void sendTexture(int x, int y, Coordinates* coordinates) {
	// load texture to TMEM if not the current one
	if (gamestate.currentTextureInTMEM != coordinates->texture) {
		gDPLoadTextureBlock(
			gfxListPtr++, 
			coordinates->texture->pointer32, 
			G_IM_FMT_RGBA, G_IM_SIZ_16b, 
			coordinates->texture->width, coordinates->texture->height, 0, 
			G_TX_WRAP, G_TX_WRAP, 
			G_TX_NOMASK, G_TX_NOMASK, 
			G_TX_NOLOD, G_TX_NOLOD
		);
	}
	// renders texture as a 2d rectangle
	gSPTextureRectangle(
		gfxListPtr++, 
        x << 2, y << 2, 
        x+coordinates->width  << 2, y+coordinates->height << 2,
        G_TX_RENDERTILE, 
        coordinates->x << 5, coordinates->y << 5, 
        1 << 10, 1 << 10
	);
}

/*
	drawSprite(
		int x						// position in the screen on the X axis 
		int y 						// position in the screen on the Y axis 
		Coordinates* coordinates	// pointer to struct coordinates (contains all needed informations on the sprite to draw)
	)
	Use to draw the requests sprite on screen at the requested x and y coordinates
	
*/
void drawSprite(int x, int y, Coordinates* coordinates) {
	//imageAdrs = GS_PIX2TMEM ((s-coordinate in TMEM) + (t-coordinate in TMEM) * (texture width at the time of loading, G_IM_SIZ_*))
	//imageStride = GS_PIX2TMEM (texture width at the time of loading, G_IM_SIZ_*)
	uObjSprite* sprite;
	// load texture to TMEM if not the current one
	if (gamestate.currentTextureInTMEM != coordinates->texture) {
		gDPLoadTextureBlock(
			gfxListPtr++, 
			coordinates->texture->pointer32, 
			G_IM_FMT_RGBA, G_IM_SIZ_16b, 
			coordinates->texture->width, coordinates->texture->height, 0, 
			G_TX_WRAP, G_TX_WRAP, 
			G_TX_NOMASK, G_TX_NOMASK, 
			G_TX_NOLOD, G_TX_NOLOD
		);
	}
	// configure the sprite and draw it
	sprite = (uObjSprite*)getNextSprite();
	sprite->s.objX = x << 2; // x screen coordinate
	sprite->s.objY = y << 2; // y screen coordinate
	sprite->s.imageW = coordinates->width << 5; // width
	sprite->s.imageH = coordinates->height << 5; // height
	sprite->s.imageAdrs = GS_PIX2TMEM (coordinates->x + coordinates->y * 64, G_IM_SIZ_16b);
	sprite->s.imageStride = GS_PIX2TMEM (coordinates->texture->width, G_IM_SIZ_16b);
	gSPObjRectangle(gfxListPtr++, sprite);
}

/*

*/
void drawBackgroundSprite(int x, int y, Texture* texture) {
	int i;
	uObjSprite* sprite;
	for (i=0; i < texture->height; i++) {
		gDPLoadMultiTile(
			gfxListPtr++, 
			texture->pointer32,
			0,                        // tmem - Address to store in TMEM
			G_TX_RENDERTILE,          // rt - Tile descriptor
			G_IM_FMT_RGBA,            // fmt - Our image format
			G_IM_SIZ_16b,             // size - Pixel size
			texture->width, texture->height,                     // width, height of the full image
			0, i,                     // Top left corner of the rectangle
			texture->width - 1, i,    // Bottom right corner
			0,                        // Palette to use (always 0)
			G_TX_WRAP, G_TX_WRAP,     // cms, cmt
			G_TX_NOMASK, G_TX_NOMASK, // masks, maskt
			G_TX_NOLOD, G_TX_NOLOD    // shifts, shiftt
		);
		sprite = (uObjSprite*)getNextSprite();
		sprite->s.objX = x << 2; // x screen coordinate
		sprite->s.objY = y << 2; // y screen coordinate
		sprite->s.imageW = texture->width << 5; // width
		sprite->s.imageH = 1 << 5; // height
		sprite->s.imageAdrs = GS_PIX2TMEM (0, G_IM_SIZ_16b);
		sprite->s.imageStride = GS_PIX2TMEM (texture->width, G_IM_SIZ_16b);
		gSPObjRectangle(gfxListPtr++, sprite);
	}
}

void drawCursor() {
	drawSprite(gamestate.cursorX - 7, gamestate.cursorY - 7, &gamestate.target);
}

void drawNumber(short top, short right, short number, short line) {
	short remnant;
	while (number >= 1) {
		remnant = number % 10;
		drawBackGroundCoordinates(&gamestate.numbers[remnant], right - gamestate.numbers[remnant].width, top, line);
		right -= gamestate.numbers[remnant].width + 5;
		number = number / 10;
	}
	
}

void drawMenuCredits() {
	drawFullBackGround(gamestate.menuTexture, -1, -1);
}

void drawMenuNew() {
	short left, right, top;
	left  = 320 - gamestate.menuTexture->width  / 2 + 140;
	right = 320 + gamestate.menuTexture->width  / 2 - 140;
	top   = 240 - gamestate.menuTexture->height / 2 + 115;
	drawFullBackGround(gamestate.menuTexture, -1, -1);
	drawBackGroundCoordinates(&gamestate.text[TEXT_MENU_NEW], -1, 480 / 2 - gamestate.menuTexture->height/2  + 22, 0);	
	
	drawBackGroundCoordinates(&gamestate.text[TEXT_WIDTH], left, top, 0);
	drawBackGroundCoordinates(&gamestate.buttons[BUTTON_LARGE], right - gamestate.buttons[BUTTON_LARGE].width, top - ((gamestate.buttons[BUTTON_LARGE].height-gamestate.text[TEXT_WIDTH].height) / 2), (gamestate.caseY == 0 ? 1 : 0));
	drawNumber(top, right - 20, gamestate.newWidth, (gamestate.caseY == 0 ? 1 : 0));
	top += 70;
	drawBackGroundCoordinates(&gamestate.text[TEXT_HEIGHT], left, top, 0);
	drawBackGroundCoordinates(&gamestate.buttons[BUTTON_LARGE], right - gamestate.buttons[BUTTON_LARGE].width, top - ((gamestate.buttons[BUTTON_LARGE].height-gamestate.text[TEXT_WIDTH].height) / 2), (gamestate.caseY == 1 ? 1 : 0));
	drawNumber(top, right - 20, gamestate.newHeight, (gamestate.caseY == 1 ? 1 : 0));
	top += 70;
	drawBackGroundCoordinates(&gamestate.text[TEXT_MINES], left, top, 0);
	drawBackGroundCoordinates(&gamestate.buttons[BUTTON_LARGE], right - gamestate.buttons[BUTTON_LARGE].width, top - ((gamestate.buttons[BUTTON_LARGE].height-gamestate.text[TEXT_WIDTH].height) / 2), (gamestate.caseY == 2 ? 1 : 0));
	drawNumber(top, right - 20, gamestate.newMines, (gamestate.caseY == 2 ? 1 : 0));	
	// validation button
	top  = 240 + gamestate.menuTexture->height / 2 - 100;
	left = 320 + gamestate.menuTexture->width  / 2 - 120;
	drawBackGroundCoordinates(&gamestate.buttons[BUTTON_CHECK], left, top, (gamestate.caseY == 3 ? 1 : 0));
}

void drawMenuPause() {
	short left, right, top;
	left  = 320 - gamestate.menuTexture->width  / 2 + 160;
	right = 320 + gamestate.menuTexture->width  / 2 - 160;
	top   = 240 - gamestate.menuTexture->height / 2 + 115;
	
	drawFullBackGround(gamestate.menuTexture, -1, -1);
	drawBackGroundCoordinates(&gamestate.text[TEXT_MENU_PAUSE], -1, 480 / 2 - gamestate.menuTexture->height/2  + 22, 0);	
	
	drawBackGroundCoordinates(&gamestate.text[TEXT_RESUME], left - gamestate.text[TEXT_RESUME].width / 2, top, (gamestate.caseY == 0 && gamestate.caseX == 0 ? 1 : 0));
	drawBackGroundCoordinates(&gamestate.text[TEXT_RESTART], right - gamestate.text[TEXT_RESTART].width / 2, top, (gamestate.caseY == 0 && gamestate.caseX == 1 ? 1 : 0));
	top += 60;
	drawBackGroundCoordinates(&gamestate.text[TEXT_NEWGAME], left - gamestate.text[TEXT_NEWGAME].width / 2, top, (gamestate.caseY == 1 && gamestate.caseX == 0 ? 1 : 0));
	drawBackGroundCoordinates(&gamestate.text[TEXT_REVEAL], right - gamestate.text[TEXT_REVEAL].width / 2, top, (gamestate.caseY == 1 && gamestate.caseX == 1 ? 1 : 0));
	top += 60;
	drawBackGroundCoordinates(&gamestate.text[TEXT_CREDITS], -1, top, (gamestate.caseY == 2 ? 1 : 0));
	
}

void drawTile(int x, int y, Item* value) {
	if (value->isRevealed) {
		// draw and a grey panel
		drawSprite(x, y, &gamestate.tileBlank);
		if (value->isBomb) {
			// lost :(
			drawSprite(x, y, &gamestate.bomb);
			gamestate.status = GAME_STATUS_OVER;
		}
		else
			switch (value->number) {
				case 1: // 1 bomb is around
					drawSprite(x, y, &gamestate.numberOne);
					break;
				case 2: // 2 bomb is around
					drawSprite(x, y, &gamestate.numberTwo);
					break;
				case 3: // 3 bomb is around
					drawSprite(x, y, &gamestate.numberThree);
					break;
				case 4: // 4 bomb is around
					drawSprite(x, y, &gamestate.numberFour);
					break;
				case 5: // 5 bomb is around
					drawSprite(x, y, &gamestate.numberFive);
					break;
				case 6: // 6 bomb is around
					drawSprite(x, y, &gamestate.numberSix);
					break;
				case 7: // 7 bomb is around
					drawSprite(x, y, &gamestate.numberSeven);
					break;
				case 8: // 8 bomb is around
					drawSprite(x, y, &gamestate.numberHeight);
					break;
			}
		
	}
	else {
		// draw a "button" panel
		drawSprite(x, y, &gamestate.tileMasked);
		if (value->isFlagged) 
			if (gamestate.status == GAME_STATUS_RUNNING && !value->isBomb)
				drawSprite(x, y, &gamestate.redFlag);
			else 
				drawSprite(x, y, &gamestate.greenFlag);
		else if (gamestate.status == GAME_STATUS_OVER && value->isBomb)
			drawSprite(x, y, &gamestate.bomb);

	}
	
	// in order to debug the features, the following was added to see bomb and values. Need to comment / remove this for release ^^ 
	/*switch (value->number) {
		case 1: // 1 bomb is around
			drawSprite(x, y, &gamestate.numberOne);
			break;
		case 2: // 2 bomb is around
			drawSprite(x, y, &gamestate.numberTwo);
			break;
		case 3: // 3 bomb is around
			drawSprite(x, y, &gamestate.numberThree);
			break;
		case 4: // 4 bomb is around
			drawSprite(x, y, &gamestate.numberFour);
			break;
		case 5: // 5 bomb is around
			drawSprite(x, y, &gamestate.numberFive);
			break;
		case 6: // 6 bomb is around
			drawSprite(x, y, &gamestate.numberSix);
			break;
		case 7: // 7 bomb is around
			drawSprite(x, y, &gamestate.numberSeven);
			break;
		case 8: // 8 bomb is around
			drawSprite(x, y, &gamestate.numberHeight);
			break;
	}
	if (value->isBomb)
			drawSprite(x, y, &gamestate.bomb);*/
}

void drawSample() {
	drawSprite(600,400, &gamestate.tileMasked);
}

void drawBackGround(Texture* texture, short x, short y, short width, short height, short startX, short startY) {
	uObjBg* background = (uObjBg*)getNextObj();
	if (x < 0)
		x = 320 - texture->width / 2;
	if (y < 0)
		y = 240 - texture->height / 2;
	background->b.imagePtr 	= texture->pointer64;
	background->b.frameX 		= x << 2;
	background->b.frameY 		= y << 2;
	background->b.imageX 		= startX << 5;
	background->b.imageY 		= startY << 5;
	background->b.imageW 		= texture->width << 2;
	background->b.imageH 		= texture->height << 2;
	background->b.frameW 		= width << 2;
	background->b.frameH 		= height << 2;
	guS2DInitBg(background);
	gSPBgRectCopy(gfxListPtr++, background);	

}

void drawBackGroundCoordinates(Coordinates* coordinates, short x, short y, short line) {
	uObjBg* background = (uObjBg*)getNextObj();
	if (x < 0)
		x = 320 - coordinates->width / 2;
	if (y < 0)
		y = 240 - coordinates->height / 2;
	background->b.imagePtr 	= coordinates->texture->pointer64;
	background->b.frameX 		= x << 2;
	background->b.frameY 		= y << 2;
	background->b.imageX 		= coordinates->x << 5;
	background->b.imageY 		= (coordinates->y + line * coordinates->height) << 5;
	background->b.imageW 		= coordinates->texture->width << 2;
	background->b.imageH 		= coordinates->texture->height << 2;
	background->b.frameW 		= coordinates->width << 2;
	background->b.frameH 		= coordinates->height << 2;
	guS2DInitBg(background);
	gSPBgRectCopy(gfxListPtr++, background);	
}


void drawFullBackGround(Texture* texture, short x, short y) {
	drawBackGround(texture, x, y, texture->width, texture->height, 0, 0);
}

void drawTitle() {
	drawFullBackGround(gamestate.title64, -1, -1);
	drawFullBackGround(gamestate.titleName, -1, -1);
	//drawFullBackGround(gamestate.titleFrom, -1, 440);
}

void drawTiles() {
	int x, y, centerX, centerY;
	centerX = 320 - gamestate.board.width * 8;
	centerY = 240 - gamestate.board.height * 8;
	for (y =0; y < gamestate.board.height; y++)
		for (x = 0; x < gamestate.board.width; x++)
			drawTile(centerX+x*16, centerY+y*16, &gamestate.board.items[y][x]);
}



