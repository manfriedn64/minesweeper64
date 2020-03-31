/*======================================================================*/
/*		NuSYS high resolution sample					 		*/
/*		main.c								  		*/
/*												  	*/
/*		Copyright (C) 1997, NINTENDO Co, Ltd.			 		*/
/*		  97/12/08	Created by Kensaku Ohki(SLANP)			*/
/*======================================================================*/  
#include <nusys.h>
#include "localdef.h"
#include "minesweeper.h"


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

u32 mainNo;
void setupHigh(void);
void setupLow(void);
static void callback_prenmi();

extern void graphic(u32 taskNum);
extern void audioInit(void);
extern u32 hireso;
extern int frame_number;
extern float random;

extern GameState gamestate;

extern char conbuf[40];
extern char mem_heap[1024*400];


/*----------------------------------------------------------------------*/
/*	Game startup. 											*/
/*	IN:	Nothing in particular. 							  	*/
/*	RET:	None											  */
/*----------------------------------------------------------------------*/
void mainproc(void* arg)
{
	frame_number = 0;
	/* Initialize graphics */
	nuGfxInit();
	random = rand();
	osSetTime(0);
	/* Initialize the controller */
	nuContInit();

	 /* Set VI */
	osViSetMode(&osViModeTable[OS_VI_NTSC_HAN1]);
	osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
	//osViSetYScale(0.833);
	nuPreNMIFuncSet((NUScPreNMIFunc)callback_prenmi);
	
	/* Since osViBlack becomes FALSE when the VI mode is changed, */
	/* set the screen display to OFF again. 					*/
	nuGfxDisplayOff();

	/* Set the frame buffer address */
	nuGfxSetCfb(HighFrameBuf, 2);
	
	/* Set the Z buffer address */
	nuGfxSetZBuffer((u16*)(ZBUFFER_ADDR));
	
	if (InitHeap(mem_heap, sizeof(mem_heap)) == -1)
        return;
	
	/* High resolution at the start */
	mainNo = MAIN_HIGH;

	initGame();
	
	
	/* Game main */
	while(1){
	switch(mainNo){
	case MAIN_HIGH:	/* High resolution */
		setupHigh();
		mainNo = MAIN_DUMMY;
		break;
		
	case MAIN_LOW: 	/* Low resolution */
		setupHigh();
		mainNo = MAIN_DUMMY;
		break;
		
	case MAIN_DUMMY:	/* Dummy */
		break;
		
	default:
		break;
	}
	}
}

/*----------------------------------------------------------------------*/
/*	setupHigh - Set high resolution. 			  				*/
/*	IN:	Nothing in particular. 								*/
/*	RET:	None												*/
/*----------------------------------------------------------------------*/
void setupHigh(void)
{
	/* Wait for all tasks to end */
	nuGfxTaskAllEndWait();
	
	nuDebConClear(0);

	/* Screen display ON */
	hireso  = 1;
	
	/* Register the callback function */
	nuGfxFuncSet(graphic);
	nuGfxDisplayOn();
}


void callback_prenmi()
{
	nuGfxDisplayOff();
	osViSetYScale(1);
}

