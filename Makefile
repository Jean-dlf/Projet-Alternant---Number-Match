CC = gcc
OPTION = -W -Wall -pedantic -std=c89 -O2

all: clean clearscreen match

match: main.o initialisation.o plateau.o game_logic.o game.o menu.o menu_management.o save.o plateau_mlv.o mlv.o
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` main.o initialisation.o plateau.o game_logic.o game.o menu.o menu_management.o save.o plateau_mlv.o mlv.o `pkg-config --libs-only-l MLV` -o match

main.o: main.c initialisation.h plateau.h game_logic.h game.h menu.h menu_management.h save.h plateau_mlv.h mlv.h
	$(CC) $(OPTION) main.c -c

initialisation.o: initialisation.c initialisation.h
	$(CC) $(OPTION) initialisation.c -c

plateau.o: plateau.c plateau.h
	$(CC) $(OPTION) plateau.c -c

game_logic.o: game_logic.c game_logic.h
	$(CC) $(OPTION) game_logic.c -c

game.o: game.c game.h
	$(CC) $(OPTION) game.c -c

menu.o: menu.c menu.h
	$(CC) $(OPTION) menu.c -c

menu_management:o menu_management.c menu_management.h
	$(CC) $(OPTION) menu_management.c -c

save.o: save.c save.h
	$(CC) $(OPTION) save.c -c

plateau_mlv.o: plateau_mlv.c plateau_mlv.h
	$(CC) $(OPTION) plateau_mlv.c -c

mlv.o: mlv.c mlv.h
	$(CC) $(OPTION) mlv.c -c

clearscreen:
	clear

clean:
	rm -rf *.o *~ match