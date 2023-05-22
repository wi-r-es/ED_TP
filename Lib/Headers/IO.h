/*******************************************************************************
 *  @file IO.h                                                                 *
 *  @brief Function prototypes to load ADTs from files.                        *
 *                                                                             *
 *  This contains the prototypes for loading clients, employees and products   *
 *  from input files.                                                          *
 *                                                                             *
 *******************************************************************************/

#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

/* -- Includes -- */
/* libc includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* clients header file */
#include "clients.h"
/* funcionarios header file */
#include "funcionarios.h"
/* produto header file */
#include "produto.h"
/* listaGenerica header file */
#include "listaGenerica.h"
/* used for testing purposes only */
#include <fcntl.h>


/************************************************************************************************************************************************
 * @brief Creates a Client LL from a file.                                                                                                      *
 *                                                                                                                                              *
 *       Reads data about clients from a file and creates a new Client struct/element for each line of data.                                    *
 *       The function then adds each new CLIENTE to the linked list provided as an argument.                                                    *
 *       The first letter of each client's name is also added to a character array provided as an argument, to create a hashtable later on.     *
 *                                                                                                                                              *
 * @param LC :  LL to store the newly created clients.                                                                                          *
 * @param letras : a string pointer to save the unique initials of all the clients read from the file.                                          *
 * @see CriarClient()                                                                                                                           *
 * @see AddLGInicio()                                                                                                                           *
 * @see logging()                                                                                                                               *
 * @return None.                                                                                                                                *
 ************************************************************************************************************************************************/
void Load_Client(LG *LC, char *letras);

/************************************************************************************************************************************************
 * @brief Creates a Employee LL from a file.                                                                                                    *
 *                                                                                                                                              *
 *       Reads data about employees from a file and creates a new Employee struct/element for each line of data.                                *
 *       The function then adds each new Employee to the linked list provided as an argument.                                                   *
 *                                                                                                                                              *
 * @param LF :  LL to store the newly created employees.                                                                                        *
 * @see CriarEmployee()                                                                                                                         *
 * @see AddLGFim()                                                                                                                              *
 * @see strtok()                                                                                                                                *
 * @see strcspn()                                                                                                                               *
 * @see isalpha()                                                                                                                               *
 * @see toupper()                                                                                                                               *
 * @see logging()                                                                                                                               *
 * @return None.                                                                                                                                *
 ************************************************************************************************************************************************/
void Load_Funcionario(LG *LF);

/************************************************************************************************************************************************
 * @brief Creates a Prodcuts LL from a file.                                                                                                    *
 *                                                                                                                                              *
 *       Reads data about products from a file and creates a new Product struct/element for each line of data.                                  *
 *       The function then adds each new Product to the linked list provided as an argument.                                                    *
 *                                                                                                                                              *
 * @param LP :  LL to store the newly created products.                                                                                         *
 * @see CriarProduct()                                                                                                                          *
 * @see AddLGInicio()                                                                                                                           *
 * @see strcspn()                                                                                                                               *
 * @see atoi()                                                                                                                                  *
 * @see strtof()                                                                                                                                *
 * @see strtod()                                                                                                                                *
 * @see strtok()                                                                                                                                *
 * @see logging()                                                                                                                               *
 * @return None.                                                                                                                                *
 ************************************************************************************************************************************************/
void Load_Produtos(LG *LP);

/**********************************************************************************************************************************
 * @brief For testing purposes only... Use Unix flags for file permissions/modes                                                  *
 **********************************************************************************************************************************/
void writeToFile(char *b);
/**********************************************************************************************************************************
 * @brief For testing purposes only...                                                                                            *
 **********************************************************************************************************************************/
void writeTesting(char *datafile, char *funcname, char *info);

#endif // IO_H_INCLUDED
