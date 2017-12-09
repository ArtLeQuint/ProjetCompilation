/**
 * Définition des quads
 * Romain Pelletier & Arthur Delrue
*/
#include "quad.h"

Quad quad_gen(int* label, Operation operation, Symbol arg1, Symbol arg2, Symbol res)
{
	Quad new = malloc(sizeof(Quad_t));
	new->label = *label;
	(*label)++;
	new->operation = operation;
	new->arg1 = arg1;
	new->arg2 = arg2;
	new->res = res;
	new->next = NULL;
	
	return new;
}

void quad_merge(Quad* quad1, Quad quad2)
{
	if(*quad1 == NULL){	
		*quad1 = quad2;
		return;
	}
	
	Quad tmp = *quad1;
	while(tmp->next != NULL)
		tmp =tmp->next;
	
	tmp->next = quad2;		
}

void quad_print(Quad quad)
{
	 if(quad == NULL)
		return;
	
	int label = quad->label;
	if(label < 0) // On affiche pas  les labels marqué "-1"
		printf ("\t");
	else
		printf ("%d:\t",label);
    switch(quad->operation)
    {
        case Assignment: printf("%s = %s ", quad->res->name, quad->arg1->name);
                break;
        case Add: printf("%s = %s + %s", quad->res->name, quad->arg1->name, quad->arg2->name);
                break;
        case Sub: printf("%s = %s - %s", quad->res->name, quad->arg1->name, quad->arg2->name);
                break;
        case Mult: printf("%s = %s * %s", quad->res->name, quad->arg1->name, quad->arg2->name);
                break;
        case Div: printf("%s = %s / %s", quad->res->name, quad->arg1->name, quad->arg2->name);
                break;
        case Modulo: printf("%s = %s %% %s", quad->res->name, quad->arg1->name, quad->arg2->name);
                break;
        case StencilOp: printf("%s = %s $ %s", quad->res->name, quad->arg1->name, quad->arg2->name);
                break;
        case UnarySub: printf("%s = -%s", quad->res->name, quad->arg1->name);
                break;
        case Abs: printf("%s = abs(%s)", quad->res->name, quad->arg1->name);
                break;
        case Increment: printf("%s = %s + 1", quad->res->name, quad->arg1->name); 
                break;
        case Decrement: printf("%s =  %s - 1", quad->res->name, quad->arg1->name); 
                break;
        case Equal: printf("if(%s == %s)  goto  %d", quad->arg1->name, quad->arg2->name, quad->res->data.number); 
                break;
        case NotEqual: printf("if(%s != %s)  goto  %d", quad->arg1->name, quad->arg2->name, quad->res->data.number); 
                break;
        case GreaterThan: printf("if(%s > %s)  goto %d", quad->arg1->name, quad->arg2->name, quad->res->data.number); 
                break;
        case GreaterThanEqual: printf("if(%s >= %s)  goto %d", quad->arg1->name, quad->arg2->name, quad->res->data.number); 
                break;
        case LesserThan: printf("if(%s < %s)  goto %d", quad->arg1->name, quad->arg2->name, quad->res->data.number); 
                break;
        case LesserThanEqual: printf("if(%s <= %s)  goto %d", quad->arg1->name, quad->arg2->name, quad->res->data.number); 
                break;
        case Printf: printf("printf(%s)", quad->res->data.string); 
                break;
        case Printi: printf("printi(%s)", quad->res->name ); 
                break;
        case Goto: printf("goto %d", quad->res->data.number ); 
                break;
        case Return: printf("return %d", quad->res->data.number ); 
                break;
        case Exit: printf("exit %d", quad->res->data.number ); 
                break;
	case LoadAddress: printf("la %s,  %s ", quad->res->name, quad->arg1->name);
		break;
	case LoadWAddress: printf("lw %s, ( %s ) ", quad->res->name, quad->arg1->name);
		break;
	case SaveWAddress: printf("sw %s, ( %s ) ",  quad->arg1->name, quad->res->name);
		break;
	default : printf("Attention, Un cas nos géré!!!");
    }
    printf("\n");
    
    quad_print(quad->next);
			
}

void quad_free(Quad quad)
{
	if(quad == NULL)
		return;
	
	Quad tmp = quad->next;
	free(quad);
	quad_free(tmp);
}

QuadList quad_list_new(Quad quad)
{
	QuadList new_quad_list = malloc(sizeof(quad_list_t));
	new_quad_list->code = quad;
	new_quad_list->next = NULL;
	
	return new_quad_list;
}

void quad_list_merge(QuadList* quad_list1,QuadList quad_list2)
{
	if(*quad_list1 == NULL)
	{
		*quad_list1 = quad_list2;
		return;
	}
	
	QuadList tmp = *quad_list1;
	
	while(tmp->next != NULL)
		tmp =tmp->next;
	
	tmp->next = quad_list2;
}

void quad_list_complete(QuadList quad_list, Symbol label)
{
	if(quad_list == NULL)
		return ;
	
	QuadList tmp = quad_list;
	while(tmp != NULL)
	{
		tmp->code->res = label;
		tmp = tmp->next;
	}
}

void quad_list_free(QuadList quad_list)
{
	if(quad_list == NULL)
		return ;
	
	QuadList tmp = quad_list->next;
	free(quad_list);
	quad_list_free(tmp);
}

bool is_relation_operation (Quad quad)
{
	if((quad->operation == Assignment) || (quad->operation == Add) || 
	   (quad->operation == Sub) || (quad->operation == Mult) || 
	   (quad->operation == Div) || (quad->operation == Modulo))
	{
		return false;
	}
	return true;
}
