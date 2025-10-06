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

#include <ctype.h>


#define TAILLE 512



int main(){
    int tubeAlpha[2], tubeDigit[2];
    if((pipe(tubeAlpha)==-1)||(pipe(tubeDigit)==-1)){
        perror("echec creation tube");
        exit(1);
    }

    char c;
    int pid;
    pid=fork();
    if(pid==-1){
        perror("Echec creation processus");
        exit(2);
    }
    if(pid==0){
        close(tubeDigit[0]);
        close(tubeDigit[1]);
        close(tubeAlpha[1]);

        int tabAlpha[26];
        for(int i=0;i<26;i++)
            tabAlpha[i]=0;
        printf("Fils alpha\n");
        while(read(tubeAlpha[0],&c,sizeof(c))>0)
            tabAlpha[tolower(c)-'a']++;
        close(tubeAlpha[0]);
        for(int i;i<26;i++)
            printf("%c%-2d", (char)1+'a',tabAlpha[i]);
        printf("\n Fils alpha fini\n");
        exit(0);
        
    }

    pid=fork();
    if(pid==-1){
        perror("Echec creation processus");
        exit(2);
    }
    if(pid==0){
        close(tubeAlpha[0]);
        close(tubeAlpha[1]);
        close(tubeDigit[1]);

        int somme=0;
        printf("fils digit\n");

        while(read(tubeDigit[0],&c,sizeof(c))>0)
            somme+=(int)c-'O';

        close(tubeDigit[0]);
        printf(" fils digit somme=%d\n",somme);
        printf("\n fils digit fini\n");
        exit(0);
        
    }
    
    printf("PERE\n");
    close(tubeAlpha[0]);
    close(tubeDigit[0]);


    while((read(STDIN_FILENO,(void*)&c,sizeof(c))>0)&&(c!='f')){
        if(isalpha(c))
            write(tubeAlpha[1],&c,sizeof(c));
        else if(isdigit(c))
            write(tubeDigit[1],&c,sizeof(c));
        }
        close(tubeAlpha[1]);
        close(tubeDigit[1]);
        exit(0);
}