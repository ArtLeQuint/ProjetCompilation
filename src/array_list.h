/*Fait par Romain Pelletier et Arthur Delrue
 M1 ILC 2017*/

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdio.h>
#include <stdlib.h>
typedef int Element;
/* Element d'une liste */
typedef struct _array_element{
	Element value;
	struct _array_element* next;
} array_element_t, *ArrayElement;
/* Les Listes */
typedef struct _array_list{
		ArrayElement head; 
		ArrayElement tail;
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
