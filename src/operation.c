/**
 * Définition des operations
 * Romain Pelletier & Arthur Delrue
*/
#include "operation.h"
void bin_operation(Operation operation, Expression res, Expression arg1, Expression arg2)
{
      Quad new_quad;
       init_to_null(res);
      res->result = table_new_tmp(symbol_table);
      new_quad = quad_gen(&next_quad_label, operation, arg1->result, arg2->result, res->result);
      res->code = arg1->code;
      quad_merge(&res->code, arg2->code);
      quad_merge(&res->code, new_quad);
}

void single_operation(Operation operation, Expression res, Expression arg1)
{
	Quad new_quad;
	new_quad = quad_gen(&next_quad_label, operation, arg1->result,  NULL, res->result);
	res->code = arg1->code;
	quad_merge(&res->code, new_quad);
}

void assignment_operation( Expression res, Expression arg1)
{
	Quad new_quad;
	res->result->state = Initialized;
	new_quad = quad_gen(&next_quad_label,Assignment, arg1->result, NULL, res->result);
	res->code = arg1->code;
	quad_merge(&res->code, new_quad);
}

void assignment_array_operation( Expression res, Expression arg1, Expression arg2)
{
	int a = -10;
	Quad new_quad;
	new_quad = quad_gen(&a, SaveWAddress, arg2->result, NULL, arg1->result);
	arg1->result->data_type = Integer;
	res->result = arg2->result;
	res->code = arg1->code;
	quad_merge(&res->code, arg2->code);
	quad_merge(&res->code, new_quad);
	
}
	

void rel_operation(Operation operation, Condition res_condition, Expression arg1, Expression arg2)
{
	Quad new_quad, new_quad2 ;
	//true quad
	new_quad = quad_gen(&next_quad_label, operation, arg1->result,  arg2->result, NULL);
	res_condition->trueList = quad_list_new(new_quad);
	//false quad
	new_quad2 = quad_gen(&next_quad_label,Goto, NULL,NULL, NULL);
	res_condition->falseList = quad_list_new(new_quad2);
	// code merging
	res_condition->code = arg1->code;
	quad_merge(&res_condition->code,arg2->code);
	quad_merge(&res_condition->code, new_quad);
	quad_merge(&res_condition->code, new_quad2);
}

void jump_operation(Operation operation, Expression res, Expression arg1)
{
      Quad new_quad;
        init_to_null(res);
	if(arg1->result== NULL)
	{
	      Symbol symbol = table_new_number(symbol_table,0);
	      new_quad = quad_gen(&next_quad_label, operation, NULL, NULL, symbol);
	      res->code = new_quad;
	      return ;
	}
      new_quad = quad_gen(&next_quad_label, operation, NULL, NULL, arg1->result);
      res->code = arg1->code;
      quad_merge(&res->code, new_quad);
}

void init_to_null(Expression expression)
{
	expression->code = NULL;
	expression->result = NULL;
	expression->nextList = NULL;
	
}

int int_power(int number, int power)
{
	int power_res = 1;
	int i;
	for(i = 0; i < power; i++)
		power_res *= number;
	
	return power_res;
}
