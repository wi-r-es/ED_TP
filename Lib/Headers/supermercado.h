/**********************************************************************************
 *  @file supermercado.h                                                          *
 *  @brief Function prototypes for Supermarcado ADT                               *
 *                                                                                *
 *  This contains the prototypes for the managing of supermarket and its fields.  *
 *                                                                                *
 **********************************************************************************/

#ifndef SUPERMERCADO_H_INCLUDED
#define SUPERMERCADO_H_INCLUDED
/* -- Includes -- */
/* listaGenerica header file */
#include "listaGenerica.h"
/* produto header file */
#include "produto.h"
/* clients header file */
#include "clients.h"
/* funcionarios header file */
#include "funcionarios.h"
/* caixa header file */
#include "caixa.h"
/* IO header file */
#include "IO.h"
/* queue header file */
#include "queue.h"
/* hashing header file */
#include "hashing.h" /**< for quicker searches for clients */
/* binary header file */
#include "binarytree.h" /**< for quicker searches for products */
/* utils header file */
#include "utils.h"
/* libc includes. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************************************************************************************************************
 * SUPERMERCADO ADT structure and vars description                                                                                      *
 * COMPANY                   -> char Array/string representing the name of the company.                                                 *
 * clients                   -> Generic LL for all clients ("database").                                                                *
 * employees                 -> Generic LL for all employees ("database").                                                              *
 * produtos                  -> Generic LL for all products ("database").                                                               *
 * caixas                    -> Generic LL for all boxes ("database")                                                                   *
 * insideSuper               -> Generic LL for clients inside the supermarket. (constantly updated through the simulation.              *
 * prodTree                  -> AVL Binary tree to make the search for a certain product faster.                                        *
 * clientsHash               -> Clients hash table to make search for a client faster.                                                  *
 * Population                -> variable that stores the total number of clients inside the supermarket.                                *
 * open                      -> bit-field variable that represents if the store is open or closed.                                      *
 * ROLEX                     -> Clock variable that stores the time during the simulation, and make the simulation "run faster".        *
 * served                    -> Variable that stores the total Number of clients served/attended.                                       *
 ****************************************************************************************************************************************/
typedef struct SUPERMERCADO
{
    char *COMPANY;
    LG *clients;
    LG *employees;
    LG *produtos;
    LG *caixas;
    LG *insideSuper;
    treeNode *prodTree; // arvore de produtos
    HASHING *clientsHash;
    int Population;
    short int open;
    Relogio ROLEX;
    int served;
    time_t totalWaitingTime;
} Supermercado, SM;

/********************************************************************************************************
 * @brief Creates a new Supermarket                                                                     *
 *                                                                                                      *
 *        Creates a new Supermarket, using a name, a LL of clients, LL of employees, LL of products,    *
 *        LL of boxes, an hashing tables of the clients, and a binary tree of the products.             *
 *                                                                                                      *
 * @param _name : A pointer to a string representing the name of the supermarket.                       *
 * @param C : A pointer to a linked list LG representing the clients.                                   *
 * @param E : A pointer to a linked list LG representing the employees.                                 *
 * @param P : A pointer to a linked list LG representing the products.                                  *
 * @param CX : A pointer to a linked list LG representing the boxes (checkout boxes).                   *
 * @param hc :  A pointer to a HASHING structure representing the clients hash table.                   *
 * @param r : A pointer to the root of the products tree.                                               *
 * @see ec_malloc()                                                                                     *
 * @see fatal()                                                                                         *
 * @see logging()                                                                                       *
 * @return A pointer to a newly created SM structure, or NULL if the allocation failed.                 *
 ********************************************************************************************************/
SM *CriarSM(char *_name, LG *C, LG *E, LG *P, LG *CX, HASHING *hc, treeNode *r);

/***********************************************************************************************************************
 * @brief Destructs the supermarket, freeing all memory occupied by this structure.                                    *
 *                                                                                                                     *
 *        Calls all the needed functions to free every Linked List and the rest of the dynamically allocated memory.   *
 *                                                                                                                     *
 * @param sm : a pointer to the SM structure.                                                                          *
 * @see DestruirLG()                                                                                                   *
 * @see DestruirClient()                                                                                               *
 * @see DestruirEmployee()                                                                                             *
 * @see DestruirProduct()                                                                                              *
 * @see DestruirCaixa()                                                                                                *
 * @see DestruirHASHING()                                                                                              *
 * @see DestructTree()                                                                                                 *
 * @see fatal()                                                                                                        *
 * @see logging()                                                                                                      *
 * @return None.                                                                                                       *
 ***********************************************************************************************************************/
