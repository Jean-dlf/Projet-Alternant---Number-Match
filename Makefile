CC = gcc
OPTION = -W -Wall -pedantic -std=c89 -O2

all: clean clearscreen match

match: main.o initialisation.o plateau.o jeu.o
	$(CC) $(OPTION) main.o initialisation.o plateau.o jeu.o -o match

main.o: main.c initialisation.h plateau.h jeu.h
	$(CC) $(OPTION) main.c -c

initialisation.o: initialisation.c initialisation.h
	$(CC) $(OPTION) initialisation.c -c

plateau.o: plateau.c plateau.h
	$(CC) $(OPTION) plateau.c -c

jeu.o: jeu.c jeu.h
	$(CC) $(OPTION) jeu.c -c

clearscreen:
	clear

clean:
	rm -rf *.o *~ match