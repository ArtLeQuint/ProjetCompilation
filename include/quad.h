/*Fait par Romain Pelletier et Arthur Delrue
 M1 ILC 2017*/

#ifndef QUAD_H
#define QUAD_H

#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Définition des opération réalisables */
typedef enum _operation{
	Assignment, Add, Sub, Mult, Div, Modulo, StencilOp, UnarySub, Abs,
	Equal, NotEqual, GreaterThan, GreaterThanEqual,
	LoadAddress, LoadWAddress, SaveWAddress,
	LesserThan, LesserThanEqual, Printf, Printi, Goto, Return,
	Exit, Increment, Decrement
} Operation;
/* Définition des quads */
typedef struct _quad{
 	int label;
 	Operation operation;
	Symbol arg1;
	Symbol arg2;
	Symbol res;
	struct _quad* next;
}Quad_t, *Quad ;

/* Liste de quads */
typedef struct _quad_list{
	Quad code;
	struct _quad_list* next;

}quad_list_t, *QuadList ;

/* Les conditions */
typedef struct _condition{
      Quad code;
      QuadList trueList;
			QuadList  falseList;
}condition_t, *Condition ;

/* Les expressions */
 typedef struct _expression{
	Quad code;/**< Le code de l'expression */
	Symbol result;/**<  Resultat de l'expression*/
	QuadList nextList;/**< Liste contenant les quads à pointer sur l'instruction suivant cette expression */
}expression_t,*Expression;

Quad quad_gen(int* , Operation, Symbol, Symbol, Symbol);
void quad_merge(Quad*, Quad);
void quad_print(Quad);
void quad_free(Quad);

QuadList quad_list_new(Quad);
void quad_list_merge(QuadList*,QuadList);
void quad_list_complete(QuadList, Symbol);
void quad_list_print(QuadList);
void quad_list_free(QuadList);
bool is_relation_operation (Quad quad);
#endif
