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


bool isSymbol(const char c);
Queue* stringToTokenQueue(const char* expression);
void computeExpressions(FILE* input);
Queue* shuntingYard(Queue* infix);
float evaluateExpression(Queue* postfix);

void computeExpressions(FILE* input) {
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;

    while ((linelen = getline(&line, &linecap, input)) != -1) {
        if (line[0] == '\n')
            continue;

        printf("Input : %s", line);

        // Étape 1 : conversion en tokens
        Queue* infix = stringToTokenQueue(line);
        printf("Infix : ");
        print_queue(stdout, infix);
        printf("\n");

        // Étape 2 : conversion en postfix
        Queue* postfix = shuntingYard(infix);
        printf("Postfix : ");
        print_queue(stdout, postfix);
        printf("\n");

        // Étape 3 : évaluation
        float result = evaluateExpression(postfix);
        printf("Evaluate : %f\n\n", result);

         //  libérer chaque token des files
        while (!queue_empty(infix)) {
            Token* t = (Token*) queue_top(infix);
            queue_pop(infix);
            free(t);
        }
        while (!queue_empty(postfix)) {
            Token* t = (Token*) queue_top(postfix);
            queue_pop(postfix);
            free(t);
        }

        // Nettoyage
        delete_queue(&infix);
        delete_queue(&postfix);
    }

    free(line);
}


bool isSymbol(char c) {
    return (c == '&' || c == '+' || c == '-' || c == '*' ||
            c == '\'' || c == '^' || c == '(' || c == ')');
}


Queue* stringToTokenQueue(const char* expression){
    Queue* q = create_queue();
    const char* curpos = expression;

    while (*curpos != '\0') {
        // Ignorer les espaces et les retours à la ligne
        if (*curpos == ' ' || *curpos == '\n') {
            curpos++;
            continue;
        }

        // Si c'est un symbole
        if (isSymbol(*curpos)) {
            Token* to = create_token_from_string(curpos, 1);
            queue_push(q, to);
            curpos++;
        } 
		else {
            const char* deb = curpos;
            int cmp = 0;
            while (*curpos != '\0' && *curpos != ' ' && *curpos != '\n' && !isSymbol(*curpos)) {
                cmp++;
                curpos++;
            }

            Token* to = create_token_from_string(deb, cmp);
            queue_push(q, to);
        }
    }
    return q;
	}


Queue* shuntingYard(Queue* infix) {
    Stack* swait = create_stack(queue_size(infix)); // pile d'opérateurs
    Queue* postfix = create_queue();                // file de sortie postfixe

    while (!queue_empty(infix)) {
        Token* t = (Token*) queue_top(infix);
        queue_pop(infix); // on avance dans la file infixée

        //  Si c'est un nombre : on le met directement dans la sortie
        if (token_is_number(t)) {
            queue_push(postfix, t);
        }

        // Si c'est un opérateur
        else if (token_is_operator(t)) {
            while (!stack_empty(swait)) {
                Token* top = (Token*) stack_top(swait);

                if (token_is_operator(top) &&
                    (
                        (token_operator_priority(top) > token_operator_priority(t)) ||
                        (token_operator_priority(top) == token_operator_priority(t)
                         && token_operator_leftAssociative(t))
                    )
                ) {
                    stack_pop(swait);
                    queue_push(postfix, top);
                } else {
                    break;
                }
            }
            stack_push(swait, t);
        }

        //  Si c’est une parenthèse ouvrante "("
        else if (token_is_parenthesis(t) && token_parenthesis(t) == '(') {
            stack_push(swait, t);
        }

        //  Si c’est une parenthèse fermante ")"
        else if (token_is_parenthesis(t) && token_parenthesis(t) == ')') {
            while (!stack_empty(swait)) {
                Token* top = (Token*) stack_top(swait);
                if (token_is_parenthesis(top) && token_parenthesis(top) == '(')
                    break;
                stack_pop(swait);
                queue_push(postfix, top);
            }

            // retirer la parenthèse ouvrante
            if (!stack_empty(swait) && token_is_parenthesis(stack_top(swait)) &&
                token_parenthesis(stack_top(swait)) == '(') {
                stack_pop(swait);
            }
        }
    }

    // À la fin, vider le reste de la pile
    while (!stack_empty(swait)) {
        Token* top = (Token*) stack_top(swait);
        stack_pop(swait);
        queue_push(postfix, top);
    }

    delete_stack(&swait);
    return postfix;
}

Token* evaluateOperator(Token* arg1, Token* op, Token* arg2){
    float a = token_value(arg1);
    float b = token_value(arg2);
    char o = token_operator(op);

    float res = 0.0f;	

	switch (o)
	{
	case '+':
		res=a+b;
		break;

	case '-':
		res=a-b;
		break;

	case '*':
		res=a*b;
		break;

	case '/':
		if(b==0){
			fprintf(stderr,"Division par 0 impossible\n");}
		else{
			res=a/b;
		}
		break;

	case '^':
		for(int i=0;i<(int)b;i++){
            res*=a;
        }
		break;

	default:
		fprintf(stderr,"operation inconnue\n");
		break;
		}

		Token* token_res = create_token_from_value(res);
		return(token_res);
	}

float evaluateExpression(Queue* postfix) {
    Stack* evalStack = create_stack(queue_size(postfix));

    while (!queue_empty(postfix)) {
        Token* t = (Token*) queue_top(postfix);
        queue_pop(postfix);

        if (token_is_number(t)) {
            stack_push(evalStack, t);
        }
        else if (token_is_operator(t)) {
            // dépiler dans l’ordre inverse
            Token* arg2 = (Token*) stack_top(evalStack);
            stack_pop(evalStack);
            Token* arg1 = (Token*) stack_top(evalStack);
            stack_pop(evalStack);

            Token* res = evaluateOperator(arg1, t, arg2);
            // free les anciens tokens
            free(arg1);
            free(arg2);
            free(t);

            stack_push(evalStack, res);

        }
    }

    // à la fin : un seul élément dans la pile
    Token* final = (Token*) stack_top(evalStack);
    float result = token_value(final);

    free(final);

    delete_stack(&evalStack);
    return result;
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

