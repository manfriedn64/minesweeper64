#include  <nusys.h>
#include "2dlibrary.h"

extern Gfx*	gfxListPtr;
extern Gfx*	gfxListPtr;
extern My2DLibrary my2dlibrary;

void initMy2DLibrary(short width, short height) {
	my2dlibrary.currentTextureInTMEM	= NULL;
	my2dlibrary.width					= width;
	my2dlibrary.height					= height;
	my2dlibrary.ratio					= 640 / width;
}

void drawSprite(int x, int y, Coordinates* coordinates) {
	//imageAdrs = GS_PIX2TMEM ((s-coordinate in TMEM) + (t-coordinate in TMEM) * (texture width at the time of loading, G_IM_SIZ_*))
	//imageStride = GS_PIX2TMEM (texture width at the time of loading, G_IM_SIZ_*)
	uObjSprite* sprite;
	// load texture to TMEM if not the current one
	if (my2dlibrary.currentTextureInTMEM != coordinates->texture->pointer32) {
		gDPLoadTextureBlock(
			gfxListPtr++, 
			coordinates->texture->pointer32, 
			G_IM_FMT_RGBA, G_IM_SIZ_16b, 
			coordinates->texture->width, coordinates->texture->height, 0, 
			G_TX_WRAP, G_TX_WRAP, 
			G_TX_NOMASK, G_TX_NOMASK, 
			G_TX_NOLOD, G_TX_NOLOD
		);
		my2dlibrary.currentTextureInTMEM = coordinates->texture->pointer32;
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

void drawBackGroundCoordinates(Coordinates* coordinates, short x, short y, short line) {
	uObjBg* background = (uObjBg*)getNextObj();
	if (x < 0)
		x = my2dlibrary.width / 2 - coordinates->width / 2;
	if (y < 0)
		y = my2dlibrary.height / 2 - coordinates->height / 2;
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
	Coordinates coordinates = (Coordinates){0, 0, texture, texture->width, texture->height};
	//drawBackGround(texture, x, y, texture->width, texture->height, 0, 0);
	drawBackGroundCoordinates(&coordinates, x, y, 0);
}
