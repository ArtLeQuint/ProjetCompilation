#include <stdlib.h>
#include <string.h>
#include "sllist.h"

typedef struct csllist csllist;

struct csllist {
  void *value;
  csllist *next;
};

struct sllist {
  csllist *head;
  csllist *tail;
};

sllist *sllist_empty(void) {
  sllist *sll = malloc(sizeof *sll);
  if (sll == NULL) {
    return NULL;
  }
  sll -> head = NULL;
  sll -> tail = NULL;
  return sll;
}

int sllist_is_empty (sllist *sll){
  return sll -> head == NULL ? 0 : 1;
}

void *sllist_insert_tail(sllist *sll, char *x) {
  if (x == NULL) {
    return NULL;
  }
  csllist *p = malloc(sizeof *p);
  if (p == NULL) {
    return NULL;
  }
  p -> value = x;
  p -> next = NULL;
  if (sll -> head == NULL) {
    sll -> head = p;
  } else {
    sll -> tail -> next = p;
  }
  sll -> tail = p;
  return x;
}

void sllist_complete(sllist *sll, int quad, char quadList[1000][4]) {
  csllist *p = sll -> head;
  while (p != NULL) {
    // TODO faire en sorte que cela remplisse les vides du tableau de quad
    // avec quad
    p = p -> next;
  }
}

void sllist_dispose(sllist **ptrsll) {
  csllist *p = (*ptrsll) -> head;
  while (p != NULL) {
    csllist *t = p;
    p = p -> next;
    free(t);
  }
  free(*ptrsll);
  *ptrsll = NULL;
}

void sllist_concatenation_head (sllist *sll1, sllist *sll2) {
  if (sllist_is_empty(sll1) == 0) {
    return;
  }
  if (sllist_is_empty(sll2) == 0) {
    sll2 -> head = sll1 -> head;
    sll2 -> tail = sll1 -> tail;
    sll1 -> head = NULL;
    sll1 -> tail = NULL;
  } else {
    sll1 -> tail -> next = sll2 -> head;
    sll2 -> head = sll1 -> head;
    sll1 -> head = NULL;
    sll1 -> tail = NULL;
  }
}
