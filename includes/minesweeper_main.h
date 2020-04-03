#ifndef _MINESWEEPER_
#define _MINESWEEPER_

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


typedef enum
{ False = 0, True = 1 }
Bool;


/* defining a texture */

typedef struct  {
	u32*	pointer32;
	u64*	pointer64;
	u32		romStart;
	u32		romEnd;
	u32		romSize;
	int		width;
	int		height;
	Bool	malloc;
} Texture; 

// defining a tile (a sprite that can be either a background decor or a foreground element */
typedef struct {
	Texture* 	texture;
	int			width;
	int			height;
	int 		x;
	int 		y;
	int			isForeground;
} Tile;


typedef struct {
	int 	red;
	int		green;
	int		blue;
} Rgb;

typedef struct {
	Texture*	texture;
	int			positionY;
	int			scrollX;
	float		speed;
} Background;

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

typedef struct {
	int x;
	int y;
	Texture* texture;
	int width;
	int height;
} Coordinates;

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
	Coordinates coordinates[10][8];
	short width;
	short height;
	short firstTexture;
	short lastTexture;
} LargeSprite;

void initGame();
void sendTexture(int x, int y, Coordinates* coordinates);
void drawSprite(int x, int y, Coordinates* coordinates);
void drawCursor();
void drawMenuNew();
void drawMenuPause();
void drawTile(int x, int y, Item* value);
void drawBackGround(Texture* texture, short x, short y, short width, short height, short startX, short startY);
void drawBackGroundCoordinates(Coordinates* coordinates, short x, short y, short line);
void drawFullBackGround(Texture* texture, short x, short y);
void drawTitle();
void drawTiles();
void drawMenuCredits();

void loadLargeSprite(LargeSprite* largesprite);
void freeLargeSprite(LargeSprite* largesprite);

void controllerInGame();
void controllerNewGame();
void controllerPause();
void controllerGameOver();
void controllerTitle();
void controllerCredits();
void readController();



Texture textures[20];

#endif /* _MINESWEEPER_ */