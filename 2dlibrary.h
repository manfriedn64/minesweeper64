#ifndef _2DLIBRARY_
#define _2DLIBRARY_

#define MOVE_OBJECTS_LIMIT	10
#define CENTER				-9999

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
	int x;
	int y;
	Texture* texture;
	int width;
	int height;
} Coordinates;

typedef struct {
	Coordinates		coordinates;
	int				posX;
	int 			posY;
	int				destX;
	int 			destY;
	int				moveX;
	int				moveY;
} MoveObject;

typedef struct {
	short 		width;
	short		height;
	short		ratio;
	u32*	currentTextureInTMEM;
} My2DLibrary;


void initMy2DLibrary(short width, short height);
void moveObjectsListClear();
MoveObject* getNextMoveObjects();
Bool doMoveOject(MoveObject* moveobject);
void drawSprite(int x, int y, Coordinates* coordinates);
void drawBackGroundCoordinates(Coordinates* coordinates, short x, short y, short line);
void drawFullBackGround(Texture* texture, short x, short y);

My2DLibrary	my2dlibrary;

MoveObject	moveOjectsList[MOVE_OBJECTS_LIMIT];
MoveObject*	moveOjectsPointer;
short		moveOjectsCount;

#endif /* _2DLIBRARY_ */