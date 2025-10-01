#include "afficher.h"
#define _POSIX_C_SOURCE 200809L     /* POur nomre Posix 1.2017 */
#include <unistd.h>
#include <stdio.h>                  /* pour print f*/
#include <stdlib.h>                 /* pour le exit */
#include <errno.h>                  /* pour errno */

void afficher(void){
    printf("PID : %d\n",getpid());
    printf("PPID : %d\n",getppid());
    printf("PGRP : %d\n",getpgrp());
    printf("LOGIN : %s\n",getlogin());
    printf("UID : %d\n",getuid());
    printf("GID : %d\n",getgid());
} 

