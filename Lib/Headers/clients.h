/*******************************************************************************
 *  @file clients.h                                                            *
 *  @brief Function prototypes for the Client ADT.                             *
 *                                                                             *
 *  This contains the prototypes for the managing of clients elements          *
 *  Set and unset flags used during the simulation to keep track of status.    *
 *                                                                             *
 *******************************************************************************/

#ifndef CLIENTS_H_INCLUDED
#define CLIENTS_H_INCLUDED

/* -- Includes -- */
/* libc includes. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* listaGenerica header file */
#include "listaGenerica.h"
/* produto header file */
#include "produto.h"
/* utils header file */
#include "utils.h" /* for useful functions, and ec_malloc() used to check errors during allocation */
/* IO header file */
#include "IO.h" //used for texting

/************************************************************************************************************************************************************
 * CLient ADT structure and vars description                                                                                                                *
 * ID                      -> char Array/string of the ID of each client.                                                                                   *
 * name                    -> full name.                                                                                                                    *
 * inQueue                 -> bit field variable. 0 = not in queue; 1 = in queue.                                                                           *
 * paying                  -> bit field variable. 0 = not paying; 1 = paying.                                                                               *
 * inSuper                 -> bit field variable. 0 = not inside super; 1 = inside super.                                                                   *
 * carrinho                -> pointer of type LG ADT to store the products randomly picked once client is in super.                                         *
 * numP                    -> variable to store the number of products in carrinho.                                                                         *
 * totalCompra             -> variable that stores the total time it take to get all the products in carrinho.                                              *
 * totalCaixa              -> variable that stores the total time it takes to get all the products passed in box.                                           *
 * totalCash               -> variable that store the total sum of all the products price in carrinho.                                                      *
 * entrance                -> variable that stores the time at which the client entered supermarket.                                                        *
 * waiting                 -> variable that stores the time once the client begins being attended, this is, once it gets out of the queue into the box.     *
 * inqueue                 -> variable that stores the time of entrance into a queue of a box.                                                              *
 ************************************************************************************************************************************************************/
typedef struct CLIENTE
{
  char ID[7];
  char *name;
  unsigned int inQueue : 1;
  unsigned int paying : 1;
  unsigned int inSuper : 1;
  LG *carrinho; // LISTA GENERICA
  int numP;
  float totalCompra;
  float totalCaixa;
  double totalCash;
  time_t entrance; // time getting products
  time_t waiting;  // time getting attended
  time_t inqueue;  // time in queue
} CLIENTE, Client, *ptr_client;

/**********************************************************************************************************************************
 * @brief Creates a new instance of the Client struct/element, and initializes its fields with the given _id and _name arguments. *
 * @param _id :  a string representing the ID of the client.                                                                      *
 * @param _name : a string representing the name of the client.                                                                   *
 * @see ec_malloc()                                                                                                               *
 * @see fatal()                                                                                                                   *
 * @return A pointer to a newly created Client struct/element.                                                                    *
 **********************************************************************************************************************************/
Client *CriarClient(char *_id, char *_name);

/**************************************************************************
 * @brief Frees the memory allocated to a given Client struct/element.    *
 * @param c : a pointer to a client struct/element. (Type void*)          *
 * @return None.                                                          *
 **************************************************************************/
void DestruirClient(void *c);

/*************************************************************************
 * @brief Prints out the fields of a given Client struct/element.        *
 * @param c : a pointer to a client struct/element. (Type void*).        *
 * @return None.                                                         *
 *************************************************************************/
void ShowClient(void *c);

/*******************************************************************************
 * @brief Compares two given Client structs/elements based on their ID field.  *
 * @param x : a pointer to a client struct/element. (Type void*).              *
 * @param y : a pointer to a client struct/element. (Type void*).              *
 * @return 1 if the ID fields of the two structs are equal, 0 otherwise.       *
 *******************************************************************************/
int compClient(void *x, void *y);

/*******************************************************************************************
 * @brief Checks if a given Client struct has the same ID field as the given _id string.   *
 * @param c : a pointer to a client struct/element. (Type void*).                          *
 * @param _id : a string representing the ID to be searched.                               *
 * @return 1 if the ID field of the struct is equal to the given _id, 0 otherwise.         *
 *******************************************************************************************/
int SearchClient(void *c, char *_id);

/********************************************************************************************
 * @brief Checks if a given Client struct has the same name field as a given _name string.  *
 * @param c : a pointer to a client struct/element. (Type void*).                           *
 * @param _name : a string representing the name to be searched.                            *
 * @return 1 if the ID field of the struct is equal to the given _id, 0 otherwise.          *
 ********************************************************************************************/
int SearchClientByName(void *c, void *_name);

/*************************************************************************************************************
 * @brief Returns the ID field of a given Client struct/element.                                             *
 * @param c : a pointer to a client struct/element. (Type void*).                                            *
 * @return A string representing the ID field of the struct/element , or NULL if the input pointer is NULL.  *
 *************************************************************************************************************/
char *getIdClient(Client *c);

/*************************************************************************************************************************************
 * @brief Returns the value of the inSuper field of a given Client struct/element.                                                   *
 * @param c : a pointer to a client struct/element. (Type Client*).                                                                  *
 * @return An integer representing the value of the inSuper field of the struct. 1 if the client is inside the super, 0 otherwise.   *
 *************************************************************************************************************************************/
