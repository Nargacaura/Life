.PHONY: doc clean archive

vpath %.c src
vpath %.h hdr
vpath %.o obj
vpath *.a lib

OBJPATH=obj/
HDRPATH=hdr/
SRCPATH=src/
LIBPATH=lib/
CC = cc
CPPFLAGS += -c
INCLUDE = -I hdr/ -I/usr/include/cairo
CPPFLAGS += -Iinclude
CFLAGS += -g -Wall -Wextra
LDTEXT += -L -ljeu
LDFLAGS += -lcairo -lm -lX11 -L -ljeu
TARFLAGS += -zcvf
SOURCES= main.c gui.c grille.c io.c jeu.c
HEADERS= gui.h io.h grille.h jeu.h
FILES=$(wildcard *file)
LIBOBJ = grille.o io.o jeu.o
EXEC = life
NAME = LifeGame
MODE = GUI

ifeq ($(MODE), TEXTE)
$(EXEC): main.o libjeu.a
	$(CC) $(CFLAGS) -o $@ $^ $(LDTEXT)
	@mv *.a $(LIBPATH)
	@mv *.o $(OBJPATH)	
else
$(EXEC): gui.o libjeu.a
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@mv *.a $(LIBPATH)
	@mv *.o $(OBJPATH)
endif

libjeu.a: $(LIBOBJ)
	ar -crv libjeu.a $^

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
	rm $(addprefix $(OBJPATH), $(LIBOBJ) gui.o main.o) $(LIBPATH)* $(EXEC) -f

archive:
	tar $(TARFLAGS) "$(NAME).tar.gz" $(addprefix $(HDRPATH), $(HEADERS)) $(addprefix $(SRCPATH), $(SOURCES)) $(FILES) grilles/