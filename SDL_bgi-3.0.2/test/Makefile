# Makefile for test commands

# C compiler: gcc, clang, or tcc
# CC = tcc -w -D SDL_DISABLE_IMMINTRIN_H
CC = gcc

# Detect the platform: GNU/Linux, Darwin (macOS), Mingw-w64
PLATFORM := $(shell uname -s | cut -b -7)

ifeq ($(PLATFORM),MINGW64)
CFLAGS = -std=gnu99 -O2 -g -I. -I/ucrt64/include -I/ucrt64/include/SDL2 -Wall
LIBS = -lmingw32 -L/ucrt64/bin -lSDL_bgi -lSDL2main -lSDL2 -lm # -mwindows
# -mconsole = open a console alongside the program
# -mwindows = window-only program (no console)
else # GNU/Linux, macOS
CFLAGS = -std=gnu99 -O2 -g -I. -I/usr/include/SDL2 -I/usr/local/include -Wall 
LIBS = -lSDL_bgi -lSDL2
endif

PROGRAMS = arc bar3d bar circle cleardevice clearviewport closegraph \
	   delay detectgraph drawpoly ellipse fillellipse fillpoly \
	   floodfill getarccoords getaspectratio getbkcolor getcolor \
	   getdefaultpalette getdrivername getfillpattern \
	   getfillsettings getgraphmode getimage getlinesettings \
	   getmaxcolor getmaxmode getmaxx getmaxy getmodename \
	   getmoderange getpalette getpalettesize getpixel \
	   gettextsettings getvisualpage getviewsettings getx gety \
	   graphdefaults grapherrormsg graphresult imagesize initgraph \
	   installuserfont kbhit line linerel lineto moverel moveto \
	   outtext outtextxy pieslice putimage putpixel rectangle \
	   restorecrtmode sector setactivepage setallpalette \
	   setaspectratio setbkcolor setcolor setfillpattern  \
	   setfillstyle setgraphbufsize setgraphmode setlinestyle  \
	   setpalette settextjustify settextstyle setusercharsize \
	   setviewport setvisualpage setwritemode textheight \
	   textwidth

all: $(PROGRAMS)

$(PROGRAMS): %: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	/bin/rm -f $(PROGRAMS)

# --- end of Makefile
