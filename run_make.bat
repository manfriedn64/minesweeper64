set ROOT=c:\ultra
set gccdir=c:\ultra\gcc
set PATH=c:\ultra\gcc\mipse\bin;c:\ultra\usr\sbin
set gccsw=-mips3 -mgp32 -mfp32 -funsigned-char -D_LANGUAGE_C -D_ULTRA64 -D__EXTENSIONS__
set n64align=on
set GCC_CELF=ON
cd C:\Documents and Settings\Administrateur\Bureau\minesweeper64
del *.o *.out
make