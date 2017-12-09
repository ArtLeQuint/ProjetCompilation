/*Fait par Romain Pelletie et Arthur Delrue
 M1 ILC 2017*/

#ifndef OPTIMISATION_H
#define OPTIMISATION_H

#include "symbol.h"
#include "quad.h"
#include "operation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern SymbolTable symbol_table;;/**<  La table de symbole*/
/**
 * \struct struct _loop
 * \typedef struct loop_t
 * \typedef struct* Loop
 * Définition d'un type contenant une intervalle définissant une boucle
 */
typedef struct _loop{
	int loop_start;/**<  Label  identifiant le debut  de la boucle */
	int loop_end;/**< Label  identifiant la fin  de la boucle */
	struct _loop* next;/**< Boucle suivante */
}loop_t, *Loop;

Loop loop_list ;/**< La liste de boucle des quads */
/**
 * \fn Loop loop_detect(Quad quad)
 * \brief Verifie si le quad définit une boucle et si oui, la renvoie
 * \param quad : le quad à verifier
 * \return Renvoie la boucles du quad s il y en a ,  NULL sinon
 */
Loop loop_detect(Quad quad);
/**
 * \fn Loop loop_detect(Quad quad)
 * \brief Verifie si le label se trouve entre une boucle
 * \param loop_list : La list des boucles
 * \param label : le label à verifié
 * \return Renvoie \b true si le label est entre l'une des boucles, \b false sinon
 */
bool is_in_loop(Loop loop_list, int label);

/**
 * \fn Loop optimization_quad_assignment(Quad quad)
 * \brief supprime les affections du type :
 * 	tmp = exp op exp
 * variable = tmp
 * En les remplacants par variable = exp op exp
 * Cette fonctions détecte aussi la liste des boucles
 * \param quad : la list des quad
 * \return Renvoie la liste des boucles s il y en a , sinon NULL
 */
Loop optimization_quad_assignment(Quad quad);

/**
 * \fn void optimization_aritmetic_computation(Quad quad)
 * \brief Remplaces les operation sur les constante par le resultat par exemple:
 * remplce <b>	variable = 2 + 3 <b> par <b> variable = 5 <b>
 * \param quad : la list des quad
 */
void optimization_aritmetic_computation(Quad quad);
/**
 * \fn void optimization_constant_propagation(Quad quad)
 * \brief Propage les constantes dans les expression
 * \param quad : la list des quad
 */
void optimization_constant_propagation(Quad quad);
/**
 * \fn void optimization_quad(Quad quad
 * \brief Fonction d'optimisation des quads.
 * Elle utilise les autres definies ci dessus
 * \param quad : la list des quad
 */
void optimization_quad(Quad quad);
void loop_free(Loop quad);

#endif