void DestruirSM(SM *sm);

/*************************************************************************
 * @brief Displays the information stored in the SM structure.           *
 * @param sm : a pointer to the SM structure.                            *
 * @see beautify()                                                       *
 * @see ShowLG()                                                         *
 * @see ShowEmployeeInSuper()                                            *
 * @see ShowCaixa()                                                      *
 * @return None.                                                         *
 *************************************************************************/
void ShowSM(SM *sm);

/***************************************************************************************************************
 * @brief Starts the clock for the supermarket by initializing the ROLEX member of the SM structure.           *
 * @param sm : a pointer to the SM structure.                                                                  *
 * @see StartRelogio()                                                                                         *
 * @return None.                                                                                               *
 ***************************************************************************************************************/
void startClock(SM *sm);

/**********************************************************************************************************************
 * @brief Finds the checkout box with the least number of products in its queue and returns a pointer to that box.    *
 * @param sm : a pointer to the SM structure.                                                                         *
 * @see getStatus()                                                                                                   *
 * @see getTotalProducts()                                                                                            *
 * @return Pointer to Box with least number of products in queue, NULL if null pointer was given as argument.         *
 **********************************************************************************************************************/
void *getLeastProductsInQueue(SM *sm);

/************************************************************************************************************************
 * @brief Handles the process of queuing a client C in one of the checkout boxes of the supermarket sm.                 *
 *                                                                                                                      *
 *        Checks which box has the better queue to put the client on. Based on queue size and total products in queue.  *
 *                                                                                                                      *
 * @param sm : a pointer to the SM structure.                                                                           *
 * @param C : a pointer to the client to be queued.                                                                     *
 * @see getStatus()                                                                                                     *
 * @see getClosingStatus()                                                                                              *
 * @see queueSize()                                                                                                     *
 * @see getTotalProducts()                                                                                              *
 * @see getLeastProductsInQueue()                                                                                       *
 * @see AddToQueue()                                                                                                    *
 * @see setQueueEntranceTime()                                                                                          *
 * @see VerTimeRelogio()                                                                                                *
 * @see fatal()                                                                                                         *
 * @return None.                                                                                                        *
 ************************************************************************************************************************/
void queueing(SM *sm, void *C); // for clients

/*********************************************************************************************************************************
 * @brief Checks the sizes of the queues in the checkout boxes of the supermarket. Opens a new one if it seems fit.              *
 *                                                                                                                               *
 *        Opens a new box if the queues have too many clients, and the median of clients per queue is greater or equeal          *
 *        to 4 OR all queues are full, AND if the number of boxes open is not the total number of boxes inside the supermarket.  *
 *                                                                                                                               *
 * @param sm : a pointer to the SM structure.                                                                                    *
 * @see logging()                                                                                                                *
 * @see getStatus()                                                                                                              *
 * @see queueSize()                                                                                                              *
 * @see getClosed()                                                                                                              *
 * @see openCaixa()                                                                                                              *
 * @see AddToQueue()                                                                                                             *
 * @see setRandomEmployee()                                                                                                      *
 * @see ShowCaixa()                                                                                                              *
 * @return None.                                                                                                                 *
 *********************************************************************************************************************************/
void checkQueuesSize(SM *sm);

/**********************************************************************************************************************************
 * @brief Searches for a closed checkout box in the given linked list lcx and returns a pointer to the first closed box found.    *
 * @param lcx : a pointer to boxes LL.                                                                                            *
 * @see getStatus()                                                                                                               *
 * @return Pointer to the first closed box encountered, NULL if null pointer was given as argument.                               *
 **********************************************************************************************************************************/
void *getClosed(LG *lcx);
//void getItems(void *c);
// int compSM(void *x, void *y);

