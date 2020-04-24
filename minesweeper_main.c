/*======================================================================*/
/*	File : minesweeper_main.c		                                    */
/*  as its name suppose it to be, it's the main entry point for the     */
/*  game. It contains the game's logic.  */
/*======================================================================*/  

#include  <nusys.h>
#include "localdef.h"
#include "minesweeper_main.h"
#include "2dlibrary.h"
#include <malloc.h>
#include <nualstl_n.h>
#include "assets/sounds/n64st1.h"

//extern Texture textures[20];
extern GameState gamestate;


void initExpansionPak() {
	int i;
	initMy2DLibrary(640, 480);
	textures[0].romStart	= (u32)_expansionpakBgSegmentRomStart;
	textures[0].romEnd		= (u32)_expansionpakBgSegmentRomEnd;
	textures[0].pointer32	= (u32*)BACKGROUND_ADDRESS;
	textures[0].width		= 640;
	textures[0].height		= 480;
	
	textures[1].romStart	= (u32)_expansionpakTxtSegmentRomStart;
	textures[1].romEnd		= (u32)_expansionpakTxtSegmentRomEnd;
	textures[1].pointer32	= (u32*)BACKGROUND_ADDRESS-(textures[1].romEnd-textures[1].romStart);
	textures[1].width		= 304;
	textures[1].height		= 154;
	
	for (i = 0; i <= 1; i++) {
		textures[i].pointer64	= (u64*)textures[i].pointer32;
		textures[i].romSize = textures[i].romEnd - textures[i].romStart;
		nuPiReadRom(textures[i].romStart, textures[i].pointer32, textures[i].romSize);
	}
	gamestate.backgroundColor	= (Rgb){160, 240, 216};
	gamestate.menu = GAME_MENU_NONE; 
	gamestate.cursorX = 1;
	gamestate.cursorY = 1;
	gamestate.debug = False;
	gamestate.background	= &textures[0];
	gamestate.text[TEXT_EXPANSIONPAK]		= (Coordinates){0,  0, &textures[1],   304, 77};
}

