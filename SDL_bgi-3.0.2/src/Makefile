# Makefile for SDL_bgi
# For GNU/Linux, macOS, and MSYS2 + MinGW-64
# Latest update: April 24, 2024

NAME    = SDL_bgi
SRC     = $(NAME).c
OBJ     = $(NAME).o
HEADER1 = $(NAME).h
HEADER2 = graphics.h
FONTS   = bold.h euro.h goth.h lcom.h litt.h \
	  sans.h scri.h simp.h trip.h tscr.h
MANPAGE = ../doc/graphics.3.gz

PLATFORM := $(shell uname -s | cut -b -7)

ifeq ($(PLATFORM),MINGW64)
USR     = /ucrt64
LIB_DIR = $(USR)/bin
LIB     = $(NAME).dll
LDFLAGS = -lSDL2
PIC     =
else # GNU/Linux, macOS
USR     = /usr
LIB_DIR = $(shell dirname $(shell locate $(LIBSDL2)))
LIB     = lib$(NAME).so
LDFLAGS = -lSDL2
PIC     = -fPIC
endif

INC_DIR = $(USR)/include
LIBSDL2 = libSDL2.a
SDL_INC = $(shell dirname $(shell locate SDL2/SDL.h))
STRIP   = strip -x
MANDIR  = $(USR)/share/man/man3/

# Python support

SDLPY   = sdl_bgi.py
PYTHON  := $(shell python --version | cut -b 8 2> /dev/null)
ifeq ($(PYTHON),3)
  PYUSERSITE := $(shell python -m site --user-site)
  $(shell mkdir -p $(PYUSERSITE))
endif

$(info *** Building on $(PLATFORM) ***)

# C compiler: tested with gcc, clang, and tcc
# tcc is supported on GNU/Linux only:
# CC = tcc -D SDL_DISABLE_IMMINTRIN_H
CC = gcc
# -Wextra
CFLAGS = -O2 -std=gnu99 -g -c -Wall \
	-I $(INC_DIR) -I $(SDL_INC) $(PIC)

.PHONY: all
all: $(LIB)

$(OBJ):	$(SRC) $(FONTS) $(HEADER1)
	$(CC) $(CFLAGS) $(SRC)

$(LIB): $(OBJ)
	$(CC) -shared -o $(LIB) $(OBJ) $(LDFLAGS) ; \
	$(STRIP) $(LIB)

ifdef EMSDK

EMINCLUDE=$(EMSDK)/upstream/emscripten/cache/sysroot/include
EMLIB=$(EMSDK)/upstream/emscripten/cache/sysroot/lib/wasm32-emscripten

wasm: # tested on GNU/Linux only!
	emcc -std=gnu99 -O2 -Wall $(SRC) \
	-s USE_SDL=2 -c -o $(NAME).bc ; \
	emar rcs lib$(NAME).a $(NAME).bc ; \
	/usr/bin/install -m 644 $(HEADER2) $(EMINCLUDE) ; \
	/usr/bin/install -m 644 $(HEADER1) $(EMINCLUDE)/SDL2 ; \
	/usr/bin/install -m 644 lib$(NAME).a $(EMLIB)
unwasm:
	/bin/rm -f $(EMINCLUDE)/$(HEADER2) ; \
	/bin/rm -f $(EMINCLUDE)/SDL2/$(HEADER1) ; \
	/bin/rm -f $(EMLIB)/lib$(NAME).a

endif

install: $(LIB) $(HEADER1)
	/usr/bin/install -m 755 $(LIB) $(LIB_DIR) ; \
	/usr/bin/install -m 644 $(HEADER1) $(SDL_INC) ; \
	/usr/bin/install $(HEADER2) $(INC_DIR) ; \
	/usr/bin/install $(MANPAGE) $(MANDIR)

python:  $(SDLPY)
ifdef PYTHON
	/usr/bin/install $(SDLPY) $(PYUSERSITE)
endif

uninstall:
	/bin/rm -f $(SDL_INC)/$(HEADER1) ; \
	/bin/rm -f $(INC_DIR)/$(HEADER2) ; \
	/bin/rm -f $(LIB_DIR)/$(LIB) ; \
	/bin/rm -f $(PYUSERSITE)/$(SDLPY) ; \
	/bin/rm -f $(MANDIR)/$(MANPAGE)

test: all
	cd ../test; make

clean:
	/bin/rm -f $(OBJ) $(LIB) a.out *.bc *.a *~


# --- end of Makefile
