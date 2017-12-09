/*Fait par Romain Pelletie et Arthur Delrue
 M1 ILC 2017*/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "symbol.h"
/**
 * \struct struct _symbol_table
 * \typedef struct symbol_table_t
 * \typedef struct* SymbolTable
 * Définition du type de la table de symbol
 * Implémentation sous forme de table de hashage
 */
typedef struct _symbol_table{
	int size;/**< La taille de la table de symbol*/
	Symbol* table;/**< Les élément de la table*/
}symbol_table_t, *SymbolTable;

SymbolTable table_create(int size);
Symbol table_add_symbol(SymbolTable symbol_table, char* name, Symbol);
Symbol table_new_integer(SymbolTable symbol_table, char* name);
Symbol table_new_constant(SymbolTable symbol_table, char* name, int number);
Symbol table_new_number(SymbolTable symbol_table, int number);
Symbol table_new_string(SymbolTable symbol_table, char* string);
Symbol table_new_array(SymbolTable symbol_table, char* name);
Symbol table_new_stencil(SymbolTable symbol_table, char* name);
Symbol table_new_tmp(SymbolTable symbol_table);
Symbol table_lookup(SymbolTable symbol_table, char* name);

void table_remove(SymbolTable symbol_table, char* name);
void print_to_string(char* dest, char* name, int id);
void table_print(SymbolTable symbol_table);
void table_free(SymbolTable symbol_table);

void table_print_code(SymbolTable symbol_table, FILE* output_file);
unsigned long hash_fuction(char* key);
void error_message(Symbol symbol);


#endif
