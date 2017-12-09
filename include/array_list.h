/*Fait par Romain Pelletie et Arthur Delrue
 M1 ILC 2017*/

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdio.h>
#include <stdlib.h>
typedef int Element; /**< Un élément de la list*/
/**
 * \struct struct _array_element
 * \typedef struct _array_element array_element_t
 * \typedef struct _array_element* ArrayElement
 * Définition du type d'un élément de la liste
 */
typedef struct _array_element{
	Element value; /**< La valeur du noeud */
	struct _array_element* next; /**< Pointeur sur l'élément suivant*/
} array_element_t, *ArrayElement;
/**
 * \struct struct array_list
 * \typedef struct _array_list array_list_t
 * \typedef struct _array_list* ArrayList 
 * Définition du type de la liste chainée d
 */
typedef struct _array_list{
		ArrayElement head; /**< Tete de la liste */
		ArrayElement tail; /**<  La queue de la liste*/
} array_list_t, *ArrayList;

ArrayElement list_new_element(Element element);
ArrayList list_new();
void list_add(ArrayList list, Element element);
void list_merge(ArrayList list, ArrayList list2);
void list_free(ArrayList list);
void list_free_inside(ArrayList list);
int list_length(ArrayList list);
void list_print_break(ArrayList list, int break_length);
void list_print(ArrayList list);

#endif
