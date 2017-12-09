/**
* Fichier d'entrée
* Romain Pelletier & Arthur Delrue
* Projet compilation 2017 M1 ILC
*/
#include "quad.h"
#include "symbol.h"
#include "symbol_table.h"
#include "array_type.h"
#include "gen_code_mips.h"
#include "../tmp/cfss.y.h"
#include <stdlib.h>
#include <string.h>
#define SYMBOL_TABLE_SIZE  251
FILE* fichier_sortie;
extern FILE* yyin;
extern SymbolTable symbol_table;
extern Expression program_expression ;

int main (int argc, char** argv)
{
	//Arguments :
	switch(argc)
	{
		case 2:
		 		// Pas de sortie
				yyin = fopen(argv[1], "r");
				fichier_sortie = fopen("output.s", "w");
				printf("-------\n");
				printf("resultat dans output.s\n\n");
			printf("--------\n\n");
				break;
		case 3:
				// Une sortie
				yyin = fopen(argv[1], "r");
				fichier_sortie = fopen(argv[2], "w");
				break;
		default:
			// TEST
			yyin = fopen("test.c", "r");
			fichier_sortie = fopen("output.s", "w");
			printf("-------\n");
			printf("test par défaut, resultat dans output.s\n\n");
			printf("--------\n\n");
	}

	//symbol_table = table_create(SYMBOL_TABLE_SIZE);
	printf("Compilation error : %d", yyparse());
	fclose(yyin);

	//quad_print(program_expression->code);

	//gen_code_mips(program_expression->code);
	fclose(fichier_sortie);
	//quad_free(program_expression->code);
	//quad_list_free(program_expression->nextList);

	//table_print(symbol_table);
	//table_free(symbol_table);

	 return 0;

 }
