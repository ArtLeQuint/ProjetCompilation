/**
 * Définition des fonctions générant du code mips
 * Romain Pelletier & Arthur Delrue
*/
#include "gen_code_mips.h"

void gen_code_mips(Quad root_quad)
{
	gen_entete_comment();

	fprintf(fichier_sortie,"\n\t.data\n");
	// Déclaration de variables
	table_print_code(symbol_table, fichier_sortie);
	gen_system_service_const();

	fprintf(fichier_sortie,"\n\t.text\n");
	fprintf(fichier_sortie,"\n\t.globl main\n\n");
	fprintf(fichier_sortie,"main:\n\n");
	//Traduction de code
	gen_quad_code(root_quad);
	//Declaration de fonction (print_i , print_f , stenC)
	gen_utils_function();

}


void gen_quad_code(Quad quad)
{
	if(quad == NULL)
		return;

    switch(quad->operation)
    {
	// binary operations
        case Add:
        case Sub:
        case Mult:
        case Div:
        case Modulo: bin_operation_code(quad);
                break;

        // Single operations
        case Assignment:
        case UnarySub:
        case Increment:
        case Abs:
        case Decrement: single_operation_code(quad);
                break;

        // Relation operations
        case Equal:
        case NotEqual:
        case GreaterThan:
        case GreaterThanEqual:
        case LesserThan:
        case LesserThanEqual: rel_operation_code(quad);
                break;

        // Jump operations
        case Printf:
        case Printi:
        case Goto:
        case Return:
        case Exit: jump_operation_code(quad);
                break;

        case LoadAddress:
        case LoadWAddress:
        case SaveWAddress: adresse_operation_tab(quad);
				break;

        default : printf("Exception:(gencode MIPS)!");
    }

    gen_quad_code(quad->next);
}

void bin_operation_code(Quad quad)
{
	//print the label
	if(quad->label > -1)
		fprintf(fichier_sortie, "L_%d:\n",quad->label);
	else
		fprintf(fichier_sortie, "\n");

	//perform the operation
	switch(quad->operation)
	{
        case Add: if(is_constant_symbol(quad->arg1))
			  {
					load_value(quad->arg2, "$t1");
					fprintf(fichier_sortie, "\tadd\t$t0, $t1, %d\n", quad->arg1->data.number);
			  }
			  else if(is_constant_symbol(quad->arg2))
				{
					load_value(quad->arg1, "$t1");
					fprintf(fichier_sortie, "\tadd\t$t0, $t1, %d\n", quad->arg2->data.number);
				}
				else
				{
					load_value(quad->arg1, "$t1");
					load_value(quad->arg2, "$t2");
					fprintf(fichier_sortie, "\tadd\t$t0, $t1, $t2\n");
				}
                break;
        case Mult: if(is_constant_symbol(quad->arg1))
			  {
					load_value(quad->arg2, "$t1");
					fprintf(fichier_sortie, "\tmul\t$t0, $t1, %d\n", quad->arg1->data.number);
			  }
			  else if(is_constant_symbol(quad->arg2))
				{
					load_value(quad->arg1, "$t1");
					fprintf(fichier_sortie, "\tmul\t$t0, $t1, %d\n", quad->arg2->data.number);
				}
				else
				{
					load_value(quad->arg1, "$t1");
					load_value(quad->arg2, "$t2");
					fprintf(fichier_sortie, "\tmul\t$t0, $t1, $t2\n");
				}
                break;
        case Sub: if(is_constant_symbol(quad->arg2))
			{
				load_value(quad->arg1, "$t1");
				fprintf(fichier_sortie, "\tsub\t$t0, $t1, %d\n", quad->arg2->data.number);
			}
			else
			{
				load_value(quad->arg1, "$t1");
				load_value(quad->arg2, "$t1");
				fprintf(fichier_sortie, "\tsub\t$t0, $t1, $t2\n");
			}
                break;
        case Div: if(is_constant_symbol(quad->arg2))
			{
				load_value(quad->arg1, "$t1");
				fprintf(fichier_sortie, "\tdiv\t$t0, $t1, %d\n", quad->arg2->data.number);
			}
			else
			{
				load_value(quad->arg1, "$t1");
				load_value(quad->arg2, "$t2");
				fprintf(fichier_sortie, "\tdiv\t$t0, $t1, $t2\n");
			}
                break;
        case Modulo: if(is_constant_symbol(quad->arg2))
				{
					load_value(quad->arg1, "$t1");
					fprintf(fichier_sortie, "\trem\t$t0, $t1, %d\n", quad->arg2->data.number);
				}
				else
				{
					load_value(quad->arg1, "$t1");
					load_value(quad->arg2, "$t2");
					fprintf(fichier_sortie, "\trem\t$t0, $t1, $t2\n");
				}
                break;
         case StencilOp: if(is_stencil_symbol(quad->arg1))
				 {
					 fprintf(fichier_sortie, "\tla $a0, %s\n", quad->arg1->name);
					 fprintf(fichier_sortie, "\tlw $a1, %s%s\n", TAILLE_, quad->arg1->name);
					 load_value(quad->arg2, "$a2");
					 fprintf(fichier_sortie, "\tjal StenC\n");
					 // save the value to the variable
					  fprintf(fichier_sortie, "\tsw $v0, %s\n", quad->res->name);
				 }
				 else
				 {
					 fprintf(fichier_sortie, "\tla $a0, %s\n", quad->arg2->name);
					 fprintf(fichier_sortie, "\tlw $a1, %s%s\n", TAILLE_, quad->arg2->name);
					 load_value(quad->arg1, "$a2");
					 fprintf(fichier_sortie, "\tjal StenC\n");
					 // save the value to the variable
					 fprintf(fichier_sortie, "\tsw $v0, %s\n", quad->res->name);
				 }
			return;
		}
	// save the value to the variable
	fprintf(fichier_sortie, "\tsw\t$t0, %s\n",quad->res->name);

}

