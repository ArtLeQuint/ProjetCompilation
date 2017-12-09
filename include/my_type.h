/*Fait par Romain Pelletier et Arthur Delrue
 M1 ILC 2017*/
#ifndef MY_TYPE_H
#define MY_TYPE_H

/* type de données à manipuler */
typedef enum { NotDefine, Void, Constant, Integer, String, Stencil, Arraytype, Procedure } DataType;
/* Etat d'une variable*/
typedef enum { NotInitialized, Initialized} VariableState;
/* bolleen */
typedef enum { false = 0, true } bool;


#endif
