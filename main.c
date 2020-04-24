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
#include <nualstl_n.h>

extern int ptr_buf[NU_AU_SAMPLE_SIZE];
extern int sfx_buf[NU_AU_SE_SIZE];
extern musHandle sndHandle;

u16* HighFrameBuf[2] = {
	(u16*)CFB_HIGH_ADDR0,
	(u16*)CFB_HIGH_ADDR1
};

static void callback_prenmi();
static void callbackExpansionPak();
static void callbackGameTitle();
static void callbackGameRunning();
static void callbackGameOver();
static void initAudio();

extern u64 time_lastframe;
extern int frame_number;
extern float random;

extern GameState gamestate;

extern char conbuf[40];
extern char mem_heap[1024*300];

extern u32 memory_size;


extern u8 contPattern;
/*----------------------------------------------------------------------*/
/*	Game startup. 											*/
/*	IN:	Nothing in particular. 							  	*/
/*	RET:	None											  */
/*----------------------------------------------------------------------*/
void mainproc(void* arg)
{
	// expansion pak detection. Needed to play sounds as I was running out of RAM for this feature
	memory_size = osGetMemSize();
	
	// variable initialization used to count frames per second
	time_lastframe = 0;
	frame_number = 0;
	
	// initialize sound if expansion pak is available
	if (memory_size == 0x00800000)
		initAudio();
	
	/* Initialize graphics */
	nuGfxInit();
	random = rand();
	/* Initialize the controller */
	contPattern = nuContInit();
	nuContQueryRead();
	
	 /* Set VI */
	 osCreateViManager(OS_PRIORITY_VIMGR);
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

	//initGame();
	initExpansionPak();
	gamestate.status = GAME_STATUS_EXPPAK;
	
	/* Game main */
	osSetTime(0);
	while(1){
		nuGfxTaskAllEndWait();
		switch (gamestate.status) {
			case GAME_STATUS_EXPPAK:
				nuGfxFuncSet(callbackExpansionPak);
				break;
			case GAME_STATUS_TITLE:
				nuGfxFuncSet(callbackGameTitle);
				break;
			case GAME_STATUS_RUNNING:
				nuGfxFuncSet(callbackGameRunning);
				break;
			case GAME_STATUS_OVER:
			case GAME_STATUS_WON:
				nuGfxFuncSet(callbackGameOver);
				break;
		}
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
	RCPInit();
	if (gamestate.menu == GAME_ANIMATION)
		animateTitle();
	else {
		drawTitle();
		if (gamestate.menu == GAME_MENU_NEW)
			drawMenuNew();
	}
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
	RCPInit();
	drawGameOver();
	if (gamestate.menu == GAME_MENU_NEW)
		drawMenuNew();
	RCPEnd();
}

void initAudio(void)
{
    musConfig c;

    c.control_flag = 0; // Set to MUSCONTROL_RAM if wbk file also placed in RAM
    c.channels = NU_AU_CHANNELS; // Maximum total number of channels
    c.sched = NULL; // The address of the Scheduler structure. NuSystem uses NULL
    c.thread_priority = NU_AU_MGR_THREAD_PRI; // Thread priority (highest)
    //c.heap = (unsigned char*)AUDIO_HEAP_ADDR; // Heap address
    c.heap = (unsigned char*)AUDIO_HEAP_ADDR; // Heap address
    c.heap_length = NU_AU_HEAP_SIZE; // Heap size
    c.ptr = NULL; // Allows you to set a default ptr file
    c.wbk = NULL; // Allows you to set a default wbk file
    c.default_fxbank = NULL; // Allows you to set a default bfx file
    c.fifo_length = NU_AU_FIFO_LENGTH; // The size of the library's FIFO buffer
    c.syn_updates = NU_AU_SYN_UPDATE_MAX; // Number of updates for the synthesizer.
    c.syn_output_rate = 44100; // Audio output rate: 44100hz
    c.syn_rsp_cmds = NU_AU_CLIST_LEN; // Maximum length of the audio command list.
    c.syn_retraceCount = 1; // The number of frames per retrace message
    
    // Number of buffers the Audio Manager can use for DMA from ROM transfer.
    c.syn_num_dma_bufs = NU_AU_DMA_BUFFER_NUM; 
    c.syn_dma_buf_size = NU_AU_DMA_BUFFER_SIZE;

    // Initialize the Audio Manager.
    nuAuStlMgrInit(&c);

    // Register the PRENMI function.
    nuAuPreNMIFuncSet(nuAuPreNMIProc);
	
	nuPiReadRom((u32)_soundsPtrSegmentRomStart, (void *)ptr_buf, (u32)(_soundsPtrSegmentRomEnd-_soundsPtrSegmentRomStart));
	MusPtrBankInitialize(ptr_buf, _soundsWbkSegmentRomStart);
	nuPiReadRom((u32)_soundsSfxSegmentRomStart, (void *)sfx_buf, (u32)(_soundsSfxSegmentRomEnd-_soundsSfxSegmentRomStart));
	MusFxBankInitialize(sfx_buf);

}