void single_operation_code(Quad quad)
{
	//print the label
	if(quad->label > -1)
		fprintf(fichier_sortie, "L_%d:\n",quad->label);
	else
		fprintf(fichier_sortie, "\n");
	//load variables values
	load_value(quad->arg1, "$t1");
	//perform the operation
	switch(quad->operation)
	{
        case Assignment:fprintf(fichier_sortie, "\tsw\t$t1, %s\n",quad->res->name);
				return;
        case UnarySub : fprintf(fichier_sortie, "\tneg\t$t0, $t1\n");
                break;
        case Increment: fprintf(fichier_sortie, "\taddi\t$t0, $t1, 1\n");
                break;
        case Decrement: fprintf(fichier_sortie, "\taddi\t$t0, $t1, -1\n");
                break;
        case Abs: fprintf(fichier_sortie, "\tabs\t$t0, $t1\n");
                break;
	}
	// save the value to the variable
	fprintf(fichier_sortie, "\tsw\t$t0, %s\n",quad->res->name);
}



void rel_operation_code(Quad quad)
{
	//print the label
	if(quad->label > -1)
		fprintf(fichier_sortie, "L_%d:\n",quad->label);
	else
		fprintf(fichier_sortie, "\n");
	//load variables values
	load_value(quad->arg1, "$t1");
	load_value(quad->arg2, "$t2");
	//perform the operation
	switch(quad->operation)
	{
        case Equal: fprintf(fichier_sortie, "\tbeq\t$t1, $t2, L_%d\n",quad->res->data.number);
                break;
        case NotEqual: fprintf(fichier_sortie, "\tbne\t$t1, $t2, L_%d\n",quad->res->data.number);
                break;
        case LesserThan : fprintf(fichier_sortie, "\tblt\t$t1, $t2, L_%d\n",quad->res->data.number);
                break;
        case LesserThanEqual : fprintf(fichier_sortie, "\tble\t$t1, $t2, L_%d\n",quad->res->data.number);
                break;
        case GreaterThan: fprintf(fichier_sortie, "\tbgt\t$t1, $t2, L_%d\n",quad->res->data.number);
                break;
        case GreaterThanEqual: fprintf(fichier_sortie, "\tbge\t$t1, $t2, L_%d\n",quad->res->data.number);
                break;
	}
}

void jump_operation_code(Quad quad)
{
	//print the label
	if(quad->label > -1 && quad->operation != Goto)
		fprintf(fichier_sortie, "L_%d:\n",quad->label);

	//perform the operation
	switch(quad->operation)
	{

        case Goto :fprintf(fichier_sortie, "\tj\tL_%d\n",quad->res->data.number);
				break;

        case Printi: load_value(quad->res, "$t1");
					 fprintf(fichier_sortie, "\tmove\t$a0, $t1\n");
					 fprintf(fichier_sortie, "\tjal\tPrint_i\n");
                break;

        case Printf: fprintf(fichier_sortie, "\tla\t$a0, %s\n",quad->res->name);
					 fprintf(fichier_sortie, "\tjal\tPrint_f\n");
                break;

        case Exit :load_value(quad->res, "$t1");
					  fprintf(fichier_sortie, "\tmove\t$a0, $t1\n");
					  fprintf(fichier_sortie, "\tjal\tExit_with_value\n");
                break;

        case Return : load_value(quad->res, "$t1");
					  fprintf(fichier_sortie, "\tmove\t$a0, $t1\n");
					  fprintf(fichier_sortie, "\tjal\tExit_with_value\n");
                break;

	}
}

