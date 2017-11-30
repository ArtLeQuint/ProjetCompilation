#ifndef SLLIST_H
#define SLLIST_H

typedef struct sllist sllist;

//  sllist_empty : crée une liste dynamique simplement chainée sur le type
//    void * initialement vide. Renvoie un pointeur sur l'objet qui gère cette
//    liste en cas de succès et NULL en cas d'échec
extern sllist *sllist_empty(void);

//  sllist_is_empy : retourne 0 si la liste est vide 1 sinon
extern int sllist_is_empty (sllist *sll);

//  sllist_insert_tail : insère x en queue de la liste associée à sll. Renvoie x
//    en cas de succès, NULL en cas d'échec
extern void *sllist_insert_tail(sllist *sll, char *x);

extern void sllist_complete(sllist *sll, int quad, char quadList[1000][4]);

//  sllist_dispose : libère les ressources allouées à *ptrsll ainsi qu'à la
//    liste associée. Donne à *ptrsll la valeur NULL
extern void sllist_dispose(sllist **ptrsll);

//  sllist_concatenation_head : concatène en tête de la liste associée à sll2 la
//    liste associée à sll1. À la terminaison, la liste associée à sll1 est vide.
//    Aucune opération d'allocation ou de désallocation n'est effectuée
extern void sllist_concatenation_head (sllist *sll1, sllist *sll2);

#endif  // SLLIST_H