void setEndGameTitles() {
	textures[0].romStart	= (u32)_loserSegmentRomStart;
	textures[0].romEnd		= (u32)_loserSegmentRomEnd;
	textures[0].pointer32	= (u32*)TITLE_LOSER_ADDRESS;
	textures[0].width		= 624;
	textures[0].height		= 173;
	textures[0].pointer64	= (u64*)textures[0].pointer32;
	textures[0].romSize		= textures[0].romEnd - textures[0].romStart;
	nuPiReadRom(textures[0].romStart, textures[0].pointer32, textures[0].romSize);
	
	textures[3].romStart	= (u32)_youwinSegmentRomStart;
	textures[3].romEnd		= (u32)_youwinSegmentRomEnd;
	textures[3].pointer32	= (u32*)TITLE_YOUWIN_ADDRESS;
	textures[3].width		= 592;
	textures[3].height		= 101;
	textures[3].pointer64	= (u64*)textures[3].pointer32;
	textures[3].romSize		= textures[3].romEnd - textures[3].romStart;
	nuPiReadRom(textures[3].romStart, textures[3].pointer32, textures[3].romSize);
	gamestate.title64		= NULL;
	gamestate.titleName		= NULL;
	gamestate.loser			= &textures[0];
	gamestate.youwin		= &textures[3];
}
/*
	Initiate graphical elements common within all themes
*/
void initGame() {
	int x, y, i;
	initMy2DLibrary(640, 480);
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
	
	textures[12].romStart	= (u32)_pressStartSegmentRomStart;
	textures[12].romEnd		= (u32)_pressStartSegmentRomEnd;
	textures[12].pointer32	= (u32*)PRESS_START_ADDRESS;
	textures[12].width		= 144;
	textures[12].height		= 26;
	textures[12].malloc		= False;
	
	// now loading from ROM to RAM
	for (i = 0; i <= 12; i++) {
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
	gamestate.backgroundPosition	= 0;
	gamestate.backgroundColor		= (Rgb){160, 240, 216};
	gamestate.title64				= &textures[0];
	gamestate.titleName				= &textures[3];
	gamestate.background			= &textures[4];
	gamestate.menuTitle				= &textures[5];
	gamestate.menuTexture			= &textures[6];
	gamestate.pressStart			= &textures[12];
	gamestate.loser					= NULL;
	gamestate.youwin				= NULL;
	gamestate.debug					= False;
	gamestate.cheat					= False;
	gamestate.rumble				= False;
	gamestate.board.width			= 20;
	gamestate.board.height			= 15;
	gamestate.board.nbrMines		= 10;
	gamestate.status				= GAME_STATUS_TITLE;
	gamestate.menu					= GAME_ANIMATION; 
	initAnimateTitle();
	gamestate.cursorX = 1;
	gamestate.cursorY = 1;
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

void incrementNumbers(short x, short y) {
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
	gamestate.cursorX = my2dlibrary.width / 2;
	gamestate.cursorY = my2dlibrary.height / 2;
	setEndGameTitles();
	
	externalDevicesInit(); // check for rumble pak
}

void revealPanel(short x, short y) {
	short tempX, tempY;
	if (x >= 0 && x < gamestate.board.width && y >= 0 && y < gamestate.board.height)
		if (!gamestate.board.items[y][x].isRevealed) {
			gamestate.board.items[y][x].isRevealed = 1;
			if (gamestate.board.items[y][x].isBomb == 1) {
				if (memory_size == 0x00800000)
					sndHandle = nuAuStlSndPlayerPlay(FX_EXPLODE);
				if (gamestate.rumble) // activate rumble while exploding
					nuContRmbStart(0, 256, 80); 
				gamestate.status = GAME_STATUS_OVER;
			}
			else if (gamestate.board.items[y][x].number > 0 && gamestate.rumble) // activate rumble if close to a bomb
				nuContRmbStart(0, 64, 40);
			gamestate.board.nbrLeftToCheck--;
			if (gamestate.board.nbrLeftToCheck == gamestate.board.nbrMines && gamestate.status != GAME_STATUS_OVER) {
				if (memory_size == 0x00800000)
					sndHandle = nuAuStlSndPlayerPlay(FX_WINNING);
				gamestate.status = GAME_STATUS_WON;
			}
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
	drawFullBackGround(gamestate.menuTexture, CENTER, CENTER);
}

void drawMenuNew() {
	short left, right, top;
	left  = my2dlibrary.width / 2 - gamestate.menuTexture->width  / 2 + 140 / my2dlibrary.ratio;
	right = my2dlibrary.width / 2 + gamestate.menuTexture->width  / 2 - 140 / my2dlibrary.ratio;
	top   = my2dlibrary.height / 2 - gamestate.menuTexture->height / 2 + 90 / my2dlibrary.ratio;
	drawFullBackGround(gamestate.menuTexture, CENTER, CENTER);
	drawBackGroundCoordinates(&gamestate.text[TEXT_MENU_NEW], CENTER, my2dlibrary.height / 2 - gamestate.menuTexture->height/2  + 22, 0);	
	
	drawBackGroundCoordinates(&gamestate.text[TEXT_WIDTH], left, top, 0);
	drawBackGroundCoordinates(&gamestate.buttons[BUTTON_LARGE], right - gamestate.buttons[BUTTON_LARGE].width, top - ((gamestate.buttons[BUTTON_LARGE].height-gamestate.text[TEXT_WIDTH].height) / 2), (gamestate.caseY == 0 ? 1 : 0));
	drawNumber(top, right - 20, gamestate.newWidth, (gamestate.caseY == 0 ? 1 : 0));
	top += 70 / my2dlibrary.ratio;
	drawBackGroundCoordinates(&gamestate.text[TEXT_HEIGHT], left, top, 0);
	drawBackGroundCoordinates(&gamestate.buttons[BUTTON_LARGE], right - gamestate.buttons[BUTTON_LARGE].width, top - ((gamestate.buttons[BUTTON_LARGE].height-gamestate.text[TEXT_WIDTH].height) / 2), (gamestate.caseY == 1 ? 1 : 0));
	drawNumber(top, right - 20, gamestate.newHeight, (gamestate.caseY == 1 ? 1 : 0));
	top += 70 / my2dlibrary.ratio;
	drawBackGroundCoordinates(&gamestate.text[TEXT_MINES], left, top, 0);
	drawBackGroundCoordinates(&gamestate.buttons[BUTTON_LARGE], right - gamestate.buttons[BUTTON_LARGE].width, top - ((gamestate.buttons[BUTTON_LARGE].height-gamestate.text[TEXT_WIDTH].height) / 2), (gamestate.caseY == 2 ? 1 : 0));
	drawNumber(top, right - 20, gamestate.newMines, (gamestate.caseY == 2 ? 1 : 0));	
	// validation button
	top  = my2dlibrary.height / 2 + gamestate.menuTexture->height / 2 - 150 / my2dlibrary.ratio;
	left = my2dlibrary.width / 2 + gamestate.menuTexture->width  / 2 - 120 / my2dlibrary.ratio;
	drawBackGroundCoordinates(&gamestate.buttons[BUTTON_CHECK], left, top, (gamestate.caseY == 3 ? 1 : 0));
}

void drawMenuPause() {
	short left, right, top;
	left  = my2dlibrary.width / 2 - gamestate.menuTexture->width  / 2 + 160 / my2dlibrary.ratio;
	right = my2dlibrary.width / 2 + gamestate.menuTexture->width  / 2 - 160 / my2dlibrary.ratio;
	top   = my2dlibrary.height / 2 - gamestate.menuTexture->height / 2 + 115 / my2dlibrary.ratio;
	drawFullBackGround(gamestate.menuTexture, CENTER, CENTER);
	drawBackGroundCoordinates(&gamestate.text[TEXT_MENU_PAUSE], CENTER, my2dlibrary.height / 2 - gamestate.menuTexture->height/2  + 22, 0);	
	drawBackGroundCoordinates(&gamestate.text[TEXT_RESUME], left - gamestate.text[TEXT_RESUME].width / 2, top, (gamestate.caseY == 0 && gamestate.caseX == 0 ? 1 : 0));
	drawBackGroundCoordinates(&gamestate.text[TEXT_RESTART], right - gamestate.text[TEXT_RESTART].width / 2, top, (gamestate.caseY == 0 && gamestate.caseX == 1 ? 1 : 0));
	top += 60 / my2dlibrary.ratio;
	drawBackGroundCoordinates(&gamestate.text[TEXT_NEWGAME], left - gamestate.text[TEXT_NEWGAME].width / 2, top, (gamestate.caseY == 1 && gamestate.caseX == 0 ? 1 : 0));
	drawBackGroundCoordinates(&gamestate.text[TEXT_REVEAL], right - gamestate.text[TEXT_REVEAL].width / 2, top, (gamestate.caseY == 1 && gamestate.caseX == 1 ? 1 : 0));
	top += 60 / my2dlibrary.ratio;
	drawBackGroundCoordinates(&gamestate.text[TEXT_CREDITS], CENTER, top, (gamestate.caseY == 2 ? 1 : 0));
}

void drawTile(int x, int y, Item* value) {
	if (value->isRevealed || gamestate.status == GAME_STATUS_OVER) {
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
}


void drawExpansionPak() {
	if (memory_size == 0x00800000)
		drawBackGroundCoordinates(&gamestate.text[TEXT_EXPANSIONPAK], CENTER, CENTER, 1);
	else
		drawBackGroundCoordinates(&gamestate.text[TEXT_EXPANSIONPAK], CENTER, CENTER, 0);
}

void drawTitle() {
	drawFullBackGround(gamestate.title64, CENTER, CENTER);
	drawFullBackGround(gamestate.titleName, CENTER, CENTER);
	drawFullBackGround(gamestate.pressStart, CENTER, my2dlibrary.height / 2 + gamestate.title64->height/2 + 10 );
}

void drawTiles() {
	int x, y, centerX, centerY;
	centerX = my2dlibrary.width / 2 - gamestate.board.width * 8;
	centerY = my2dlibrary.height / 2 - gamestate.board.height * 8;
	for (y =0; y < gamestate.board.height; y++)
		for (x = 0; x < gamestate.board.width; x++) 
			drawTile(centerX+x*16, centerY+y*16, &gamestate.board.items[y][x]);
}

void drawGameOver() {
	drawTiles();
	if (gamestate.status == GAME_STATUS_OVER)
		drawFullBackGround(gamestate.loser, CENTER, CENTER);
	else
		drawFullBackGround(gamestate.youwin, CENTER, CENTER);
}

/*
	WARNING : somehow it seems to crash the game is activated while board size is big
	funny to see debug mode to induce a bug :) I guess there is a good reason.
*/
void drawDebug() {
	u64 time_elapsed_u64;
	float time_elapsed_float;
	int fps;
	if (gamestate.debug)  {
		// compute how much time elapsed since the last time we were here
		time_elapsed_u64 = osGetTime();
		time_elapsed_float = (float)(OS_CYCLES_TO_USEC(time_elapsed_u64-time_lastframe)/1000)/1000;
		fps = 1 / time_elapsed_float;
		// set the last frame variable to now()
		time_lastframe = time_elapsed_u64;
		
		nuDebConTextAttr(0, NU_DEB_CON_ATTR_BLINK);
		nuDebConTextColor(0, NU_DEB_CON_TEXT_RED);
		
		nuDebConTextPos(0, 17,1);
		nuDebConPuts(0, "Running");
		nuDebConTextAttr(0, NU_DEB_CON_ATTR_NORMAL);

		nuDebConTextColor(0, NU_DEB_CON_TEXT_YELLOW);
		nuDebConTextPos(0,25,1);
		sprintf(conbuf, "FPS      : %d  ", fps);
		nuDebConCPuts(0, conbuf);
		nuDebConTextColor(0, NU_DEB_CON_TEXT_WHITE);
		nuDebConTextPos(0,25,2);
		sprintf(conbuf, "Time     : %llu ", OS_CYCLES_TO_USEC(time_elapsed_u64)/1000000);
		nuDebConCPuts(0, conbuf);
		nuDebConTextPos(0,25,3);
		sprintf(conbuf, "TV Type  : %d    ", osTvType);
		nuDebConCPuts(0, conbuf);
		nuDebConTextPos(0,25,4);
		sprintf(conbuf, "Cursor X : %d   ", gamestate.cursorX);
		nuDebConCPuts(0, conbuf);
		nuDebConTextPos(0,25,5);
		sprintf(conbuf, "Cursor Y : %d   ", gamestate.cursorY);
		nuDebConCPuts(0, conbuf);
		nuDebConTextPos(0,25,6);
		sprintf(conbuf, "Case X   : %d   ", gamestate.caseX);
		nuDebConCPuts(0, conbuf);
		nuDebConTextPos(0,25,7);
		sprintf(conbuf, "Case Y   : %d   ", gamestate.caseY);
		nuDebConCPuts(0, conbuf);
		nuDebConTextPos(0,25,8);
		sprintf(conbuf, "Status   : %d   ", gamestate.status);
		nuDebConCPuts(0, conbuf);
		nuDebConTextPos(0,25,9);
		sprintf(conbuf, "Menu     : %d   ", gamestate.menu);
		nuDebConCPuts(0, conbuf);
		nuDebConTextPos(0,25,10);
		sprintf(conbuf, "Cheat    : %d   ", gamestate.cheat);
		nuDebConCPuts(0, conbuf);
		nuDebConTextPos(0,25,11);
		sprintf(conbuf, "Rumble   : %d   ", gamestate.rumble);
		nuDebConCPuts(0, conbuf);
		nuDebConTextPos(0,25,12);
		sprintf(conbuf, "pattern  : %d   ", contPattern);
		nuDebConCPuts(0, conbuf);
	}	
}

void initAnimateTitle() {
	gamestate.animateTitle[0] = getNextMoveObjects();
	gamestate.animateTitle[0]-> posX = my2dlibrary.width / 2 - gamestate.title64->width / 2;
	gamestate.animateTitle[0]-> destY = my2dlibrary.height / 2 - gamestate.title64->height/2;
	gamestate.animateTitle[0]-> posY = gamestate.animateTitle[0]-> destY - gamestate.titleName->width;
	gamestate.animateTitle[0]-> moveX = 0;
	gamestate.animateTitle[0]-> moveY = 1;
	gamestate.animateTitle[0]-> destX = gamestate.animateTitle[0]-> posX;
	gamestate.animateTitle[0]-> coordinates = (Coordinates){0, 0, gamestate.title64, 227, 285};

	gamestate.animateTitle[1] = getNextMoveObjects();
	gamestate.animateTitle[1]-> destY = my2dlibrary.height / 2 - gamestate.title64->height/2;
	gamestate.animateTitle[1]-> posX = my2dlibrary.width / 2 + gamestate.title64->width / 2 - 240;
	gamestate.animateTitle[1]-> posY = gamestate.animateTitle[1]-> destY + gamestate.titleName->width;
	gamestate.animateTitle[1]-> moveX = 0;
	gamestate.animateTitle[1]-> moveY = -1;
	gamestate.animateTitle[1]-> destX = gamestate.animateTitle[1]-> posX;
	gamestate.animateTitle[1]-> coordinates = (Coordinates){248, 0, gamestate.title64, 240, 285};
	
	gamestate.animateTitle[2] = getNextMoveObjects();
	gamestate.animateTitle[2]-> posX = gamestate.titleName->width * -1;
	gamestate.animateTitle[2]-> posY = my2dlibrary.height / 2 - gamestate.titleName->height/2;
	gamestate.animateTitle[2]-> moveX = 1;
	gamestate.animateTitle[2]-> moveY = 0;
	gamestate.animateTitle[2]-> destX = my2dlibrary.width / 2 - gamestate.titleName->width / 2;
	gamestate.animateTitle[2]-> destY = gamestate.animateTitle[2]-> posY;
	gamestate.animateTitle[2]-> coordinates = (Coordinates){0, 0, gamestate.titleName, gamestate.titleName->width, gamestate.titleName->height/2};
	gamestate.animateTitle[3] = getNextMoveObjects();

	gamestate.animateTitle[3]-> posX = my2dlibrary.width;
	gamestate.animateTitle[3]-> posY = my2dlibrary.height / 2;
	gamestate.animateTitle[3]-> moveX = -1;
	gamestate.animateTitle[3]-> moveY = 0;
	gamestate.animateTitle[3]-> destX = my2dlibrary.width / 2 - gamestate.titleName->width / 2;
	gamestate.animateTitle[3]-> destY = gamestate.animateTitle[3]-> posY;
	gamestate.animateTitle[3]-> coordinates = (Coordinates){0, 0, gamestate.titleName, gamestate.titleName->width, gamestate.titleName->height/2};
}

void animateTitle() {
	Bool title6, title4, name1, name2;
	title6 = doMoveOject(gamestate.animateTitle[0]);
	title4 = doMoveOject(gamestate.animateTitle[1]);
	name1  = doMoveOject(gamestate.animateTitle[2]);
	name2  = doMoveOject(gamestate.animateTitle[3]);
	drawBackGroundCoordinates(&gamestate.animateTitle[0]->coordinates, gamestate.animateTitle[0]->posX, gamestate.animateTitle[0]->posY, 0);
	drawBackGroundCoordinates(&gamestate.animateTitle[1]->coordinates, gamestate.animateTitle[1]->posX, gamestate.animateTitle[1]->posY, 0);
	drawBackGroundCoordinates(&gamestate.animateTitle[2]->coordinates, gamestate.animateTitle[2]->posX, gamestate.animateTitle[2]->posY, 0);
	drawBackGroundCoordinates(&gamestate.animateTitle[3]->coordinates, gamestate.animateTitle[3]->posX, gamestate.animateTitle[3]->posY, 1);
	if (title4 && title6 && name1 && name2)
		gamestate.menu = GAME_MENU_NONE;
}