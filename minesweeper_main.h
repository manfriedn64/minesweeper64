#ifndef _MINESWEEPER_
#define _MINESWEEPER_

#include "2dlibrary.h"

#define BOARD_MAX_WIDTH 40
#define BOARD_MAX_HEIGHT 30

#define NUMBER_0		0
#define NUMBER_1		1
#define NUMBER_2		2
#define NUMBER_3		3
#define NUMBER_4		4
#define NUMBER_5		5
#define NUMBER_6		6
#define NUMBER_7		7
#define NUMBER_8		8
#define NUMBER_9		9
#define TEXT_WIDTH          0
#define TEXT_HEIGHT         1
#define TEXT_MINES          2
#define TEXT_RESUME         3
#define TEXT_RESTART        4
#define TEXT_NEWGAME        5
#define TEXT_REVEAL         6
#define TEXT_CREDITS        7
#define TEXT_MENU_NEW       8
#define TEXT_MENU_PAUSE     9
#define BUTTON_UP	        0
#define BUTTON_DOWN	        1
#define BUTTON_EMPTY        2
#define BUTTON_CHECK        3
#define BUTTON_LARGE        4


typedef struct {
	Bool isBomb;
	Bool isFlagged;
	Bool isRevealed;
	short number;
} Item;

typedef struct {
	int width;
	int height;
	int nbrMines;
	int nbrLeftToCheck;
	Item items[BOARD_MAX_HEIGHT][BOARD_MAX_WIDTH];
} Board;

typedef struct Panel Panel;
struct Panel {
	Panel* next;
	Panel* previous;
	int value;
	int position;
} ;

typedef struct {
	Panel* first;
	Panel* last;
	int size;
	Panel* allPanels;
} List;

typedef struct {
	short 			backgroundPosition;
	Rgb				backgroundColor;
	Texture*		backgroundTexture;
	Texture*		title64;
	Texture*		titleName;
	Texture*		background;
	Texture*		menuTexture;
	Texture*		menuTitle;
	Coordinates		tileBlank;
	Coordinates		tileMasked;
	Coordinates		redFlag;
	Coordinates		bomb;
	Coordinates		greenFlag;
	Coordinates		numberOne;
	Coordinates		numberTwo;
	Coordinates		numberThree;
	Coordinates		numberFour;
	Coordinates		numberFive;
	Coordinates		numberSix;
	Coordinates	 	numberSeven;
	Coordinates		numberHeight;
	Coordinates 	target;
	Coordinates		text[10];
	Coordinates		numbers[10];
	Coordinates		buttons[5];
	Board			board;
	short			status;
	short			menu;
	Panel*			allPanels;
	short			cursorX;
	short			cursorY;
	short			caseX;
	short			caseY;
	short			newWidth;
	short			newHeight;
	short			newMines;
	Bool			debug;
	
} GameState;

GameState gamestate;


void initGame();

void insertIntoList(List* list, int value);
void removeItemFromList(List* list, Panel* panel);
Panel* findValueInList(List* list, int position);
void incrementNumbers(short x, short y);
void createMines();
void setBoard();
void revealPanel(short x, short y);

void drawCursor();
void drawMenuNew();
void drawMenuPause();
void drawTile(int x, int y, Item* value);
void drawTitle();
void drawTiles();
void drawMenuCredits();

void drawDebug();


Texture textures[20];

#endif /* _MINESWEEPER_ */