/*Fait par Romain Pelletier et Arthur Delrue
 M1 ILC 2017*/
#ifndef GEN_CODE_MIPS_H
#define GEN_CODE_MIPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quad.h"
#include "symbol.h"
#include "symbol_table.h"
#include "operation.h"
#include "array_type.h"

extern FILE * fichier_sortie;
extern SymbolTable symbol_table;

extern int unsigned next_quad_label;
void gen_code_mips(Quad root_quad);
void gen_quad_code(Quad quad);
void bin_operation_code(Quad quad);
void single_operation_code(Quad quad);
void rel_operation_code(Quad quad);
void jump_operation_code(Quad quad);
void load_value(Symbol symbol, char* register_name);
void gen_system_service_const();
void gen_utils_function();
void gen_entete_comment();

void adresse_operation_tab(Quad quad);

void gen_function_exit();
void gen_function_print_string();
void gen_function_print_int();
void gen_function_exit_value();


#endif