/********************************************************************************************************************************************
 * @brief Traverses the list of clients inside the supermarket and checks wether or not the needed time as passed for them to be queued.    *
 *                                                                                                                                          *
 *        It calculates the time passed since each client entered the supermarket and checks if the time exceeds the client's total         *
 *        purchase time (auxiliary_clock >= ((Client *)ptr)->totalCompra). If the condition is met and the client is not already in         *
 *        the queue (getFlaginQueue(ptr) == 0), it queues the client using the queueing() function, sets the queue flag.                    *
 *                                                                                                                                          *
 * @param sm : a pointer to the SM structure.                                                                                               *
 * @param time_passed : "current" time in the simulation.                                                                                   *
 * @see logging()                                                                                                                           *
 * @see getFlaginQueue()                                                                                                                    *
 * @see queueing()                                                                                                                          *
 * @see setInQeueu()                                                                                                                        *
 * @return None.                                                                                                                            *
 ********************************************************************************************************************************************/
void traverseList_checkTimes(SM *sm, time_t time_passed);

/********************************************************************************************************************************************
 * @brief Traverses the list of boxes in the supermarket and performs actions based on the box's status and queue.                          *
 *                                                                                                                                          *
 *        If a box is open, it checks if there are clients in the queue and if the box is not currently serving a client.                   *
 *        If these conditions are met, it sets the box to serving status, dequeues a client from the box's queue, updates the client's      *
 *        unqueued time, and sets the box's auxiliary pointer to the dequeued client.                                                       *
 *        If the box has no clients in the queue and is flagged for closing, it closes the box, sets its status to closed,                  *
 *        sets the employee assigned to the box to rest, resets some variables, and decrements the count of open boxes in the supermarket.  *
 *                                                                                                                                          *
 * @param sm : a pointer to the SM structure.                                                                                               *
 * @param time_passed : "current" time in the simulation.                                                                                   *
 * @see logging()                                                                                                                           *
 * @see queueSize()                                                                                                                         *
 * @see getService()                                                                                                                        *
 * @see setService()                                                                                                                        *
 * @see deQueue()                                                                                                                           *
 * @see unqueued()                                                                                                                          *
 * @see setAux()                                                                                                                            *
 * @see getClosingStatus()                                                                                                                  *
 * @see closeCaixa()                                                                                                                        *
 * @see unsetClosingStatus()                                                                                                                *
 * @return None.                                                                                                                            *
 ********************************************************************************************************************************************/
void traverseQueueBox(SM *sm, time_t current_time);

/***********************************************************************************************************************************************************************************
 * @brief Simulates the process of attending clients at the cashier boxes.                                                                                                         *
 *                                                                                                                                                                                 *
 *        It iterates through each box and checks if it is open and has a client to be served.                                                                                     *
 *        If a client is being served, it calculates the time the client has spent in the queue and offers a free product if the waiting time exceeds 5 minutes.                   *
 *        If the auxiliary clock (current time - client's waiting time) is greater than or equal to the total time required to serve the client, the client is considered served.  *
 *        The cashier box is updated with the cash received from the client, the client is removed from the insideSuper list, and the box is marked as available.                  *
 *        The population and served counters are updated accordingly.                                                                                                              *
 *                                                                                                                                                                                 *
 * @param sm : a pointer to the SM structure.                                                                                                                                      *
 * @param current_time : The "current" time in the simulation.                                                                                                                     *
 * @see logging()                                                                                                                                                                  *
 * @see getStatus()                                                                                                                                                                *
 * @see getService()                                                                                                                                                               *
 * @see getPricyProduct()                                                                                                                                                          *
 * @see AddFreeProd()                                                                                                                                                              *
 * @see addCash()                                                                                                                                                                  *
 * @see unService()                                                                                                                                                                *
 * @see removeByID()                                                                                                                                                               *
 * @return None.                                                                                                                                                                   *
 ***********************************************************************************************************************************************************************************/
void attend(SM *sm, time_t current_time);

/***************************************************************************************************************
 * @brief Opens the supermarket.                                                                               *
 *                                                                                                             *
 *        Simulates opening the boxes using simulateOpenBoxes(),                                               *
 *        displays the opened boxes using ShowLG(),                                                            *
 *        creates an empty linked list for clients inside the supermarket and starts the supermarket clock.    *
 *                                                                                                             *
 * @param sm : a pointer to the SM structure.                                                                  *
 * @see logging()                                                                                              *
 * @see simulateOpenBoxes()                                                                                    *
 * @see ShowLG()                                                                                               *
 * @see CriarLG()                                                                                              *
 * @see startClock()                                                                                           *
 * @return None.                                                                                               *
 ***************************************************************************************************************/
