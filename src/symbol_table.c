/**
 * Définition de la table des symbols
 * Romain Pelletier & Arthur Delrue
*/

#include "symbol_table.h"


SymbolTable table_create(int size)
{
	SymbolTable symbol_table;
	int i;
	// taille non null et allocation memoire reussie ?
	if(size < 1 || (symbol_table = malloc(sizeof(symbol_table_t))) == NULL)
		return NULL;

	// Allocation memoire des elements reussie? And initialisation
	if((symbol_table->table = calloc(size, sizeof(symbol_t))) == NULL)
		return NULL;

	symbol_table->size = size;
	return symbol_table;
}


Symbol table_add_symbol(SymbolTable symbol_table, char* name, Symbol symbol)
{
	if(name == NULL || symbol == NULL)
		return NULL;

	unsigned long index = hash_fuction(name);
	index %= symbol_table->size;
	symbol->successor = symbol_table->table[index];
	symbol_table->table[index] = symbol;

 	return symbol;
}


Symbol table_lookup(SymbolTable symbol_table, char* name)
{
	Symbol symbol;

	if(name == NULL)
		return NULL;

	unsigned long index = hash_fuction(name);
	index %= symbol_table->size;
	symbol = symbol_lookup(symbol_table->table[index], name);

	return symbol;
}

Symbol table_new_integer(SymbolTable symbol_table, char* name)
{
	Symbol symbol = table_lookup(symbol_table, name);
	if(symbol != NULL){
		error_message(symbol);
		return symbol;
	}
	symbol = symbol_new_integer(name);
	symbol->state = Initialized;
	table_add_symbol(symbol_table,name, symbol);
	return symbol;
}


Symbol table_new_constant(SymbolTable symbol_table, char* name, int number)
{
	Symbol symbol = table_lookup(symbol_table, name);
	if(symbol != NULL){
		error_message(symbol);
		return symbol;
	}
	symbol = symbol_new_constant(name, number);
	table_add_symbol(symbol_table,name, symbol);
	return symbol;
}



Symbol table_new_number(SymbolTable symbol_table, int number)
{
	static char const_id_name[MAX_NAME_LENGTH];

	print_to_string(const_id_name, CONSTANT_, number);
	Symbol symbol = table_lookup(symbol_table, const_id_name);
	if(symbol != NULL)
		return symbol;

	char* const_name = strdup(const_id_name);
	symbol = symbol_new_constant(const_name, number);
	table_add_symbol(symbol_table,const_name, symbol);
	return symbol;
}

Symbol table_new_string(SymbolTable symbol_table, char* string)
{
	static int string_number = 0;
	static char string_id_name[MAX_NAME_LENGTH];
	print_to_string(string_id_name, "string_",string_number);
	string_number++;
	Symbol symbol = table_lookup(symbol_table, string_id_name);
	if(symbol != NULL){
		error_message(symbol);
		return symbol;
	}
	char* string_name = strdup(string_id_name);
	symbol = symbol_new_string(string_name, string);
	table_add_symbol(symbol_table,string_name, symbol);
	return symbol;
}

Symbol table_new_tmp(SymbolTable symbol_table)
{
	static int tmp_number = 0;
	static char tmp_id_name[MAX_NAME_LENGTH];
	print_to_string(tmp_id_name, TEMPORARY_ ,tmp_number);
	tmp_number++;
	char* tmp_name = strdup(tmp_id_name);
	Symbol symbol =  table_new_integer(symbol_table, tmp_name);
	symbol->state = Initialized;
	return symbol;
}

void table_print(SymbolTable symbol_table)
{
	printf("\t=====  Symbol table =====\n");
	if(symbol_table == NULL)
		return;
	int i ;
	for(i= 0; i < symbol_table->size; i++)
	{
		//printf("%d\n",i+1);
		symbol_print(symbol_table->table[i]);
	}
}

void table_remove(SymbolTable symbol_table, char* name)
{
	 Symbol tmp_symbol;

	if(name == NULL)
		return ;

	unsigned long index = hash_fuction(name);
	index %= symbol_table->size;

	if(symbol_table->table[index]!=NULL)
	{
		if(strcmp(symbol_table->table[index]->name, name) == 0)
		{
			tmp_symbol = symbol_table->table[index];
			symbol_table->table[index] = symbol_table->table[index]->successor;
			symbol_free(tmp_symbol);
			return;
		}
		//else
			//return;
	}


	 tmp_symbol = symbol_table->table[index];
	 while(tmp_symbol->successor != NULL)
	 {
		 if(strcmp(tmp_symbol->successor->name, name) == 0)
		 {
			Symbol tmp_symbol2 = tmp_symbol->successor;
			tmp_symbol->successor = tmp_symbol->successor->successor;
			symbol_free(tmp_symbol2) ;
			return;
		 }
		tmp_symbol = tmp_symbol->successor ;
	 }
}


void table_free(SymbolTable symbol_table)
{
	if(symbol_table == NULL)
		return;
	int i;
	Symbol tmp_symbol;
	Symbol symbol_to_free;
	for( i = 0; i < symbol_table->size ; i++)
	{
		tmp_symbol = symbol_table->table[i];
		while(tmp_symbol != NULL )
		{
			symbol_to_free = tmp_symbol;
			tmp_symbol = tmp_symbol->successor;
			symbol_free(symbol_to_free);

		}
	}
	free(symbol_table->table);
	symbol_table->table = NULL;
	free(symbol_table);
	symbol_table = NULL;


}

/*
 * See for the hash function details
 * http://www.cse.yorku.ca/~oz/hash.html
 */

unsigned long hash_fuction(char* key)
{
	unsigned long hash = 5381;
	int c;

	while (c = *key++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

void print_to_string(char* dest, char* name, int id)
{
	sprintf(dest,"%s%d",name,id);
}

void error_message(Symbol symbol)
{
		if(is_constant_symbol(symbol))
			fprintf(stderr,"La constante %s est deja definie !!!\n", symbol->name);
		else
			fprintf(stderr,"Une variable du meme nom (%s) est deja definie !!!\n", symbol->name);
}


void table_print_code(SymbolTable symbol_table, FILE* output_file)
{
	int i ;


	fprintf(output_file,"\t#String constante\n");
	for( i = 0 ; i < symbol_table->size ; i++)
		symbol_print_code(symbol_table->table[i], output_file, String);

	fprintf(output_file,"\t#Integer variable\n");
	for( i = 0 ; i < symbol_table->size ; i++)
		symbol_print_code(symbol_table->table[i], output_file, Integer);

	fprintf(output_file,"\t#Integer Constant\n");
	for( i = 0 ; i < symbol_table->size ; i++)
		symbol_print_code(symbol_table->table[i], output_file, Constant);

}
