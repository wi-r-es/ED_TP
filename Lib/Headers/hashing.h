/*******************************************************************************
 *  @file hashing.h                                                            *
 *  @brief Function prototypes to manage hashing tables ADt.                   *
 *                                                                             *
 *  This contains the prototypes for managig hashing tables.                   *
 *                                                                             *
 *******************************************************************************/

#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED
/* -- Includes -- */
/* libc includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* listaGenerica header file */
#include "listaGenerica.h"
/* clients header file */
#include "clients.h"
/* IO header file */
#include "IO.h" // used for testing

/*
#define NUM_ENTRADAS 27 //Letras no alfabeto +1
*/

/************************************************************************************************************************************************************
 * Hashing table ADT structure and vars description                                                                                                         *
 * DADOS:                                                                                                                                                   *
 * >>>>>>Faixa                      -> char Array/string of the ID of each client.                                                                          *
 * >>>>>>Clientes                   -> LL for the clients of a specific key.                                                                                *
 * NEL                              -> Number of keys/faixa.                                                                                                *
 ************************************************************************************************************************************************************/
typedef struct
{
    char Faixa;
    ListaGenerica *Clientes;
} GROUP;
typedef struct
{
    GROUP *DADOS;
    int NEL;
} HASHING;

/**********************************************************************************************************************************
 * @brief Creates a new hash table based on the size of the string received, and allocates the necessary memory.                  *
 * @param str : a string containing the initials that will be keys of the new hash table.                                         *
 * @see ec_malloc()                                                                                                               *
 * @see fatal()                                                                                                                   *
 * @return A pointer to a newly created Hash Table.                                                                               *
 **********************************************************************************************************************************/
HASHING *CriarHASHING(char *str);

/**************************************************************************
 * @brief Frees the memory allocated to a give hash table.                *
 * @param H : a pointer to the hash table. (Type HASHING*)                *
 * @return None.                                                          *
 **************************************************************************/
void DestruirHASHING(HASHING *H);

/************************************************************************************
 * @brief Prints out a given hash table, and the informaton of each key vaue.       *
 * @param H : a pointer to the hash table. (Type HASHING*)                          *
 * @see ShowFaixa()                                                                 *
 * @return None.                                                                    *
 ************************************************************************************/
void ShowHASHING(HASHING *H);

/***************************************************************************
 * @brief Prints out the content of a given key from the hash table.       *
 *                                                                         *
 *        In this case a list of clients that are stored with that key.    *
 *                                                                         *
 * @param H : a pointer to the hash table. (Type HASHING*)                 *
 * @param p : hash table key.                                              *
 * @return None.                                                           *
 ***************************************************************************/
void ShowFaixa(HASHING *H, int p);

/**********************************************************************************************************************************************************
 * @brief Adds a given client to the according key to the given hash table.                                                                               *
 *                                                                                                                                                        *
 *        Calculates the position for the element using the FuncaoHASHING function                                                                        *
 *        and adds the element to the linked list Clientes at that position.                                                                              *
 *                                                                                                                                                        *
 * @param H : a pointer to the hash table. (Type HASHING*)                                                                                                *
 * @param c : pointer to element to be added. (Type void*)                                                                                                *
 * @see FuncaoHASHING()                                                                                                                                   *
 * @see AddLGInicio()                                                                                                                                     *
 * @return 1 if the addition is successful, -1 if the calculated position is less than 0 (this is, not valid), and -2 if either H or c is a null pointer. *
 **********************************************************************************************************************************************************/
int AddHASHING(HASHING *H, void *c);

/**********************************************************************************************************************************************************
 * @brief Calculates the position/key (hash value) for an client c in the specified hash table.                                                           *
 *                                                                                                                                                        *
 *        It extracts the first character of the client's name and matches it against the Faixa property of each entry in DADOS.                          *
 *        If a match is found, the position is set to the corresponding index.                                                                            *
 *                                                                                                                                                        *
 * @param H : a pointer to the hash table. (Type HASHING*)                                                                                                *
 * @param c : pointer to element to be added. (Type void*)                                                                                                *
 * @return The calculated position if it is valid (between 0 and NEL - 1), otherwise it returns -1. If either H or c is a null pointer, it returns -2.    *
 **********************************************************************************************************************************************************/
int FuncaoHASHING(HASHING *H, void *c);

/**********************************************************************************************************************************************************
 * @brief Loads elements from a linked list C into the specified HASHING ADT hash table.                                                                  *
 *                                                                                                                                                        *
 *        It iterates over the linked list and adds each element to hash_table using the AddHASHING function.                                             *
 *                                                                                                                                                        *
 * @param H : a pointer to the hash table. (Type HASHING*)                                                                                                *
 * @param C : LL to clients elements. (Type LG*)                                                                                                          *
 * @see AddHASHING()                                                                                                                                      *
 * @return None.                                                                                                                                          *
 **********************************************************************************************************************************************************/
void LoadHashingFromLinkedList(HASHING *hash_table, LG *C);

/*************************************************************************************************************************************************************
 * @brief Retrieves an element at a specified position p within the LL Clientes of a given hash table and with a specified Faixa value f.                    *
 *                                                                                                                                                           *
 *        It first checks if hash_table is valid and retrieves the corresponding linked list Clientes based on the Faixa value.                              *
 *        It then iterates through the linked list to find the element at the desired position.                                                              *
 *                                                                                                                                                           *
 * @param hash_table : a pointer to the hash table. (Type HASHING*)                                                                                          *
 * @param f : faixa of the element to be retrieved.                                                                                                          *
 * @param p : position of the element inside the faixa f LL.                                                                                                 *
 * @see fatal()                                                                                                                                              *
 * @return Pointer to the retrieved element if successful, and NULL if the hash_table is invalid, the linked list is empty or the position is out of bounds. *                                                                                                                                         *
 *************************************************************************************************************************************************************/
void *getElementInFaixa_Pos(HASHING *hash_table, int f, int p);

#endif // HASHING_H_INCLUDED
