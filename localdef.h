/*======================================================================*/
/*	File : localdef.h				                                    */
/*  included by almost all .c files, it defines our global variables    */
/*======================================================================*/  

#ifndef _LOCALDEF_H_
#define _LOCALDEF_H_

#define	ZBUFFER_ADDR	(0x80400000-640*480*2*3)
#define CFB_HIGH_ADDR0	(0x80400000-640*480*2*2)
#define CFB_HIGH_ADDR1	(0x80400000-640*480*2*1)



/* background image is stored in the memory area that should be allocated to the z-buffer. */
#define BACKGROUND_ADDRESS	((u32*)(ZBUFFER_ADDR))
/* we don't really need to store these addresses but it makes the .c code look cleaner  */
#define TITLE64_ADDRESS		(BACKGROUND_ADDRESS-((u32*)_title64SegmentRomEnd-(u32*)_title64SegmentRomStart))
#define TITLENAME_ADDRESS	(TITLE64_ADDRESS-((u32*)_titleNameSegmentRomEnd-(u32*)_titleNameSegmentRomStart))
#define MENU_ADDRESS		(TITLENAME_ADDRESS-((u32*)_menuSegmentRomEnd-(u32*)_menuSegmentRomStart))

/*
 *  Macro for extern declaration of WAVE data segment
 */
#define EXTERN_SEGMENT(name)    \
extern  char    _##name##SegmentStart[], _##name##SegmentEnd[], \
                _##name##SegmentRomStart[], _##name##SegmentRomEnd[]
				
#define EXTERN_SEGMENT_U8(name)    \
extern  u8      _##name##SegmentStart[], _##name##SegmentEnd[], \
                _##name##SegmentRomStart[], _##name##SegmentRomEnd[]

/* this is to know where the segments are in ROM (check initGame() or initExpansionPak() for example) */
EXTERN_SEGMENT(code);
EXTERN_SEGMENT_U8(title64);
EXTERN_SEGMENT_U8(titleName);
EXTERN_SEGMENT_U8(tiles1);
EXTERN_SEGMENT_U8(tiles2);
EXTERN_SEGMENT_U8(background);
EXTERN_SEGMENT_U8(menu);
EXTERN_SEGMENT_U8(credits);
EXTERN_SEGMENT_U8(button);
EXTERN_SEGMENT_U8(smallbuttons);
EXTERN_SEGMENT_U8(newgamepause);
EXTERN_SEGMENT_U8(menutext);
EXTERN_SEGMENT_U8(pausetext);
EXTERN_SEGMENT_U8(numbers);
EXTERN_SEGMENT_U8(expansionpakBg);
EXTERN_SEGMENT_U8(expansionpakTxt);

/* some values definition to make the code more readable */	
#define GAME_STATUS_TITLE   0
#define GAME_STATUS_RUNNING 1
#define GAME_STATUS_OVER    2
#define GAME_STATUS_EXPPAK  3
#define GAME_MENU_NONE      0     
#define GAME_MENU_PAUSE     1
#define GAME_MENU_NEW       2
#define GAME_MENU_CREDITS   3


/* Counter for how many frames were drawn */
int frame_number;
/* Buffer for console display */
char conbuf[40];
/* shared variable for random value (not really need to be shared) */
float random;
/* storing the amount of RAM available. Shared because calling osGetMemSize() clears memory in the expansion pak, so it needs to be done early in the code */
u32 memory_size;
/* dedicated memory area for malloc */
char mem_heap[1024*300]; // 90ko for texts + 110ko for ui elements + 2x4ko for tiles + + 92ko for some other stuff and to make it round

#endif /* _LOCALDEF_H_*/
