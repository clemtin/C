// Need this to use the getline C function on Linux. Works without this on MacOs. Not tested on Windows.
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "token.h"
#include "queue.h"
#include "stack.h"


/** 
 * Utilities function to print the token queues
 */
void print_token(const void* e, void* user_param);
void print_queue(FILE* f, Queue* q);

/** 
 * Function to be written by students
 */
void computeExpressions(FILE* input) {
	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;

	while((linelen = getline(&line,&linecap,input))!=-1){
		if(line[0]=='\n')
			continue;
		printf("Ìnput : %s",line);
	}
}	

Queue* stringToTokenQueue(const char* expression){
	int cmpt = 0;
	Queue* q=create_queue(void);
	const char* curpos = expression;
	while(curpos!='\0'){
		
		while((curpos!=' ')||(curpos!='\n')){
		curpos++; //  Le début de l’élément syntaxique devra etre désigné par curpos,
		cmpt++; // 	la fin de l’élément par le nombre de caractere le composant.

			if(isSymbol(curpos)&&(curpos!='\0')){
				Token* t=create_token_from_string(curpos,1);
				Queue_push(q,curpos);
				curpos++;
			}

			
			
		
			}

		}
			return q;
	}
bool isSymbol(char c){
	return(((c=='&')||(c=='+')||(c=='-'))||(c=='*')||(c==''\'')||(c=='^')||(c=='(')||(c==')'));
		
}

/** Main function for testing.
 * The main function expects one parameter that is the file where expressions to translate are
 * to be read.
 *
 * This file must contain a valid expression on each line
 *
 */
int main(int argc, char** argv){
	if (argc<2) {
		fprintf(stderr,"usage : %s filename\n", argv[0]);
		return 1;
	}
	
	FILE* input = fopen(argv[1], "r");

	if ( !input ) {
		perror(argv[1]);
		return 1;
	}

	computeExpressions(input);

	fclose(input);
	return 0;
}
 
void print_token(const void* e, void* user_param) {
	FILE* f = (FILE*)user_param;
	Token* t = (Token*)e;
	token_dump(f, t);
}

void print_queue(FILE* f, Queue* q) {
	fprintf(f, "(%d) --  ", queue_size(q));
	queue_map(q, print_token, f);
}

