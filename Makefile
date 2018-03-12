.PHONY: all clean archive

CC = cc
CPPFLAGS += -c
CFLAGS += -g -Wall -Wextra
LDFLAGS +=
TARFLAGS += -zcvf
SOURCES=$(wildcard *.c)
HEADERS=$(wildcard *.h)
FILES=$(wildcard *file)
OBJECTS=$(SOURCES:.c=.o)
EXEC = life
NAME = LifeGame
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

main.o: main.c grille.h io.h jeu.h
grille.o: grille.c grille.h
io.o: io.c io.h
jeu: jeu.c jeu.h

%o: %c
	$(CC) $(CPPFLAGS) $(CFLAGS) $<

doc:
	doxygen Doxyfile
	
clean:
	rm $(OBJECTS) $(EXEC) doc -f

archive:
	tar $(TARFLAGS) "$(NAME).tar.gz" $(SOURCES) $(HEADERS) $(FILES) grilles/