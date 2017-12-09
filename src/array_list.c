/**
 * Définition des listes
 * Romain Pelletier & Arthur Delrue
*/

#include "array_list.h"


ArrayElement list_new_element(Element element)
{
	ArrayElement new_element = malloc( sizeof(array_element_t));
	new_element->value = element;
	new_element->next = NULL ;
	return new_element;
}	

ArrayList list_new()
{
	ArrayList array_list1 = (ArrayList) malloc(sizeof(array_list_t));
	array_list1->head = NULL;
	array_list1->tail = NULL;
	return array_list1;
}

void list_add(ArrayList list, Element element)
{
	ArrayElement array_elmt = list_new_element(element);
	if(list->head == NULL){
		list->head = array_elmt ;
		list->tail = array_elmt ;
		return;
	}
	list->tail->next = array_elmt;
	list->tail = array_elmt;
}

void list_merge(ArrayList list, ArrayList list2)
{
	if(list->head == NULL){
		list->head = list2->head ;
		list->tail = list2->tail ;
		return;
	}
	if(list2->head == NULL)
		return ;

	list->tail->next =  list2->head;
	list->tail =  list2->tail;
}

void list_free(ArrayList list)
{
	if(list == NULL)
		return;
	
	list_free_inside(list);
	free(list);
}

void list_free_inside(ArrayList list)
{
	if(list == NULL)
		return;
	ArrayElement tmp2,  tmp = list->head;
	
	while(tmp != NULL){
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
}

int list_length(ArrayList list)
{
	int length = 0;
	ArrayElement tmp = list->head;
	
	while(tmp != NULL) {
		length++;
		tmp = tmp->next;
	}
	return length;
}
void list_print_break(ArrayList list, int break_length)
{
		int len = 0;
		ArrayElement tmp = list->head;
		
		while(tmp!=NULL)
		{
			printf("%d", tmp->value);
			tmp = tmp->next;
			len++;
			if(tmp != NULL && len != break_length)
				printf(", ");
			else
			{
				printf("\n");
				len = 0;
			}
		}
}

void list_print(ArrayList list)
{
		list_print_break(list, 10);
}



