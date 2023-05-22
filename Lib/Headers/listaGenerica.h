/*******************************************************************************
 *  @file listaGenerica.h                                                      *
 *  @brief Function prototypes for Generic Linked Lists.                       *
 *                                                                             *
 *  This contains the prototypes for the managing of generic LL.               *
 *                                                                             *
 *******************************************************************************/

#ifndef LISTAGENERICA_H_INCLUDED
#define LISTAGENERICA_H_INCLUDED
/* -- Includes -- */
/* libc includes. */
#include <stdio.h>
#include <stdlib.h>

// #include "clients.h"
/* funcionarios header file */
#include "funcionarios.h"
/* produto header file */
#include "produto.h"
// #include "supermercado.h"

/**************************************************************************************************
 * Generic LL ADT structure and vars description                                                  *
 * LG:                                                                                            *
 * >>>>>>NEL          -> Number of elements in LL                                                 *
 * >>>>>>head         -> pointer to the head of the LL                                            *
 * >>>>>>tail         -> pointer to the tail of the LL                                            *
 * NODE:                                                                                          *
 * >>>>>>info         -> pointer to the ADT in the LL (can be clients, products, employees)       *
 * >>>>>>next         -> pointer to the next element in the LL                                    *
 * >>>>>>prev         -> pointer to the previous element in the LL                                *
 **************************************************************************************************/
typedef struct NODE
{
    void *info;
    struct NODE *next;
    struct NODE *prev;

} NODE;
typedef struct
{
    int NEL;
    NODE *head;
    NODE *tail;
} ListaGenerica, LG;
/*
typedef struct
{
    int height;
    NO_TREE *Root;
}TREE; */

/****************************************************************************************
 * @brief Creates a new Generic Linked List                                             *
 *                                                                                      *
 *        Creates a new generic LL and sets all pointers to NULL, and NEL to 0.         *
 *                                                                                      *
 * @see ec_malloc()                                                                     *
 * @see fatal()                                                                         *
 * @see logging()                                                                       *
 * @return A pointer to a newly created Generic LL, or NULL if the allocation failed.   *
 ****************************************************************************************/
ListaGenerica *CriarLG();

/****************************************************************************************************
 * @brief Frees the memory allocated to a Generic LL.                                               *
 *                                                                                                  *
 *        Recieves the proper function to the ADT in the generic LL to free the allocated memory.   *
 *        And recieves an integer that tells if its to free the element memory or just the Nodes.   *
 *                                                                                                  *
 * @param lg : a pointer to a generic LL. (Type LG*)                                                *
 * @param fdest : a pointer to a function to free the elements memory. (Type void*)                 *
 * @param t : integer that works as a flag.                                                         *
 * @see logging()                                                                                   *
 * @return None.                                                                                    *
 ****************************************************************************************************/
void DestruirLG(ListaGenerica *lg, void (*fdest)(void *), int t);

/********************************************************************************
 * @brief Shows a Generic Linked List Elements information.                     *
 *                                                                              *
 *        Receives a proper function print the element information.             *
 *                                                                              *
 * @param lg : a pointer to a generic LL. (Type LG*)                            *
 * @param f : a pointer to a function to print the elements info. (Type void*)  *
 * @return None.                                                                *
 ********************************************************************************/
void ShowLG(ListaGenerica *lg, void (*f)(void *));

/************************************************************************************
 * @brief Adds an element to the end of a Generic Linked List. (Stack behaviour)    *
 *                                                                                  *
 * @param lg : a pointer to a generic LL. (Type LG*)                                *
 * @param X : a pointer to the element to be added to the generic LL. (Type void*)  *
 * @return None.                                                                    *
 ************************************************************************************/
void AddLGFim(ListaGenerica *lg, void *X); // add stack

/**********************************************************************************************
 * @brief Adds an element to the beginning of a Generic Linked List. (Heap/Queue behaviour)   *
 *                                                                                            *
 * @param lg : a pointer to a generic LL. (Type LG*)                                          *
 * @param X : a pointer to the element to be added to the generic LL. (Type void*)            *
 * @return None.                                                                              *
 **********************************************************************************************/
void AddLGInicio(ListaGenerica *lg, void *X);

/**************************************************************************************************************
 * @brief Searches for the given element in the given Linked List                                             *
 *                                                                                                            *
 *        The fsearch function will return 1 if the element was found, 0 otherwise.                           *
 *                                                                                                            *
 * @param lg : a pointer to a generic LL. (Type LG*)                                                          *
 * @param key : Value for comparisson with the elements to know if the element was found.                     *
 * @param fsearch : a pointer to a function to search for the specific elements type. (Type void*)            *
 * @return A pointer to the element if it was found, NULL otherwise or if the parameters were null pointers.  *
 **************************************************************************************************************/
void *SearchLG(LG *lg, void *key, int (*fsearch)(void *, void *));

/**************************************************************************************************************
 * @brief Checks wethers a given element belongs to the Generic LL.                                           *
 *                                                                                                            *
 *        The fcomp function will return 1 if the element was equal to the given one, 0 otherwise.            *
 *                                                                                                            *
 * @param lg : a pointer to a generic LL. (Type LG*)                                                          *
 * @param X : pointer to the element for comparisson to know if the element is the same. (Type void*)         *
 * @param fcomp : a pointer to a function to compare the specific elements. (Type void*)                      *
 * @return 1 if the element belonged to the LL, 0 otherwise or if the paremeters where NULL pointers.         *
 **************************************************************************************************************/
int PertenceLG(ListaGenerica *lg, void *X, int (*fcomp)(void *, void *));

/*********************************************************************************
 * @brief Gets an element at the given position.                                 *
 *                                                                               *
 * @param lg : a pointer to a generic LL. (Type LG*)                             *
 * @param p : position of the element to get on the LL.                          *
 * @return The element at the given position, or NULL if lg was a Null pointer.  *
 *********************************************************************************/
void *getByPos(LG *lg, int p);

#endif // LISTAGENERICA_H_INCLUDED
