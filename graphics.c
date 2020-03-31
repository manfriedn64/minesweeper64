/*======================================================================*/
/*		NuSYS high resolution sample						  	*/
/*		graphics.c											*/
/*												   	*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			  	*/
/*		  97/12/08	Created by Kensaku Ohki(SLANP)			*/
/*======================================================================*/
#include <nusys.h>
#include <PR/gs2dex.h>
#include "localdef.h"
#include "minesweeper.h"

#define SCREEN_SIZE_LOW		0
#define SCREEN_SIZE_HIGH	1
#define GFX_LIST_NUM		3
#define GFX_LIST_SIZE		16384
#define OBJ_LIST_SIZE		100
#define SPRITE_LIST_SIZE	3700


typedef struct st_Display {
	u32	width;
	u32	high;
}  ScreenSize;

ScreenSize screen[] = {
	{ 320, 240},
	{ 640, 480}
};

Gfx rdpInit_dl[] = {
	gsDPPipeSync(),
	gsDPPipelineMode(G_PM_1PRIMITIVE),
	gsDPSetTextureLOD(G_TL_TILE),
	gsDPSetTextureLUT(G_TT_NONE),
	gsDPSetTextureDetail(G_TD_CLAMP),
	gsDPSetTexturePersp(G_TP_NONE),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsDPSetTextureConvert(G_TC_FILT),
	gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
	gsDPSetCombineKey(G_CK_NONE),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsDPSetColorDither(G_CD_DISABLE),
	gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0,640, 480),
	gsSPEndDisplayList(),
};

Gfx spriteInit_dl[] = {
	gsDPPipeSync(),
	gsDPSetTexturePersp(G_TP_NONE),
	gsDPSetTextureLOD(G_TL_TILE),
	gsDPSetTextureLUT(G_TT_NONE),
	gsDPSetTextureConvert(G_TC_FILT),
	gsDPSetAlphaCompare(G_AC_THRESHOLD),
	gsDPSetBlendColor(0, 0, 0, 0x01),
	gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
	gsSPEndDisplayList(),
};

uObjBg	objList[OBJ_LIST_SIZE];
uObjBg* objListPrt;
int objListCnt = 0;

uObjSprite	spriteList[SPRITE_LIST_SIZE];
uObjSprite*	spriteListPtr;
int spriteListCnt = 0;

Gfx	gfxListBuf[GFX_LIST_NUM][GFX_LIST_SIZE];
u32	gfxListCnt = 0;
Gfx*	gfxListPtr;
Gfx*	gfxListStartPtr;

u32 	hireso;
extern u32 mainNo;