void adresse_operation_tab(Quad quad)
{
	//print the label
	if(quad->label > -1)
		fprintf(fichier_sortie, "L_%d:\n",quad->label);
	else
		fprintf(fichier_sortie, "\n");

	switch(quad->operation)
	{
        case LoadAddress :  fprintf(fichier_sortie, "\tla $s0,  %s\n", quad->arg1->name);
							fprintf(fichier_sortie, "\tsw $s0, %s\n", quad->res->name);
                break;
        case LoadWAddress : fprintf(fichier_sortie, "\tlw $s0, %s\n", quad->arg1->name);
							fprintf(fichier_sortie, "\tlw $t1, ($s0)\n");
							fprintf(fichier_sortie, "\tsw $t1, %s\n", quad->res->name);
                break;
        case SaveWAddress :  load_value(quad->arg1, "$t1");
							fprintf(fichier_sortie, "\tlw $s0, %s\n", quad->res->name);
							fprintf(fichier_sortie, "\tsw $t1, ($s0)\n");
                break;
	}
}


void load_value(Symbol symbol, char* register_name)
{

	if(symbol == NULL)
		return	;

	switch (symbol->data_type)
	{
		case Constant : if(strstr(symbol->name,CONSTANT_) != NULL)
							fprintf(fichier_sortie,"\tli\t%s, %d\n",register_name,symbol->data.number);
						else
							fprintf(fichier_sortie,"\tlw\t%s, %s\n",register_name,symbol->name);
			break;
		case Integer  : fprintf(fichier_sortie,"\tlw\t%s, %s\n",register_name,symbol->name);
			 break;
	}
}


void gen_system_service_const()
{
		fprintf(fichier_sortie, "\t#System call service Constant\n");
		fprintf(fichier_sortie, "\tSYS_STRING_PRINT:\t4\n");
		fprintf(fichier_sortie, "\tSYS_INT_PRINT:\t1\n");
		fprintf(fichier_sortie, "\tSYS_EXIT:\t10\n");
		fprintf(fichier_sortie, "\tSYS_EXIT_VALUE:\t17\n\n");

		return;
}

void gen_utils_function()
{
	gen_function_exit();
	gen_function_print_string();
	gen_function_print_int();
	gen_function_exit_value();
	return;
}

void gen_entete_comment()
{
	fprintf(fichier_sortie, "#M1ILC2017 Represente\n");
	fprintf(fichier_sortie, "#Compilation Pelletier et Delrue\n");
	fprintf(fichier_sortie, "\t#-----------------#\n\n");

	return;
}

void gen_function_exit()
{
	fprintf(fichier_sortie, "L_%d:\n", next_quad_label);
	fprintf(fichier_sortie, "\n\n\t# Fonction utilitaire pour l'affichage et exit\n\n");
	fprintf(fichier_sortie, "# Sert à Exit\n");
	fprintf(fichier_sortie, "#Passer les arguments dans $a0 avant l'appel à la fonction\n");
	fprintf(fichier_sortie, "Exit:\n");
		fprintf(fichier_sortie, "\tlw   $v0, SYS_EXIT\n");
		fprintf(fichier_sortie, "\tsyscall\n\n");

	return;
}

void gen_function_print_string()
{
	fprintf(fichier_sortie, "# Sert à afficher un String\n");
	fprintf(fichier_sortie, "#Passer les arguments dans $a0 avant l'appel à la fonction\n");
	fprintf(fichier_sortie, "Print_f:\n");
		fprintf(fichier_sortie, "\tlw   $v0, SYS_STRING_PRINT\n");
		fprintf(fichier_sortie, "\tsyscall\n");
		fprintf(fichier_sortie, "\tjr   $ra\n\n");

	return;
}

void gen_function_print_int()
{
	fprintf(fichier_sortie, "# Sert à afficher un entier\n");
	fprintf(fichier_sortie, "#Passer les arguments dans $a0 avant l'appel à la fonction\n");
	fprintf(fichier_sortie, "Print_i:\n");
		fprintf(fichier_sortie, "\tlw   $v0, SYS_INT_PRINT\n");
		fprintf(fichier_sortie, "\tsyscall\n");
		fprintf(fichier_sortie, "\tjr   $ra\n\n");

	return;
}

void gen_function_exit_value()
{
	fprintf(fichier_sortie, "# Sert à Exit avec valeur\n");
	fprintf(fichier_sortie, "#Passer les arguments dans $a0 avant l'appel à la fonction\n");
	fprintf(fichier_sortie, "Exit_with_value:\n");
		fprintf(fichier_sortie, "\tlw   $v0, SYS_EXIT_VALUE\n");
		fprintf(fichier_sortie, "\tsyscall\n\n");
	return;
}
