/*******************************************************************************
 *  @file caixa.h                                                              *
 *  @brief Function prototypes to manage box ADT.                              *
 *                                                                             *
 *  This contains the prototypes for managig boxes and their bit fields vars.  *
 *                                                                             *
 *******************************************************************************/

#ifndef CAIXA_H_INCLUDED
#define CAIXA_H_INCLUDED

/* -- Includes -- */
/* libc includes. */
#include <stdio.h>
#include <stdlib.h>
/* funcionarios header file */
#include "funcionarios.h"
/* listaGenerica header file */
#include "listaGenerica.h"
/* queue header file */
#include "queue.h"
/* utils header file */
#include "utils.h" /* for useful functions, and ec_malloc() used to check errors during allocation */

/************************************************************************************************************************************************************
 * BOX ADT structure and vars description                                                                                                                   *
 * numero                      -> char representing the box element                                                                                         *
 * status                      -> bit field variable. 0 = closed; 1 = open.                                                                                 *
 * in_service                  -> bit field variable. 0 = free/ready to attend; 1 = busy/attending a client.                                                *
 * closing                     -> bit field variable. 0 = not being closed; 1 = closing soon.                                                               *
 * itemsInQueue                -> integer to represent the total number of products/items in the queue LL.                                                  *
 * num_produtos_oferecidos     -> integer to represent the total nnumber of offered products.                                                               *
 * valor_produtos_oferecidos   -> variable that represents the total value of offered products.                                                             *
 * cashBox                     -> variable to represent the total cash a box have, starting at 0 before it starts serving clients.                          *
 * QUEUE                       -> pointer of type LG ADT to represent the queue of a box, and stores the clients ona specific queue.                        *
 * auxiliary                   -> pointer to the client being attended. NULL when no client is being attended or at the start of the simulation.            *
 * funcionario                 -> pointer to an employee. When the box changes from closed to open, an employee is assigned.                                *
 * served                      -> number of clients served.                                                                                                 *
 * totalProducts               -> total number of products sold.                                                                                            *
 ************************************************************************************************************************************************************/
typedef struct CAIXA
{
    char numero;
    unsigned int status : 1; // 0 fechada | 1 aberta
    unsigned int in_service : 1;
    unsigned int closing : 1;
    int itemsInQueue;
    int num_produtos_oferecidos;
    double cashBox;
    double valor_produtos_oferecidos;
    LG *QUEUE;
    void *auxiliary;
    Employee *funcionario;
    int served;
    int totalProducts;
} BOX, *ptr_caixa;

/************************************************************************************************************************************************
 * @brief Creates a BOX struct/element.                                                                                                         *
 *                                                                                                                                              *
 *       Creates a new BOX with the given _id.                                                                                                  *
 *       It allocates memory for a new BOX structure, initializes its properties, and returns a pointer to the new BOX object.                  *
 *                                                                                                                                              *
 * @param _id :  char ID/faixa of the new box to be created.                                                                                    *
 * @see ec_malloc()                                                                                                                             *
 * @return A pointer to the newly created box strcuture, or NULL if memory allocation failed.                                                   *
 ************************************************************************************************************************************************/
BOX *CriarCaixa(char _id);

/************************************************************************************************************************************************
 * @brief Generates a random number, and creates that random number of boxes.                                                                   *
 *                                                                                                                                              *
 *       This function generates a random number between 3 and 10, and creates that many new boxes using the CriarCaixa() function.             *
 *       It then adds these boxes to the end of the linked list pointed to by lcx.                                                              *
 *       If memory allocation fails during the creation of a new box, the function stops generating boxes and returns.                          *
 *                                                                                                                                              *
 * @param lcx :  LL to store the newly created boxes.                                                                                           *
 * @see getRandomInt()                                                                                                                          *
 * @see CriarCaixa()                                                                                                                            *
 * @see AddLGFim()                                                                                                                              *
 * @see fatal()                                                                                                                                 *
 * @return None.                                                                                                                                *
 ************************************************************************************************************************************************/
void GenerateBoxes(LG *lcx);

/**************************************************************************
 * @brief Frees the memory allocated to a given BOX struct/element.       *
 * @param b : a pointer to a BOX struct/element. (Type void*)             *
 * @return None.                                                          *
 **************************************************************************/
void DestruirCaixa(void *b);

/****************************************************************************************************************************************
 * @brief Prints out the fields of a given Box struct/element.                                                                          *
 *                                                                                                                                      *
 *        It prints the box's number, status (open or closed), closing status (whether it is closing soon),                             *
 *        whether it has an assigned employee, the number of products offered by the box, and the total value of these products.        *
 *        If the box has an assigned employee and is open, it also prints details about the employee using the ShowEmployee function.   *
 *                                                                                                                                      *
 * @param b : a pointer to a BOX struct/element. (Type void*)                                                                           *
 * @see ShowEmployee()                                                                                                                  *
 * @return None.                                                                                                                        *
 ****************************************************************************************************************************************/
void ShowCaixa(void *b);

