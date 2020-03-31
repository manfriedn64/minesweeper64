#ifndef _MINESWEEPER_TEXTURES_
#define _MINESWEEPER_TEXTURES_

typedef struct {
	short	width;
	short	height;
	short	x;
	short	y;
	u32		romStart;
	u32		romEnd;
} QuickTexture;


void initMenuTextures();

#endif /* _MINESWEEPER_TEXTURES_ */