int getFlagEntry(void *c);

/*********************************************************************************************************************************************************
 * @brief Sets the value of the inSuper field of a given Client struct/element to 1, and initializes its carrinho field with a new empty linked list.    *
 * @param c : a pointer to a client struct/element. (Type void*).                                                                                        *
 * @see CriarLG()                                                                                                                                        *
 * @return None.                                                                                                                                         *
 *********************************************************************************************************************************************************/
void setEntry(void *c);

/**************************************************************************************************************************************************************
 * @brief Sets the value of the inSuper field of a given Client struct/element to 0.                                                                          *
 *                                                                                                                                                            *
 *        THIS FUNCTION WAS CREATED WITH THE PURPOSE TO BE USED. BUT AFTER CONTINUING WITH THE PROGRAM IT WASNT USED BECAUSE THE CLIENT ONLY ENTERS ONCE.     *
 *        THE CLIENT CANNOT RE-ENTER THE SUPERMARKET FOR THIS SIMULATION IN PARTICULAR.                                                                       *
 *                                                                                                                                                            *
 * @param c : a pointer to a client struct/element. (Type void*).                                                                                             *
 * @return None.                                                                                                                                              *
 **************************************************************************************************************************************************************/
void setDisentry(void *c);

/****************************************************************************************
 * @brief Sets the value of the inQueue field of a given Client struct/element to 1.    *
 * @param c : a pointer to a client struct/element. (Type void*).                       *
 * @return None.                                                                        *
 ****************************************************************************************/
void setInQeueu(void *c);

/*****************************************************************************************
 * @brief Returns the value of the inQueue field of a given Client struct/element.       *
 * @param c : a pointer to a client struct/element. (Type void*).                        *
 * @return The value of the inQueue field. 1 if the client is in a queue, 0 otherwise.   *
 *****************************************************************************************/
int getFlaginQueue(void *c);

/**********************************************************************************************************
 * @brief Sets the value of the entrance field of a given Client struct/element to the given time.        *
 * @param c : a pointer to a client struct/element. (Type void*).                                         *
 * @param time : the time the client entered the supermarket.                                             *
 * @return None.                                                                                          *
 **********************************************************************************************************/
void setEntranceTime(void *c, time_t time);

/**
 void ShowClientsInSuper(LG *lg);
 */


/************************************************************************************************************************************
 * @brief Adds the times of the products in the linked list carrinho of the client and saves each value in the respective variable. *
 *                                                                                                                                  *
 *        totalCaixa for the sum of the times the product takes to get "scanned" in box.                                            *
 *        totalCompra for the sum of the times the client takes to find/get the product.                                            *
 *                                                                                                                                  *
 * @param c : a pointer to a client struct/element. (Type void*).                                                                   *
 * @return None.                                                                                                                    *
 ************************************************************************************************************************************/
void SumTimes(void *c);

/***********************************************************************************************************************************
 * @brief Sets the value of the paying field of a given Client struct/element to 1 and sets the waiting field to the given time.   *
 * @param c : a pointer to a client struct/element. (Type void*).                                                                  *
 * @param time : the time the client got unqueued and start being attended by an employee.                                         *
 * @return None.                                                                                                                   *
 ***********************************************************************************************************************************/
void unqueued(void *c, time_t time);

/***************************************************************************************************
 * @brief Sets the value of the inqueue field of a given Client struct/element to the given time.  *
 * @param c : a pointer to a client struct/element. (Type void*).                                  *
 * @param time : the time the client entered a queue.                                              *
 * @return None.                                                                                   *
 ***************************************************************************************************/
void setQueueEntranceTime(void *C, time_t time);

/**********************************************************************************************
 * @brief Returns the value of the inqueue field of a given Client struct/element.            *
 * @param c : a pointer to a client struct/element. (Type void*).                             *
 * @return The value of the inQueue field. 1 if the client is in a queue, 0 otherwise.        *
 **********************************************************************************************/
time_t getQtime(void *c);

/*********************************************************************************************
 * @brief Returns the value of the entrance field of a given Client struct/element.          *
 * @param c : a pointer to a client struct/element. (Type void*).                            *
 * @return The value of the entrance field. -1 if the given pointer parameter was NULL.      *
 *********************************************************************************************/
time_t getTime(void *c);

/*********************************************************************************************************
 * @brief Adds the value of the given amount into the totalCompra field of the Client struct/element.    *
 * @param c : a pointer to a client struct/element. (Type Client*).                                      *
 * @param amount : the amount to add to the client. The price of the product in this case.               *
 * @return None.                                                                                         *
 *********************************************************************************************************/
void takeFromWallet(Client *C, double amount);

/***********************************************************************************************************************
 * @brief Removes the client with the given ID (_id) from a given linked list lg.                                      *
 *                                                                                                                     *
 *        In this case, used to remove the client from the linked list that stores the clients inside supermarket.     *
 *                                                                                                                     *
 * @param lg : Linked List (LL) to remove the client from.                                                             *
 * @param _id : string with the id value of te client to remove from the LL.                                           *
 * @return None.                                                                                                       *
 ***********************************************************************************************************************/
void removeByID(LG *lg, char *_id);

#endif // CLIENTS_H_INCLUDED