void OpenSuperMarket(SM *sm);

/************************************************************************************************
 * @brief Opens a random number of boxes based on the number of boxes the supermarket has.      *
 *                                                                                              *
 * @param sm : a pointer to the SM structure.                                                   *
 * @see logging()                                                                               *
 * @see getRandomInt()                                                                          *
 * @see getStatus()                                                                             *
 * @see openCaixa()                                                                             *
 * @see setRandomEmployee()                                                                     *
 * @return None.                                                                                *
 ************************************************************************************************/
void simulateOpenBoxes(SM *sm);

/*************************************************************************************
 * @brief Simulates the entrance of a client into the supermarket.                   *
 *                                                                                   *
 *        Selects a random client index (ni) of the hash table and                   *
 *        a random position within that client's linked list of that index (pos).    *
 *        If the choosen client is already in the supermarket it returns NULL.       *
 *                                                                                   *
 * @param sm : a pointer to the SM structure.                                        *
 * @see logging()                                                                    *
 * @see getRandomInt()                                                               *
 * @see getElementInFaixa_Pos()                                                      *
 * @see getFlagEntry()                                                               *
 * @see setEntry()                                                                   *
 * @return None.                                                                     *
 *************************************************************************************/
void *simulateEntrance(SM *sm);

/**************************************************************************************************************************
 * @brief Selects and assigns random number of items for a client to purchase.                                            *
 *                                                                                                                        *
 *        Generates a random number (randItems) to determine the number of items the client will buy.                     *
 *        Then, it iterates randItems times and selects a random node from the binary search tree.                        *
 *        If the client's cart is empty, the selected product is added to the cart, and the client's                      *
 *        total purchase and total time variables are updated.                                                            *
 *        If the cart already contains the selected product, the loop iteration is decremented to repeat the selection.   *
 *                                                                                                                        *
 * @param c : a pointer to a client.                                                                                      *
 * @param root : a pointer to the root of the products binary tree.                                                       *
 * @see logging()                                                                                                         *
 * @see getRandomInt()                                                                                                    *
 * @see SelectRandomNode()                                                                                                *
 * @see AddLGInicio()                                                                                                     *
 * @see getProductTimeToBuy()                                                                                             *
 * @see getProductTimeToGet()                                                                                             *
 * @see PertenceLG()                                                                                                      *
 * @see takeFromWallet()                                                                                                  *
 * @return None.                                                                                                          *
 **************************************************************************************************************************/
void getItemsToBuy(void *c, treeNode *root);

/****************************************************************************************************************
 * @brief Retrieves the most expensive product from a client's shopping cart and returns it.                    *
 *                                                                                                              *
 *        It checks each item's price in the client's cart and compares it to find the highest-priced product.  *
 *        The function also subtracts the price of the selected product from the client's total cash.           *
 *                                                                                                              *
 * @param C : a pointer to a client.                                                                            *
 * @see logging()                                                                                               *
 * @see getPrice()                                                                                              *
 * @return The most expensive product in client's shopping cart, or NULL if C.carrinho or C are Null pointers.  *
 ****************************************************************************************************************/
void *getPricyProduct(Client *C);

/********************************************************************************************************
 * @brief Iterates through the boxes in the supermarket and checks if any of them need to be closed.    *
 *                                                                                                      *
 *        It examines the status of each box and the number of clients in its queue.                    *
 *        If the number of clients in the queue is less than a specified condition and                  *
 *        the supermarket has more than two open boxes, it sets the closing status for that box.        *
 *                                                                                                      *
 * @param sm : a pointer to the SM structure.                                                           *
 * @see logging()                                                                                       *
 * @see getStatus()                                                                                     *
 * @see queueSize()                                                                                     *
 * @see setClosingStatus()                                                                              *
 * @return None.                                                                                        *
 ********************************************************************************************************/
void traverseBoxes(SM *sm);

/*********************************************************************************************************************************
 * @brief Iterates through the boxes in the supermarket and returns the box with the smallest number of clients in its queue.    *
 *                                                                                                                               *
 *        It checks the status and queue size of each box and selects the one with the fewest clients.                           *
 *                                                                                                                               *
 * @param sm : a pointer to the SM structure.                                                                                    *
 * @see logging()                                                                                                                *
 * @see getStatus()                                                                                                              *
 * @see queueSize()                                                                                                              *
 * @return Pointer to bos with lesser queue size, NULL if sm was a null pointer.                                                 *
 *********************************************************************************************************************************/
