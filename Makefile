#
# 	NuSystem highreso Program 
#
#	Copyright (C) 1997, NINTENDO Co,Ltd.
#

include $(ROOT)/usr/include/make/PRdefs

#
# NUSYS LIBRARY
#
#
N64KITDIR    = c:\nintendo\n64kit
NUSYSINCDIR  = $(N64KITDIR)/nusys/include
NUSYSLIBDIR  = $(N64KITDIR)/nusys/lib
NUSTDINCDIR  = $(N64KITDIR)/nustd/include
NUSTDLIBDIR  = $(N64KITDIR)/nustd/lib

APP 		=	minesweeper.out

OPTIMIZER 	=	-g

TARGETS 	=	minesweeper.n64

TEXHFILES 	=

HFILES 		= 	localdef.h

CODEFILES   	= 	main.c graphics.c minesweeper.c minesweeper_textures.c

CODEOBJECTS	=	$(CODEFILES:.c=.o) $(NUSYSLIBDIR)/nusys.o

DATAFILES   	=

DATAOBJECTS	=	$(DATAFILES:.c=.o)

CODESEGMENT	=	codesegment.o

OBJECTS		=	$(CODESEGMENT) $(DATAOBJECTS)


LCDEFS = 
LCINCS =	-I. -I$(NUSYSINCDIR) -I$(NUSTDINCDIR)
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib   -L$(NUSYSLIBDIR) -L$(NUAULIBDIR) -lnusys_d  -lultra_d
LCOPTS =	-G 0
LDFLAGS =	$(MKDEPOPT) -L$(ROOT)/usr/lib  -lnusys_d -L$(NUSYSLIBDIR) -lgultra_d  -L$(GCCDIR)/mipse/lib -lkmc -L$(NUSTDLIBDIR) -lnustd
		
LDIRT  =	$(APP)

default:	$(TARGETS)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(TARGETS) $(APP):	spec $(OBJECTS)
		$(MAKEROM)  spec -I$(NUSYSINCDIR) -r $(TARGETS) -e $(APP)
