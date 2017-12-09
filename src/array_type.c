/**
 * Définition des listes
 * Romain Pelletier & Arthur Delrue
*/
#include "array_type.h"

Array array_new()
{
	Array array = malloc(sizeof(array_t));
	
	if(array == NULL)
		return NULL;
	
	array->dim_values = NULL;
	array->element_list= NULL;
	array->limits= NULL;
	array->dim_number = 0;
	array->elements_number = 0;
	return array;
}

void array_init(Array array, ArrayList dim_values, ArrayList array_elements)
{
	if(array == NULL){
		fprintf(stderr, "Can't assign array elements values, becaure the array pointer is null\n");
		return ;
	}
	array->element_list = array_elements;
	array->dim_values = dim_values;
	array->dim_number = list_length(dim_values);
	array->elements_number = compute_array_size(dim_values);
	array->limits = compute_array_limits(dim_values);
}

Array array_create_init( ArrayList dim_values, ArrayList array_elements)
{
	Array array = array_new();
	array_init(array, dim_values, array_elements);
	return array;
} 

int compute_array_size(ArrayList element_list)
{
	int size = 1;
	if(element_list == NULL)
		return 0;
		
	ArrayElement tmp = element_list->head;
	while(tmp != NULL){
		size *= tmp->value;
		tmp = tmp->next; 
	}
	return size;
}

int* compute_array_limits(ArrayList dim_list)
{
	int i, j, limit_value;
	int nb_dim = 0;
	nb_dim = list_length(dim_list);
	
	if(nb_dim < 2)
		return NULL;
	
	int* limits = (int*) malloc((nb_dim - 1) * sizeof(int) );
	ArrayElement tmp = dim_list->head;
	ArrayElement tmp_save = dim_list->head;
	
	for(i = 0; i < nb_dim -1 ; i++)
	{
		tmp_save = tmp_save->next;
		tmp = tmp_save;
		limit_value = 1;
		
		while( tmp != NULL )
		{
			limit_value *= tmp->value;
			tmp = tmp->next;
		}
		limits[i] = limit_value;
	}
	
	return limits;

}

int array_get_limit(Array array, int rank)
{
	if(array == NULL || rank >= array->dim_number)
		return 1;
	
	if(rank < 1)
	{
		fprintf(stderr, "the limit rank must be equal or greater than 1 \n");
		return 1;
	}
	
	return array->limits[rank-1];
}


void array_free_inside(Array array)
{
	if(array == NULL)
		return;
	
	if(array->dim_values != NULL)
		list_free(array->dim_values);
		
	if(array->limits != NULL)
		free(array->limits);
		
	if(array->element_list!= NULL)
		list_free(array->element_list);
}

void array_free(Array array)
{
	if(array == NULL)
		return;
				
	array_free_inside(array);
	free(array);
	array = NULL;
	return;
}
