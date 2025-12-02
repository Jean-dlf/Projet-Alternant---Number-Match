# Options de compilation
CC = gcc
OPTION = -W -Wall -pedantic -std=c89 -O2

# Dossiers pour les fichiers .c et .o
OBJECTS = ./Objects/
SOURCE = ./Source/

# Nom de l'exécutable
EXEC = match

# Liste des fichiers objets
OBJ = $(OBJECTS)main.o $(OBJECTS)initialisation.o $(OBJECTS)plateau.o $(OBJECTS)game_logic.o $(OBJECTS)game.o $(OBJECTS)menu.o $(OBJECTS)menu_management.o $(OBJECTS)save.o $(OBJECTS)plateau_mlv.o $(OBJECTS)mlv.o $(OBJECTS)score.o

# Ce qui va être exécuté lors du make
all: clean clearscreen $(EXEC)

# Compilation de l'exécutable avec les fichiers objets
$(EXEC): $(OBJ)
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` $^ `pkg-config --libs-only-l MLV` -o $@

# Création du dossier Objetcs
$(OBJECTS):
	mkdir -p $(OBJECTS)

# Compilation de tous les fichiers .c en .o dans le fichier Objects
$(OBJECTS)%.o: $(SOURCE)%.c | $(OBJECTS)
	$(CC) $(OPTION) $^ -c -o $@

# optionnel mais permet de clear la page lors d'un make
clearscreen:
	clear

# Nettoie tous les fichiers .o et l'exécutable
clean:
	rm -rf $(OBJECTS) *~ $(EXEC)