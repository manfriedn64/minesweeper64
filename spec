/*======================================================================*/
/*		NuSYS hello program					*/
/*		main.c							*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/* 97/09/23	Created by Kensaku Ohki(SLANP)				*/
/*======================================================================*/  
#include "nusys.h"

beginseg
	name	"code"
	flags	BOOT OBJECT
	entry 	nuBoot
	address 0x80000400
	/*stack	nuMainStack + 0x8000
	address NU_SPEC_BOOT_ADDR*/
	stack	NU_SPEC_BOOT_STACK
	include "codesegment.o"
	include "$(ROOT)/usr/lib/PR/rspboot.o"
	include "$(ROOT)/usr/lib/PR/aspMain.o"
	include "$(ROOT)/usr/lib/PR/n_aspMain.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspL3DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.Rej.fifo.o"
        include "$(ROOT)/usr/lib/PR/gspF3DEX2.NoN.fifo.o"
        include "$(ROOT)/usr/lib/PR/gspF3DLX2.Rej.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspS2DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/aspMain.o"
	include "$(ROOT)/usr/lib/PR/n_aspMain.o"
endseg

beginseg
	name	"title64"
	flags	RAW
	include "assets/title/title_64.551"
endseg
beginseg
	name	"titleName"
	flags	RAW
	include "assets/title/title_name.551"
endseg
beginseg
	name	"loser"
	flags	RAW
	include "assets/title/loser.551"
endseg
beginseg
	name	"youwin"
	flags	RAW
	include "assets/title/you_win.551"
endseg
beginseg
	name	"pressStart"
	flags	RAW
	include "assets/title/press_start.551"
endseg

beginseg
	name	"tiles1"
	flags	RAW
	include "assets/tiles/tiles_1.551"
endseg
beginseg
	name	"tiles2"
	flags	RAW
	include "assets/tiles/tiles_2.551"
endseg

beginseg
	name	"background"
	flags	RAW
	include "assets/background/background.551"
endseg

beginseg
	name	"menu"
	flags	RAW
	include "assets/gui/menu.551"
endseg
beginseg
	name	"credits"
	flags	RAW
	include "assets/gui/credits.551"
endseg
beginseg
	name	"button"
	flags	RAW
	include "assets/gui/button.551"
endseg
beginseg
	name	"smallbuttons"
	flags	RAW
	include "assets/gui/small_buttons.551"
endseg

beginseg
	name	"newgamepause"
	flags	RAW
	include "assets/text/newgame_pause.551"
endseg
beginseg
	name	"menutext"
	flags	RAW
	include "assets/text/menu_text.551"
endseg
beginseg
	name	"pausetext"
	flags	RAW
	include "assets/text/pause_text.551"
endseg
beginseg
	name	"numbers"
	flags	RAW
	include "assets/text/numbers.551"
endseg

beginseg
	name	"expansionpakBg"
	flags	RAW
	include "assets/background/expansion_pak.551"
endseg
beginseg
	name	"expansionpakTxt"
	flags	RAW
	include "assets/text/expansion_pak_text.551"
endseg



beginseg
	name	"soundsWbk"
	flags	RAW
	include "assets/sounds/n64st1.wbk"
endseg
beginseg
	name	"soundsSfx"
	flags	RAW
	include "assets/sounds/n64st1.bfx"
endseg
beginseg
	name	"soundsPtr"
	flags	RAW
	include "assets/sounds/n64st1.ptr"
endseg



beginwave
	name	"minesweeper"
	include	"code"
	include	"title64"
	include	"loser"
	include	"youwin"
	include	"pressStart"
	include	"titleName"
	include	"tiles1"
	include	"tiles1"
	include	"background"
	include	"menu"
	include	"credits"
	include	"button"
	include	"smallbuttons"
	include	"newgamepause"
	include	"menutext"
	include	"pausetext"
	include	"numbers"
	include	"expansionpakBg"
	include	"expansionpakTxt"
	
	include	"soundsWbk"
	include	"soundsSfx"
	include	"soundsPtr"
endwave
