/*======================================================================*/
/*		NuSYS high resolution sample				*/
/*		localdef.h						*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/* 97/12/12	Created by Kensaku Ohki(SLANP)				*/
/*======================================================================*/  
#include "minesweeper_main.h"

#ifndef _LOCALDEF_H_
#define _LOCALDEF_H_

#define	MAIN_HIGH	0x0000
#define	MAIN_LOW	0x0001
#define MAIN_DUMMY	0xFFFF

#define	ZBUFFER_ADDR	(0x80400000-640*480*2*3)
#define CFB_HIGH_ADDR0	(0x80400000-640*480*2*2)
#define CFB_HIGH_ADDR1	(0x80400000-640*480*2*1)


	

//#define BACKGROUND_ADDRESS	((u32*)(ZBUFFER_ADDR-(_backgroundSegmentRomEnd-_backgroundSegmentRomStart)))
#define BACKGROUND_ADDRESS	((u32*)(ZBUFFER_ADDR))
#define TITLE64_ADDRESS		(BACKGROUND_ADDRESS-((u32*)_title64SegmentRomEnd-(u32*)_title64SegmentRomStart))
#define TITLENAME_ADDRESS	(TITLE64_ADDRESS-((u32*)_titleNameSegmentRomEnd-(u32*)_titleNameSegmentRomStart))
#define MENU_ADDRESS		(TITLENAME_ADDRESS-((u32*)_menuSegmentRomEnd-(u32*)_menuSegmentRomStart))


/*
#define BACKGROUND_ADDRESS	((u32*)_codeSegmentEnd)
#define TITLE64_ADDRESS		(BACKGROUND_ADDRESS+((u32*)_backgroundSegmentRomEnd-(u32*)_backgroundSegmentRomStart))
#define TITLENAME_ADDRESS	(TITLE64_ADDRESS+((u32*)_title64SegmentRomEnd-(u32*)_title64SegmentRomStart))
#define MENU_ADDRESS		(TITLENAME_ADDRESS+((u32*)_titleNameSegmentRomEnd-(u32*)_titleNameSegmentRomStart))
*/

/*
 *  Macro for extern declaration of WAVE data segment
 */
#define EXTERN_SEGMENT(name)    \
extern  char    _##name##SegmentStart[], _##name##SegmentEnd[], \
                _##name##SegmentRomStart[], _##name##SegmentRomEnd[]
				
#define EXTERN_SEGMENT_U8(name)    \
extern  u8      _##name##SegmentStart[], _##name##SegmentEnd[], \
                _##name##SegmentRomStart[], _##name##SegmentRomEnd[]

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
EXTERN_SEGMENT_U8(expansionpak_bg);
EXTERN_SEGMENT_U8(expansionpak_txt);


	
#define GAME_STATUS_TITLE   0
#define GAME_STATUS_RUNNING 1
#define GAME_STATUS_OVER    2
#define GAME_STATUS_EXPPAK  3
#define GAME_MENU_NONE      0     
#define GAME_MENU_PAUSE     1
#define GAME_MENU_NEW       2
#define GAME_MENU_CREDITS   3


int frame_number;
/* Buffer for console display */
char conbuf[40];
float random;
//char mem_heap[1024*2100]; // 600 for background + 825ko max for GUI + 373 for title + 105ko for fonts +  2x4ko for tiles + 189ko security for some other stuff and to make it round
char mem_heap[1024*300]; // 90ko for texts + 110ko for ui elements + 2x4ko for tiles + + 92ko security for some other stuff and to make it round

short expansion_pak;

#endif /* _LOCALDEF_H_*/
