/*Fait par Romain Pelletier et Arthur Delrue
 M1 ILC 2017*/

#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_type.h"
#include "array_type.h"

#define MAX_NAME_LENGTH 50
#define CONSTANT_  "Const_"
#define TEMPORARY_ "Tmp_"
#define STRING_    "String_"
#define TAILLE_    "Taille_"

/* Définition du type symbol */
typedef struct _symbol{
		char* name;
		DataType data_type;
		VariableState state;
		union{
			int number ;
			char*  string;
			Array array;
		} data;

		struct _symbol* successor;
} symbol_t, *Symbol;


Symbol symbol_new(char* id_name);
Symbol symbol_new_integer(char* id_name);
Symbol symbol_new_integer_init(char* id_name, int number);
Symbol symbol_new_constant(char* id_name, int number);
Symbol symbol_new_string(char* id_name, char* string);
// Les fonctions de test :
bool is_constant_symbol(Symbol symbol);
bool is_integer_symbol(Symbol symbol);
bool is_string_symbol(Symbol symbol);
bool is_stencil_symbol(Symbol symbol);
bool is_array_symbol(Symbol symbol);
bool is_ref_to_array_symbol(Symbol symbol);

Symbol symbol_lookup(Symbol list_symbol, char* id_name);
void symbol_free(Symbol symbol);
void symbol_print(Symbol symbol);
void symbol_print_code(Symbol symbol, FILE* output_file, DataType data_type);

#endif
