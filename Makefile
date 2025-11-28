CC = gcc
OPTION = -W -Wall -pedantic -std=c89 -O2
OBJECTS = ./Objects/
SOURCE = ./Source/
EXEC = match

OBJ = $(OBJECTS)main.o $(OBJECTS)initialisation.o $(OBJECTS)plateau.o $(OBJECTS)game_logic.o $(OBJECTS)game.o $(OBJECTS)menu.o $(OBJECTS)menu_management.o $(OBJECTS)save.o $(OBJECTS)plateau_mlv.o $(OBJECTS)mlv.o

all: clearscreen $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` $^ `pkg-config --libs-only-l MLV` -o $@

$(OBJECTS):
	mkdir -p $(OBJECTS)

$(OBJECTS)main.o: $(SOURCE)main.c | $(OBJECTS)
	$(CC) $(OPTION) $^ -c -o $@

$(OBJECTS)initialisation.o: $(SOURCE)initialisation.c | $(OBJECTS)
	$(CC) $(OPTION) $^ -c -o $@

$(OBJECTS)plateau.o: $(SOURCE)plateau.c | $(OBJECTS)
	$(CC) $(OPTION) $^ -c -o $@

$(OBJECTS)game_logic.o: $(SOURCE)game_logic.c | $(OBJECTS)
	$(CC) $(OPTION) $^ -c -o $@

$(OBJECTS)game.o: $(SOURCE)game.c | $(OBJECTS)
	$(CC) $(OPTION) $^ -c -o $@

$(OBJECTS)menu.o: $(SOURCE)menu.c | $(OBJECTS)
	$(CC) $(OPTION) $^ -c -o $@

$(OBJECTS)menu_management.o: $(SOURCE)menu_management.c | $(OBJECTS)
	$(CC) $(OPTION) $^ -c -o $@

$(OBJECTS)save.o: $(SOURCE)save.c | $(OBJECTS)
	$(CC) $(OPTION) $^ -c -o $@

$(OBJECTS)plateau_mlv.o: $(SOURCE)plateau_mlv.c | $(OBJECTS)
	$(CC) $(OPTION) `pkg-config --cflags MLV` $^ -c -o $@

$(OBJECTS)mlv.o: $(SOURCE)mlv.c | $(OBJECTS)
	$(CC) $(OPTION) `pkg-config --cflags MLV` $^ -c -o $@

clearscreen:
	clear

clean:
	rm -rf $(OBJECTS) *~ $(EXEC)