.PHONY: all doc clean archive

OBJPATH=obj/
SRCPATH=src/
CC = cc
CPPFLAGS += -c
INCLUDE = -I hdr/
CFLAGS += -g -Wall -Wextra
LDFLAGS +=
TARFLAGS += -zcvf
vpath %.c src
vpath %.h hdr
vpath %.o obj
SOURCES=$(wildcard *.c)
HEADERS=$(wildcard *.h)
FILES=$(wildcard *file)
OBJECTS = main.o grille.o io.o jeu.o
EXEC = life
NAME = LifeGame

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
	mv *.o $(OBJPATH)

main.o: $(SRCPATH)main.c
	$(CC) $(CFLAGS) -c $(SRCPATH)main.c $(INCLUDE)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< $(INCLUDE)

doc:
	doxygen Doxyfile
	
clean:
	rm $(OBJECTS) $(EXEC) -f

archive:
	tar $(TARFLAGS) "$(NAME).tar.gz" $(SOURCES) $(HEADERS) $(FILES) grilles/