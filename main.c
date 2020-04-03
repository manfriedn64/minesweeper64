/*======================================================================*/
/*		NuSYS high resolution sample					 		*/
/*		main.c								  		*/
/*												  	*/
/*		Copyright (C) 1997, NINTENDO Co, Ltd.			 		*/
/*		  97/12/08	Created by Kensaku Ohki(SLANP)			*/
/*======================================================================*/  
#include <nusys.h>
#include "localdef.h"
#include "minesweeper_main.h"


/*----------------------------------------------------------------------*/
/*	Memory mapping 	*/
/*	 0x80000000 +------------------+ */
/*				|      System      | */
/*   0x80000400 |------------------| */
/*				|                  | */
/*				| Collision-Buffer | */
/*				|                  | */
/*   0x80025c00 |------------------| */
/*				|                  | */
/*				|       Code       | */
/*				|                  | */
/*   0x800FB050 |------------------| */
/*				|                  | */
/*				|       Data       | */
/*				|                  | */
/*   0x804A2370 |------------------| */
/*				|                  | */
/*				|      Empty       | */
/*				|                  | */
/*   0x805BE000 |------------------| */
/*				|                  | */
/*				|     Z-Buffer     | */
/*				|                  | */
/*   0x08654000 |------------------| */
/*				|                  | */
/*				|   Frame-Buffer   | */
/*				|                  | */
/*   0x80780000 |------------------| */
/*				|                  | */
/*				|    Audio-Heap    | */
/*				|                  | */
/*   0x003FFFFF |------------------| */
/*----------------------------------------------------------------------*/

/* High resolution frame buffer address array. */
u16* HighFrameBuf[2] = {
	(u16*)CFB_HIGH_ADDR0,
	(u16*)CFB_HIGH_ADDR1
};

static void callback_prenmi();
static void callbackExpansionPak();
static void callbackGameTitle();
static void callbackGameRunning();
static void callbackGameOver();

extern void audioInit(void);
extern int frame_number;
extern float random;

extern GameState gamestate;

extern char conbuf[40];
extern char mem_heap[1024*300];
extern short expansion_pak;

u32 memory_size;

/*----------------------------------------------------------------------*/
/*	Game startup. 											*/
/*	IN:	Nothing in particular. 							  	*/
/*	RET:	None											  */
/*----------------------------------------------------------------------*/
void mainproc(void* arg)
{
	memory_size = osGetMemSize();
	if (memory_size == 0x00800000)
		expansion_pak = 1;
	else
		expansion_pak = 0;
	frame_number = 0;
	gamestate.status = GAME_STATUS_EXPPAK;
	/* Initialize graphics */
	nuGfxInit();
	random = rand();
	osSetTime(0);
	/* Initialize the controller */
	nuContInit();

	 /* Set VI */
	 if (osTvType == OS_TV_PAL ) {
		osViSetMode(&osViModeTable[OS_VI_PAL_HAN1]);
		osViSetYScale(0.833);
		nuPreNMIFuncSet((NUScPreNMIFunc)callback_prenmi);
	 }
	 else if (osTvType == OS_TV_MPAL )
		osViSetMode(&osViModeTable[OS_VI_MPAL_HAN1]); 
	else
		osViSetMode(&osViModeTable[OS_VI_NTSC_HAN1]); 
	osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
	
	/* Since osViBlack becomes FALSE when the VI mode is changed, */
	/* set the screen display to OFF again. 					*/
	nuGfxDisplayOff();

	/* Set the frame buffer address */
	nuGfxSetCfb(HighFrameBuf, 2);
	
	/* Set the Z buffer address 
	We won't use it, but I prefer to set it somewhere it won't hurt if for any reason it comes to be used inadvertently
	*/
	nuGfxSetZBuffer((u16*)(ZBUFFER_ADDR));
	
	if (InitHeap(mem_heap, sizeof(mem_heap)) == -1)
        return;

	initGame();
	
	/* Game main */
	while(1){
		nuGfxTaskAllEndWait();
		switch (gamestate.status) {
			case GAME_STATUS_TITLE:
				nuGfxFuncSet(callbackGameTitle);
				break;
			case GAME_STATUS_RUNNING:
				nuGfxFuncSet(callbackGameRunning);
				break;
			case GAME_STATUS_OVER:
				nuGfxFuncSet(callbackGameOver);
				break;
		}
		readController();
		nuGfxDisplayOn();
		
	}
}

/*----------------------------------------------------------------------*/
/*	setupHigh - Set high resolution. 			  				*/
/*	IN:	Nothing in particular. 								*/
/*	RET:	None												*/
/*----------------------------------------------------------------------*/


void callback_prenmi()
{
	nuGfxDisplayOff();
	osViSetYScale(1);
}

void callbackGameTitle(u32 taskNum) {
	/* Do not process if the tasks are not finished.  Any reference to "nuGfxTaskSpool" MUST be inside a nuGfxFuncSet callback function. Otherwise hardware crashes */ 
	if(nuGfxTaskSpool) return;
	//readController();
	RCPInit();
	drawTitle();
	if (gamestate.menu == GAME_MENU_NEW)
		drawMenuNew();
	RCPEnd();
}

void callbackExpansionPak() {
	/* Do not process if the tasks are not finished.  Any reference to "nuGfxTaskSpool" MUST be inside a nuGfxFuncSet callback function. Otherwise hardware crashes */ 
	if(nuGfxTaskSpool) return;
	RCPInit();
	drawExpansionPak();
	RCPEnd();
		
	
}

void callbackGameRunning() {
	/* Do not process if the tasks are not finished.  Any reference to "nuGfxTaskSpool" MUST be inside a nuGfxFuncSet callback function. Otherwise hardware crashes */ 
	if(nuGfxTaskSpool) return;
	//readController();
	RCPInit();
	drawTiles();
	drawCursor();
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
	RCPEnd();
}

void callbackGameOver() {
	/* Do not process if the tasks are not finished.  Any reference to "nuGfxTaskSpool" MUST be inside a nuGfxFuncSet callback function. Otherwise hardware crashes */ 
	if(nuGfxTaskSpool) return;
	//readController();
	RCPInit();

	drawTiles();
	if (gamestate.menu == GAME_MENU_NEW)
		drawMenuNew();
	RCPEnd();
}
