/*Fait par Romain Pelletie et Arthur Delrue
 M1 ILC 2017*/
#ifndef MY_TYPE_H
#define MY_TYPE_H

/**
 * \typedef  enum DataType
 * Définition des  type de données à manipuler
 */
typedef enum { NotDefine, Void, Constant, Integer, String, Stencil, Arraytype, Procedure } DataType;
/**
 * \typedef  enum VariableState
 * Définition du type identifiant l'état d'une variable
 */
typedef enum { NotInitialized, Initialized} VariableState;
/**
 * \typedef  enum bool 
 * Définition du type booleen
 */
typedef enum { false = 0, true } bool;


#endif
