/*Fait par Romain Pelletie et Arthur Delrue
 M1 ILC 2017*/
#ifndef ARRAY_ELEMENTS_H
#define ARRAY_ELEMENTS_H

#include <stdlib.h>
#include <stdio.h>
#include "my_type.h"
#include "array_list.h"

/**
 * \struct struct _array
 * \typedef struct array_t
 * \typedef struct *Array
 * Définition du type tableau Array
 */
typedef struct _array{
	ArrayList dim_values; /**< Liste des éléments de la dimension*/
	ArrayList element_list;/**< Liste des éléments du tableau*/
	int dim_number;/**< Nombre de dimension */
	int elements_number;/**< Nombre d éléments */
	int* limits;/**< Les limites pour le calculs des décalage */
}array_t, *Array;

Array array_new();
void array_init(Array array, ArrayList dim_values, ArrayList array_elements);
Array array_create_init(ArrayList dim_values, ArrayList array_elements);
int compute_array_size(ArrayList element_list);
int* compute_array_limits(ArrayList dim_list);
void array_free_inside(Array array);
void array_free(Array array);

#endif
