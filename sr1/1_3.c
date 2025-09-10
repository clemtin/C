#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <errno.h>                  /* pour erno */



int main(int argc, char *argv[]){
    if(argc <2){
        fprintf(stderr,"Usage; %s int [int ...]\n" ,argv[0]);
        exit(1);
    }
    // printf("%lu  %lu\n",sizeof(int),sizeof(long));
    long val; /* long int == long*/
    char * endptr;
    for (int i=1;i<argc;i++){
        errno=0;
        val=strtol(argv[i],&endptr,10);
        if (errno)/* erno!=0*/{
            perror(argv[i]);
        }
        else if (argv[i]==endptr) // ou bien (*endptr != '\0)
        {
            fprintf(stderr,"%s n'est pas un nombre entier\n",argv[i]);
        }
        else
        printf("%ld\n",val);

    }
    exit(0);
    }