/****************************************************************************************************************************************
 * @brief Prints out the fields of a given Box struct/element, if the box is currently opened.                                          *
 *                                                                                                                                      *
 *        It prints the box's number, whether it has an assigned employee, the size of the queue waiting at the box,                    *
 *        and the number and total value of products offered by the box.                                                                *
 *        If the box has an assigned employee, it also prints details about the employee using the ShowEmployee function.               *
 *                                                                                                                                      *
 * @param b : a pointer to a BOX struct/element. (Type void*)                                                                           *
 * @see ShowEmployee()                                                                                                                  *
 * @return None.                                                                                                                        *
 ****************************************************************************************************************************************/
void ShowOpenCaixa(void *b);

/*********************************************************************************************************************************************************
 * @brief Assigns an Employee element pointed to by the E argument to a BOX element pointed to by the b argument.                                        *
 *                                                                                                                                                       *
 *        Stores the employee in the funcionario field of the box structure.                                                                             *
 *                                                                                                                                                       *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @param E : a pointer to a Employee struct/element. (Type void*).                                                                                      *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
void setEmployerTo(void *b, void *E);

/*********************************************************************************************************************************************************
 * @brief Gets the current value of the status field of a given Box struct/element.                                                                      *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @return Returns 1 if the box is open and 0 if it is closed. If the b argument is NULL, it returns -2.                                                 *
 *********************************************************************************************************************************************************/
int getStatus(void *b);

/*********************************************************************************************************************************************************
 * @brief Gets the current value of the in_service field of a given Box struct/element.                                                                  *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @return Returns 1 if the box is attending and 0 if it isn't. If the b argument is NULL, it returns -2.                                                *
 *********************************************************************************************************************************************************/
int getService(void *b);

/*********************************************************************************************************************************************************
 * @brief Sets the value of the in_service field of a given Box struct/elemen to 1.                                                                      *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
void setService(void *b, void* C);

/*********************************************************************************************************************************************************
 * @brief Sets the value of the in_service field of a given Box struct/elemen to 0.                                                                      *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
void unService(void *b);

/*********************************************************************************************************************************************************
 * @brief Gets the current value of the closing field of a given Box struct/element.                                                                     *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @return Returns 1 if the box is closing soon and 0 if it isn't. If the b argument is NULL, it returns -2.                                             *
 *********************************************************************************************************************************************************/
int getClosingStatus(void *b);

/*********************************************************************************************************************************************************
 * @brief Sets the value of the closing field of a given Box struct/element to 1.                                                                        *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
void setClosingStatus(void *b);

/*********************************************************************************************************************************************************
 * @brief Sets the value of the closing field of a given Box struct/element to 0.                                                                        *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
void unsetClosingStatus(void *b);

/*********************************************************************************************************************************************************
 * @brief Sets the value of the status field of a given Box struct/element to 1, and initializes its QUEUE field with a new empty linked list.           *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @see CriarLG()                                                                                                                                        *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
void openCaixa(void *b);

/*********************************************************************************************************************************************************
 * @brief Sets the value of the auxiliary field of a given Box struct/element to the client being attended at the moment.                                *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
void setAux(void *b, void *c);

/*********************************************************************************************************************************************************
 * @brief Sets the value of the funcionario field of a given Box struct/element pointing to a random employee.                                           *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @param lg : Linked List with the employees.                                                                                                           *
 * @see getRandomInt()                                                                                                                                   *
 * @see getByPos()                                                                                                                                       *
 * @see getStatusE()                                                                                                                                     *
 * @see setToWork()                                                                                                                                      *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
void setRandomEmployee(void *b, LG *lg);

/*********************************************************************************************************************************************************
 * @brief Adds the amount of money received as an argument to the argument b (BOX) received as argument as well, onto the cashBox field.                 *
 * @param b : a pointer to a BOX struct/element. (Type BOX*).                                                                                           *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
void addCash(BOX *b, double money);

/*********************************************************************************************************************************************************
 * @brief Instantly closes a box, updates its satus field to 0 and returns its queue.                                                                    *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @return Pointer to the queue of the box to be instantly closed, NULL if the give argument was NULL.                                                   *
 *********************************************************************************************************************************************************/
LG *InstantcloseCaixa(void *b);

/*********************************************************************************************************************************************************
 * @brief Closes a box and deletes/frees its queue. And updates the pointer QEUEU of the box to NULL.                                                    *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
void closeCaixa(void *b);

/*********************************************************************************************************************************************************
 * @brief Adds given Client to the give Box queue.                                                                                                       *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @param c : a pointer to a client struct/element. (Type void*).                                                                                        *
 * @see enQueue()                                                                                                                                        *
 * @return The result of the call to enQeueu() function or -2 if any of the arguments was NULL.                                                          *
 *********************************************************************************************************************************************************/
int AddToQueue(void *b, void *c);

/*********************************************************************************************************************************************************
 * @brief Gets the total number of products in the queue of the given Box struct/element.                                                                *
 * @param b : a pointer to a BOX struct/element. (Type void*).                                                                                           *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
int getTotalProducts(void *b);

/*********************************************************************************************************************************************************
 * @brief Adds the information of a offered product given as argument to the box respective fields.                                                      *
 * @param b : a pointer to a BOX struct/element. (Type BOX*).                                                                                            *
 * @param p : a pointer to a product struct/element. (Type void*).                                                                                       *
 * @see getPrice()                                                                                                                                       *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
void AddFreeProd(BOX *b, void *p);

#endif // CAIXA_H_INCLUDED
