CC = gcc
CFLAGS = -std=c11 -Wpedantic -Wall -Wextra
LDLIBS = -lm
RM = rm -f
OBJ = matrice.o tp8ex1.o

EXE = tp8ex1


# Règle par défaut pour construire l'exécutable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LDLIBS)



# Règle pour générer identite.o à partir de identite.c
matrice.o: matrice.c matrice.h
	$(CC) $(CFLAGS) -c matrice.c

# Règle pour générer testidentite.o à partir de testidentite.c
tp8ex1.o: tp8ex1.c tp8ex1.h
	$(CC) $(CFLAGS) -c tp8ex1.c


# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	$(RM) $(OBJ) $(EXE)
