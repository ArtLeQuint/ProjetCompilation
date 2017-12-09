/*Fait par Romain Pelletie et Arthur Delrue
 M1 ILC 2017*/

#ifndef OPERATION_H
#define OPERATION_H

#include "quad.h"
#include "symbol.h"
#include "symbol_table.h"
#include "array_type.h"
#include <stdio.h>
#include <stdlib.h>

int unsigned next_quad_label;/**< L'entier pour marques les labels des quads*/
SymbolTable symbol_table;/**<  La table de symbole*/

void bin_operation(Operation operation, Expression res, Expression arg1, Expression arg2);
void single_operation(Operation operation, Expression res, Expression arg1);
void assignment_operation( Expression res, Expression arg1);
void assignment_array_operation( Expression res, Expression arg1, Expression arg2);
void jump_operation(Operation operation, Expression res, Expression arg1);
void rel_operation(Operation operation, Condition res_condition, Expression arg1, Expression arg2);
void array_declaration(char* array_name, ArrayList dimension_elements, ArrayList array_elements);
void stencil_declaration(char* stencil_name, int neighbor, int nb_dimension, ArrayList stencil_elements);
void init_to_null(Expression expression);
int int_power(int number, int power);

#endif
