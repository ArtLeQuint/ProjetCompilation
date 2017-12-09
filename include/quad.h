/*Fait par Romain Pelletie et Arthur Delrue
 M1 ILC 2017*/

#ifndef QUAD_H
#define QUAD_H

#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * \enum _operation
 * \typedef enum Operation
 * Définition des opération réalisables
 */
typedef enum _operation{
	Assignment, Add, Sub, Mult, Div, Modulo, StencilOp, UnarySub, Abs,
	Equal, NotEqual, GreaterThan, GreaterThanEqual, 
	LoadAddress, LoadWAddress, SaveWAddress,
	LesserThan, LesserThanEqual, Printf, Printi, Goto, Return,
	Exit, Increment, Decrement
} Operation;
/**
 * \struct struct _quad
 * \typedef struct Quad_t
 * \typedef struct  *Quad 
 * Définition du type Quad_t
 */
typedef struct _quad{
 	int label; /**< Label du quad*/
 	Operation operation;/**< Le type d'operation du quad*/
	Symbol arg1;/**< Le premier argument*/
	Symbol arg2;/**< Le second argument*/
	Symbol res;/**< Le resultat de l'operation*/
	struct _quad* next;/**< Le quad suivant */
}Quad_t, *Quad ;

/**
 * \struct struct _quad_list
 * \typedef struct quad_list_t
 * \typedef struct  *QuadList
 * Définition d'une liste chainé de quad 
 */
typedef struct _quad_list{
	Quad code;/**< Le quad du noeud*/
	struct _quad_list* next;/**< La chaine suivante*/

}quad_list_t, *QuadList ;

/**
 * \struct struct _condition
 * \typedef struct condition_t
 * \typedef struct *Condition
 * Définition du type d'une condition
 */
typedef struct _condition{
      Quad code;/**< Le code de la condition  */
      QuadList trueList;/**< Liste contenant les quads à completer si la condition est vrai  */
      QuadList  falseList;/**<Liste contenant les quads à completer si la condition est vrai  */
  }condition_t, *Condition ;
    
/**
 * \struct struct _expression
 * \typedef struct expression_t
 * \typedef struct  *Expression
 * Définition du type d'une expression
 */
 typedef struct _expression{
	Quad code;/**< Le code de l'expression */
	Symbol result;/**<  Resultat de l'expression*/
	QuadList nextList;/**< Liste contenant les quads à pointer sur l'instruction suivant cette expression */
}expression_t,*Expression;

/**
 * \struct struct _array_ref
 * \typedef struct array_ref_t
 * \typedef struct* ArrayRef
 * Définition du type pour le reférencement d'un élément d un tableau
 */
typedef struct _array_ref{
		Quad code;/**< Le code du référencement*/
		Symbol result;/**< Le resultat contenant l'adresse du decalage*/
		int nb_dim; /**< nombre de dimension de la référence */
} array_ref_t, *ArrayRef;


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