/*----------------------------------------------------------------------*/
/*	Clear the frame buffer. 								*/
/*	IN:	**glist_ptr										  */
/*		screen		Screen size 					  	*/
/*			SCREEN_SIZE_LOW	 0							*/
/*			SCREEN_SIZE_HIGH 1					  		*/
/*	RET:	None										   	*/
/*----------------------------------------------------------------------*/
void gfxClearCfb(u32 size)
{
	ScreenSize* screenPtr;
	
	screenPtr = &screen[size];

	gSPSegment(gfxListPtr++, 0, 0x0);

	gDPSetCycleType(gfxListPtr++, G_CYC_FILL);
	
	/* Clear the Z buffer. */
	gDPSetDepthImage(gfxListPtr++, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
	
	gDPSetColorImage(gfxListPtr++, G_IM_FMT_RGBA, G_IM_SIZ_16b,
			 screenPtr->width,
			 OS_K0_TO_PHYSICAL(nuGfxZBuffer));
	gDPSetFillColor(gfxListPtr++,(GPACK_ZDZ(G_MAXFBZ,0) << 16 |
				  GPACK_ZDZ(G_MAXFBZ,0)));
	gDPFillRectangle(gfxListPtr++, 0, 0, screen->width-1, screenPtr->high-1);

	gDPPipeSync(gfxListPtr++);


	gDPSetColorImage(gfxListPtr++, G_IM_FMT_RGBA, G_IM_SIZ_16b,
			 screenPtr->width,
			 OS_K0_TO_PHYSICAL(nuGfxCfb_ptr)); 
	gDPSetFillColor(gfxListPtr++, (GPACK_RGBA5551(gamestate.backgroundColor.red, gamestate.backgroundColor.green, gamestate.backgroundColor.blue, 1) << 16
					 | GPACK_RGBA5551(gamestate.backgroundColor.red, gamestate.backgroundColor.green, gamestate.backgroundColor.blue, 1)));
	gDPFillRectangle(gfxListPtr++, 0, 0,
			 screenPtr->width-1, screenPtr->high - 1);
	gDPPipeSync(gfxListPtr++);

}

/*----------------------------------------------------------------------*/
/*	Change the display list buffer. 							*/
/*	IN:	None												*/
/*	RET:	Pointer to the display list buffer.		   			*/
/*----------------------------------------------------------------------*/
void gfxListBufferChange(void)
{
	gfxListStartPtr = &gfxListBuf[gfxListCnt][0];
	gfxListPtr = gfxListStartPtr;
	gfxListCnt++;
	gfxListCnt %= GFX_LIST_NUM;
	return;
}

void objListClear(void)
{
	objListPrt = &objList[0];
	objListCnt = 0;
	return;
}

uObjBg* getNextObj()
{
	if (objListCnt < OBJ_LIST_SIZE)
		objListPrt = &objList[objListCnt++];
		//objListPrt->b.imageLoad 	= G_BGLT_LOADBLOCK;
		objListPrt->b.imageLoad 	= G_BGLT_LOADTILE;
		objListPrt->b.imageFmt 		= G_IM_FMT_RGBA;
		objListPrt->b.imageSiz 		= G_IM_SIZ_16b;
		objListPrt->b.imagePal 		= 0;
		objListPrt->b.imageFlip 	= 0;
		return objListPrt;
	return 0;
}

void spriteListClear(void)
{
	spriteListPtr = &spriteList[0];
	spriteListCnt = 0;
	return;
}

uObjSprite* getNextSprite()
{
	// typedef struct {
	  // s16 objX;        /* x-coordinate of upper-left corner of OBJ (s10.2) */
	  // u16 scaleW;      /* Width-direction scaling (u5.10) */
	  // u16 imageW;      /* Texture width (length in s direction, u10.5)   */
	  // u16 paddingX;    /* Unused (always 0)  */
	  // s16 objY;        /* y-coordinate of upper-left corner of OBJ (s10.2)  */
	  // u16 scaleH;      /* Height-direction scaling (u5.10) */
	  // u16 imageH;      /* Texture height (length in t direction, u10.5)  */
	  // u16 paddingY;    /* Unused (always 0) */
	  // u16 imageStride; /* Texel wrapping width (In units of 64-bit words)  */
	  // u16 imageAdrs;   /* Texture starting position in TMEM (In units of 64-bit words)  */  
	  // u8  imageFmt;    /* Texel format
						  // G_IM_FMT_RGBA (RGBA format)
						  // G_IM_FMT_YUV (YUV format)
						  // G_IM_FMT_CI (CI format)
						  // G_IM_FMT_IA (IA format)
						  // G_IM_FMT_I (I format)*/
	  // u8  imageSiz;    /* Texel size
						  // G_IM_SIZ_4b (4 bits/texel)
						  // G_IM_SIZ_8b (8 bits/texel)
						  // G_IM_SIZ_16b (16 bits/texel)
						  // G_IM_SIZ_32b (32 bits/texel) */
	  // u16 imagePal;    /* Position of palette for 4-bit color
						  // index texture  (4-bit precision, 0~7)   */
	  // u8  imageFlags;  /* Display flag
						  // (*) Multiple flags can be specified as the bit sum of the flags: 
						  // 0 (Normal display (no inversion))
						  // G_OBJ_FLAG_FLIPS (s-direction (x) inversion)
						  // G_OBJ_FLAG_FLIPT  (t-direction (y) inversion)  */
	// } uObjSprite_t;    /* 24 bytes */
	if (spriteListCnt < SPRITE_LIST_SIZE) {
		spriteListPtr = &spriteList[spriteListCnt++];
		spriteListPtr->s.paddingX 		= 0;
		spriteListPtr->s.paddingY 		= 0;
		spriteListPtr->s.imageFmt 		= G_IM_FMT_RGBA;
		spriteListPtr->s.imageSiz 		= G_IM_SIZ_16b;
		spriteListPtr->s.imagePal 		= 0;
		spriteListPtr->s.imageFlags		= 0;
		spriteListPtr->s.scaleH			= 1 << 10;
		spriteListPtr->s.scaleW			= 1 << 10;
	}
	else
		return 0;
}

/*----------------------------------------------------------------------*/
/*	High resolution display							  	*/
/*	IN:	taskNum	Number of tasks remaining				*/
/*	RET:	None										  	*/
/*----------------------------------------------------------------------*/
void graphic(u32 taskNum)
{
	/* Do not process if the tasks are not finished. */ 
	if(nuGfxTaskSpool) return;
	
	/* Set the display list buffer. */
	gfxListBufferChange();
	gSPDisplayList(gfxListPtr++, rdpInit_dl);
    gDPSetDepthSource(gfxListPtr++, G_ZS_PRIM);
	/* Clear the screen. */
	gfxClearCfb(hireso);

	/* end top-level display list */
	gDPFullSync(gfxListPtr++);
	gSPEndDisplayList(gfxListPtr++);
	
	nuGfxTaskStart(gfxListStartPtr, gfxListPtr - gfxListStartPtr, NU_GFX_UCODE_S2DEX,NU_SC_NOSWAPBUFFER);
	gfxListBufferChange();
	
	/* before drawing any sprite, first clear / init the list of uObjBg that we will be using */
	objListClear();
	spriteListClear();
	gSPDisplayList(gfxListPtr++, rdpInit_dl);
	gSPDisplayList(gfxListPtr++, spriteInit_dl);
	gDPSetRenderMode(gfxListPtr++, G_RM_SPRITE, G_RM_SPRITE2);
	gDPSetCycleType(gfxListPtr++, G_CYC_COPY);
	gDPSetTextureFilter(gfxListPtr++, G_TF_POINT);
	
	/* now run all the drawing sprite functions */
	drawFullBackGround(gamestate.background, -1, -1);
	switch (gamestate.status) {
		case GAME_STATUS_TITLE:
			drawTitle();
			break;
		case GAME_STATUS_RUNNING:
			drawTiles();
			drawCursor();
			break;
		case GAME_STATUS_OVER:
			drawTiles();
			break;
	}
	switch (gamestate.menu) {
		case GAME_MENU_PAUSE:
			drawMenuPause();
			break;
		case GAME_MENU_NEW:
			drawMenuNew();
			break;
		case GAME_MENU_CREDITS:
			drawMenuCredits();
			break;
	}

	/*if (gamestate.status == 0) {
		drawTitle();
	}
	if (gamestate.status > 0) {
		drawTiles();
		
		drawCursor();
	}*/
	gDPFullSync(gfxListPtr++);
	
	/* end top-level display list */
	
	gSPEndDisplayList(gfxListPtr++);
	
	nuGfxTaskStart(gfxListStartPtr, gfxListPtr - gfxListStartPtr, NU_GFX_UCODE_S2DEX,NU_SC_NOSWAPBUFFER);
	
	
	//gfxListBufferChange();
	
	
	/* debug bar + blink message to check it's running */
	
	nuDebConDisp(NU_SC_NOSWAPBUFFER);
	
	nuDebTaskPerfBar1(1, 480, NU_SC_SWAPBUFFER);
	
	nuDebConTextAttr(0, NU_DEB_CON_ATTR_BLINK);
	nuDebConTextColor(0, NU_DEB_CON_TEXT_RED);
	nuDebConTextPos(0, 17,0);
	nuDebConPuts(0, "Running");
	nuDebConTextAttr(0, NU_DEB_CON_ATTR_NORMAL);
	
	
	
	nuDebConTextPos(0,3,21);
	sprintf(conbuf, "End of code : 0x%X", _codeSegmentEnd);
	nuDebConCPuts(0, conbuf);
	nuDebConTextPos(0,3,22);
	sprintf(conbuf, "BACKGROUND_ADDRESS : 0x%X", BACKGROUND_ADDRESS);
	nuDebConCPuts(0, conbuf);
	nuDebConTextPos(0,3,23);
	sprintf(conbuf, "ZBUFFER : 0x%X", ZBUFFER_ADDR);
	nuDebConCPuts(0, conbuf);
	nuDebConTextPos(0,3,24);
	sprintf(conbuf, "FBUFFER start : 0x%X", CFB_HIGH_ADDR0);
	nuDebConCPuts(0, conbuf);
	nuDebConTextPos(0,3,25);
	sprintf(conbuf, "FBUFFER end : 0x%X", AUDIO_HEAP_ADDR);
	nuDebConCPuts(0, conbuf);
	/*
	nuDebConTextPos(0,3,26);
	sprintf(conbuf, "Frame Number : %d", frame_number);
	nuDebConCPuts(0, conbuf);
	nuDebConTextPos(0,3,27);
	sprintf(conbuf, "Random : %f", random);
	nuDebConCPuts(0, conbuf);
	nuDebConTextPos(0,3,28);
	sprintf(conbuf, "Seed : %d", osGetCount() % 10000000);
	nuDebConCPuts(0, conbuf);
	*/
	
	
	/*nuDebConTextPos(0,3,28);
	sprintf(conbuf, "Gfx : %d", sizeof(Gfx));
	nuDebConCPuts(0, conbuf);*/
	/*nuDebConTextPos(0,3,10);
	sprintf(conbuf, "gfxList Pointer : %X", gfxListPtr);
	nuDebConCPuts(0, conbuf);
	nuDebConTextPos(0,3,11);
	sprintf(conbuf, "gfxList Starter : %X", &gfxListBuf[gfxListCnt-1][0]);
	nuDebConCPuts(0, conbuf);*/
	/*nuDebConTextPos(0,3,28);
	sprintf(conbuf, "mem_heap : 0x%X", &mem_heap);
	nuDebConCPuts(0, conbuf);*/
	/*
	nuDebConTextPos(0,25,5);
	sprintf(conbuf, "Cursor X : %d   ", gamestate.cursorX);
	nuDebConCPuts(0, conbuf);
	nuDebConTextPos(0,25,6);
	sprintf(conbuf, "Cursor Y : %d   ", gamestate.cursorY);
	nuDebConCPuts(0, conbuf);
	nuDebConTextPos(0,25,7);
	sprintf(conbuf, "Case X   : %d   ", gamestate.caseX);
	nuDebConCPuts(0, conbuf);
	nuDebConTextPos(0,25,8);
	sprintf(conbuf, "Case Y   : %d   ", gamestate.caseY);
	nuDebConCPuts(0, conbuf);
	
	nuDebConTextPos(0,25,9);
	sprintf(conbuf, "Status   : %d   ", gamestate.status);
	nuDebConCPuts(0, conbuf);
	nuDebConTextPos(0,25,10);
	sprintf(conbuf, "Menu     : %d   ", gamestate.menu);
	nuDebConCPuts(0, conbuf);*/
	
	readController();
	frame_number++;
}

