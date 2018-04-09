.PHONY: all doc clean archive

vpath %.c src
vpath %.h hdr
vpath %.o obj

OBJPATH=obj/
HDRPATH=hdr/
SRCPATH=src/
CC = cc
CPPFLAGS += -c
INCLUDE = -I hdr/ -I/usr/include/cairo
CPPFLAGS += -Iinclude
CFLAGS += -g -Wall -Wextra
LDFLAGS += -lcairo -lm -lX11
TARFLAGS += -zcvf
SOURCES= main.c gui.c grille.c io.c jeu.c
HEADERS= gui.h io.h grille.h jeu.h
FILES=$(wildcard *file)
OBJECTS_GUI = gui.o grille.o io.o jeu.o
OBJECTS = main.o grille.o io.o jeu.o
EXEC = life
NAME = LifeGame
MODE = GUI

ifeq ($(MODE), TEXTE)
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
	@mv *.o $(OBJPATH)
else
$(EXEC): $(OBJECTS_GUI)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@mv *.o $(OBJPATH)
endif

ifeq ($(MODE), TEXTE)
main.o: $(SRCPATH)main.c
	$(CC) $(CFLAGS) -c $(SRCPATH)main.c $(INCLUDE)
else
gui.o: $(SRCPATH)gui.c
	$(CC) $(CFLAGS) -c $(SRCPATH)gui.c $(INCLUDE)
endif

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< $(INCLUDE)
	
doc:
	doxygen Doxyfile

clean:
	rm $(addprefix $(OBJPATH), $(OBJECTS) $(OBJECTS_GUI)) $(EXEC) -f

archive:
	tar $(TARFLAGS) "$(NAME).tar.gz" $(addprefix $(HDRPATH), $(HEADERS)) $(addprefix $(SRCPATH), $(SOURCES)) $(FILES) grilles/