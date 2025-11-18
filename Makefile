CC = gcc
OPTION = -W -Wall -pedantic -std=c89 -O2

all: clean clearscreen match

match: main.o initialisation.o plateau.o jeu.o deroulement.o menu.o gestion_menu.o save.o
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` main.o initialisation.o plateau.o jeu.o deroulement.o menu.o gestion_menu.o save.o `pkg-config --libs-only-l MLV` -o match

main.o: main.c initialisation.h plateau.h jeu.h deroulement.h menu.o gestion_menu.o save.o
	$(CC) $(OPTION) main.c -c

initialisation.o: initialisation.c initialisation.h
	$(CC) $(OPTION) initialisation.c -c

plateau.o: plateau.c plateau.h
	$(CC) $(OPTION) plateau.c -c

jeu.o: jeu.c jeu.h
	$(CC) $(OPTION) jeu.c -c

deroulement.o: deroulement.c deroulement.h
	$(CC) $(OPTION) deroulement.c -c

menu.o: menu.c menu.h
	$(CC) $(OPTION) menu.c -c

gestion_menu:o gestion_menu.c gestion_menu.h
	$(CC) $(OPTION) gestion_menu.c -c

save.o: save.c save.h
	$(CC) $(OPTION) save.c -c

clearscreen:
	clear

clean:
	rm -rf *.o *~ match