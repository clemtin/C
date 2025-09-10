CC=gcc
# Options de compilation
CFLAGS=-std=c11 -Wpedantic -Wall -Wextra

# Bibliothèques à lier
LDLIBS=-lm

# Commande pour supprimer des fichiers
RM=rm -f

# Liste des fichiers objets
OBJLIST=testlistemots.o listemots.o
OBJ=statstxt.o listemots.o utils.o
OBJANA =analysermots.o listemots.o utils.o
OBJT = testlistemots.o listemots.o statstxt.o listemots.o utils.o analysermots.o listemots.o utils.o
# Nom des exécutables
EXE=prog statstxt analysermots

#nom des TXT
TEXTE = statistiques.txt liste_mots_01.txt liste_mots_02.txt

# Pour produire l'exécutable prog
prog: $(OBJ)
	$(CC) $(CFLAGS) $(OBJLIST) -o prog $(LDLIBS)


# Pour produire l'exécutable statstxt
statstxt: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o statstxt $(LDLIBS)

# Pour produire L'executable analysermots
analysermots: $(OBJANA)
	$(CC) $(CFLAGS) $(OBJANA) -o analysermots $(LDLIBS)


# Pour produire tout les executables 
tous: $(OBJT)
	$(CC) $(CFLAGS) $(OBJLIST) -o prog $(LDLIBS)
	$(CC) $(CFLAGS) $(OBJ) -o statstxt $(LDLIBS)
	$(CC) $(CFLAGS) $(OBJANA) -o analysermots $(LDLIBS)

# Pour produire les fichiers objets
testlistemots.o: testlistemots.c listemots.h
	$(CC) $(CFLAGS) -c testlistemots.c -o testlistemots.o

listemots.o: listemots.c listemots.h
	$(CC) $(CFLAGS) -c listemots.c -o listemots.o


statstxt.o: statstxt.c listemots.h utils.h
	$(CC) $(CFLAGS) -c statstxt.c -o statstxt.o

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c -o utils.o

analysermots.o: analysermots.c listemots.h utils.h
	$(CC) $(CFLAGS) -c analysermots.c -o analysermots.o



# Pour effacer les objets et les exécutables
clean:
	$(RM) $(OBJ) $(OBJLIST) $(EXE) $(TEXTE)

