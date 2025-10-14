#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include <dirent.h>

#define N 4
#define MAX_BASSIN 5
#define TAILLE 512

#include <math.h>         /* Pour sqrt */

int est_premier (unsigned long long int n)
{
  if ((n>1) && (n==2 || n==3 || ((n%2)&&(n%3))))
  {
    unsigned long long int i,y;

    y=sqrt(n)+1;
    i=5;
    while(i<y)
    {
      if (n%i == 0)
        return 0;
      i+=2;
      if (n%i == 0)
        return 0;
      i+=4;
    }
    return 1;
  }
  return 0;
}




int main(int argc,char* argv[]){

    if (argc < 2) {
        fprintf(stderr, "Usage : %s n1 n2 ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Création des fils
    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            // Code du fils
            close(pipefd[1]); // le fils ferme l’écriture

            unsigned long long int n;
            int nb_premiers = 0;

            while (read(pipefd[0], &n, sizeof(n)) == sizeof(n)) {
                if (est_premier(n)) {
                    printf("Fils %d : %llu est premier\n", i, n);
                    nb_premiers++;
                }
            }

            close(pipefd[0]);
            exit(nb_premiers);
        }
    }

    // Code du père
    close(pipefd[0]); // le père ferme la lecture

    // Écrire chaque argument dans le tube
    for (int i = 1; i < argc; i++) {
        char *endptr;
        unsigned long long int n = strtoull(argv[i], &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stderr, "Erreur : '%s' n'est pas un entier valide.\n", argv[i]);
            continue;
        }
        write(pipefd[1], &n, sizeof(n));
    }

    close(pipefd[1]); // fin d’écriture

    // Attente des fils et comptage total
    int total_premiers = 0;
    for (int i = 0; i < N; i++) {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            total_premiers += WEXITSTATUS(status);
        }
    }

    printf("Total de nombres premiers : %d\n", total_premiers);
    return 0;






    return 0;
}