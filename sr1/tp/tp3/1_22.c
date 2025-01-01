#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define TAILLE 512

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s fichier1 [fichier2 ...]\n", argv[0]);
        return 1;
    }

    struct stat Infos;

    // Parcourir les fichiers donnés en argument
    for (int i = 1; i < argc; i++) {
        if (lstat(argv[i], &Infos) == -1) {
            perror(argv[i]);
            continue;
        }

        printf("%s ", argv[i]);
        Affiche_inode(&Infos);
    }

    return 0;
}