void *getBoxLesserQueue(SM *sm);

/************************************************************************************************************************************
 * @brief Closes a given box.                                                                                                       *
 *                                                                                                                                  *
 *        It receives a box pointer (b) and closes it using the closeCaixa() function.                                              *
 *        It also transfers clients from the closed box's queue to the box with the fewest clients using the AddToQueue() function. *
 *        The number of items in the queue of the destination box is updated accordingly.                                           *
 *                                                                                                                                  *
 * @param sm : a pointer to the SM structure.                                                                                       *
 * @param b : a pointer to the box to be closed.                                                                                    *
 * @see logging()                                                                                                                   *
 * @see InstantcloseCaixa()                                                                                                         *
 * @see deQueue()                                                                                                                   *
 * @see getBoxLesserQueue()                                                                                                         *
 * @see AddToQueue()                                                                                                                *
 * @see closeCaixa()                                                                                                                *
 * @return None.                                                                                                                    *
 ************************************************************************************************************************************/
void caixaClose(SM *sm, void *b);

/************************************************************************************************************************************
 * @brief Main loop that simulates the operation of the supermarket.                                                                *
 *                                                                                                                                  *
 *       It runs until the specified flag is set.                                                                                   *
 *       Inside the loop, it performs various tasks such as simulating client entrance,                                             *
 *       updating times, checking queue sizes, attending clients, and closing boxes when necessary.                                 *
 *       The function terminates when the flag is set to 1 and all clients have been served and removed from the insideSuper list.  *
 *                                                                                                                                  *
 * @param sm : a pointer to the SM structure.                                                                                       *
 * @param flag : integer that represents if the supermarket is being closed or not.                                                 *
 * @see logging()                                                                                                                   *
 * @see simulateEntrance()                                                                                                          *
 * @see VerTimeRelogio()                                                                                                            *
 * @see setEntranceTime()                                                                                                           *
 * @see getItemsToBuy()                                                                                                             *
 * @see SumTimes()                                                                                                                  *
 * @see AddLGInicio()                                                                                                               *
 * @see ShowClient()                                                                                                                *
 * @see traverseList_checkTimes()                                                                                                   *
 * @see checkQueuesSize()                                                                                                           *
 * @see traverseQueueBox()                                                                                                          *
 * @see attend()                                                                                                                    *
 * @see traverseBoxes()                                                                                                             *
 * @see ShowSM()                                                                                                                    *
 * @return None.                                                                                                                    *
 ************************************************************************************************************************************/
void run(SM *sm, int flag);

/***********************************************************************************************************************
 * @brief Retrieves the box that has served the most clients in the supermarket simulation.                            *
 *                                                                                                                     *
 *        Traverse the boxes list and selects the one that served more clients.                                        *
 *                                                                                                                     *
 * @param sm : a pointer to the SM structure.                                                                          *
 * @see logging()                                                                                                      *
 * @return Pointer to box that served the most clients. NULL if given a null pointer as parameter or no boxes exist.   *
 ***********************************************************************************************************************/
BOX *getServedMore(SM *sm);

/****************************************************************************************************************************
 * @brief Retrieves the employee who served the fewest clients in the supermarket simulation.                               *
 *                                                                                                                          *
 *        Traverse the boxes list and selects the one that served less clients.                                             *
 *                                                                                                                          *
 * @param sm : a pointer to the SM structure.                                                                               *
 * @see logging()                                                                                                           *
 * @return Pointer to employee who served the fewest clients. NULL if given a null pointer as parameter or no boxes exist.  *
 ****************************************************************************************************************************/
Employee *getServedLess(SM *sm);

/***********************************************************************************************************************
 * @brief Retrieves the box that has sold the most products in the supermarket simulation.                             *
 *                                                                                                                     *
 *        Traverse the boxes list and selects the one that sold the most.                                              *
 *                                                                                                                     *
 * @param sm : a pointer to the SM structure.                                                                          *
 * @see logging()                                                                                                      *
 * @return Pointer to box that sold the most products. NULL if given a null pointer as parameter or no boxes exist.    *
 ***********************************************************************************************************************/
BOX *getSoldMore(SM *sm);

#endif // SUPERMERCADO_H_INCLUDED
