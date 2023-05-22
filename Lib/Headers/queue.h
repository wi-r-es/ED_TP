/*******************************************************************************
 *  @file queue.h                                                              *
 *  @brief Function prototypes to manage box queues.                           *
 *                                                                             *
 *  This contains the prototypes for managig queues of the supermarket boxes.  *
 *                                                                             *
 *******************************************************************************/

#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
/* -- Includes -- */
/* libc includes. */
#include <stdio.h>
#include <stdlib.h>
/* listaGenerica header file */
#include "listaGenerica.h"
/* utils header file */
#include "utils.h"
#define MAX_SIZE 10

/*****************************************************************************************************
 * @brief Checks if a given queue is empty.                                                          *
 *                                                                                                   *
 * @param lg : Pointer to LL queue.                                                                  *
 * @return 1 if the queue is not empty and 0 if it is empty. If lg is a null pointer, it returns -2. *
 *****************************************************************************************************/
int isEmptyQueue(LG *lg);

/*****************************************************************************************************************
 * @brief Checks the size of a given queue.                                                                      *
 *                                                                                                               *
 * @param lg : Pointer to LL queue.                                                                              *
 * @return The value of lg->NEL, which represents the size of the queue. If lg is a null pointer, it returns -2. *
 *****************************************************************************************************************/
int queueSize(LG *lg);

/*************************************************************************************
 * @brief Adds the element x (client) to the given queue.                            *
 *                                                                                   *
 *        Since its the queue it will add the element to the end of the LL lg.       *
 *                                                                                   *
 * @param lg : Pointer to LL queue.( Type LG*)                                       *
 * @param x : Pointer to element to be added (client in this case). (Type void*)     *
 * @see AddLGFim()                                                                   *
 * @return 1 if the addition is successful. If lg is a null pointer, it returns -2   *
 *************************************************************************************/
int enQueue(LG *lg, void *x);

/*****************************************************************************************************************************************
 * @brief Pops an element from the queue.                                                                                                *
 *                                                                                                                                       *
 *        Removes and returns the element at the front of the LL lg,                                                                     *
 *        implementing a queue-like behavior.                                                                                            *
 *        It first checks if lg is a null pointer or if the queue is empty using the isEmptyQueue() function.                            *
 *        If the queue is not empty, it removes the element at the head of the LL, updates the head pointer,                             *
 *        and decrements the size (lg->NEL) of the LL(queue)                                                                             *
 *        It then frees the memory occupied by the node of the removed element and returns                                               *
 *        a pointer to the removed element info (_el which is the client ADT).                                                           *
 *        If lg is a null pointer or if the queue is empty, it prints an error message and returns NULL.                                 *
 *                                                                                                                                       *
 * @param lg : Pointer to LL queue.( Type LG*)                                                                                           *
 * @see isEmptyQueue()                                                                                                                   *
 * @return Pointer to the head of the queue that got deleted from the queue, or NULL if the lg was a NULL pointer or the queue is empty. *
 *****************************************************************************************************************************************/
void *deQueue(LG *lg);

#endif // QUEUE_H_INCLUDED
