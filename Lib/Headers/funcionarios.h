/*******************************************************************************
 *  @file funcionarios.h                                                       *
 *  @brief Function prototypes for the FUNCIONARIO/Employee ADT.               *
 *                                                                             *
 *  This contains the prototypes for the managing of Employees elements        *
 *  Set and unset flag used during the simulation to keep track of status.     *
 *                                                                             *
 *******************************************************************************/

#ifndef FUNCIONARIOS_H_INCLUDED
#define FUNCIONARIOS_H_INCLUDED

/* -- Includes -- */
/* libc includes. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* utils header file */
#include "utils.h" /* for useful functions, and ec_malloc() used to check errors during allocation */

/************************************************************************************************************************************************************
 * Employee ADT structure and vars description                                                                                                              *
 * ID                      -> char Array/string of the ID of each employee.                                                                                 *
 * name                    -> full name.                                                                                                                    *
 * working                 -> bit field variable. 0 = not in queue; 1 = in queue.                                                                           *
 ************************************************************************************************************************************************************/

typedef struct FUNCIONARIO
{
  int ID;
  char *name;
  // char cargo;
  unsigned int working : 1;
} Employee, *ptr_emp;


/************************************************************************************************************************************
 * @brief Creates a new instance of the Employee struct/element, and initializes its fields with the given _id and _name arguments. *
 * @param _id :  a string representing the ID of the Employee.                                                                      *
 * @param _name : a string representing the name of the Employee.                                                                   *
 * @see ec_malloc()                                                                                                                 *
 * @see fatal()                                                                                                                     *
 * @return A pointer to a newly created Client struct/element.                                                                      *
 ************************************************************************************************************************************/
Employee *CriarEmployee(int _id, char *_name);
/****************************************************************************
 * @brief Frees the memory allocated to a given Employee struct/element.    *
 * @param e : a pointer to a employee struct/element.(Type void*).          *
 * @return None.                                                            *
 ****************************************************************************/
void DestruirEmployee(void *e);

/*************************************************************************
 * @brief Prints out the fields of a given Employee struct/element.      *
 * @param e : a pointer to a employee struct/element.(Type void*).       *
 * @return None.                                                         *
 *************************************************************************/
void ShowEmployee(void *e);

/************************************************************************************************
 * @brief Prints out the fields of a given Employee struct/element, only if it is working.      *
 * @param e : a pointer to a employee struct/element.(Type void*).                              *
 * @return None.                                                                                *
 ************************************************************************************************/
void ShowEmployeeInSuper(void *e);

/*********************************************************************************
 * @brief Compares two given Employee structs/elements based on their ID field.  *
 * @param x : a pointer to a Employee struct/element. (Type void*).              *
 * @param y : a pointer to a Employee struct/element. (Type void*).              *
 * @return 1 if the ID fields of the two structs are equal, 0 otherwise.         *
 *********************************************************************************/
int compEmployee(void *x, void *y);

/**********************************************************************************************************************
 * @brief Checks if a given Employee struct has the same ID field as the given _id parameter passed as an argument.   *
 * @param e : a pointer to a Employee struct/element. (Type void*).                                                   *
 * @param _id : a void pointer pointing to the ID to be searched.                                                     *
 * @return 1 if the ID field of the struct is equal to the given _id, 0 otherwise.                                    *
 **********************************************************************************************************************/
int SearchEmployee(void *e, void *_id);

/**************************************************************************************************************
 * @brief Returns the ID field of a given Employee struct/element.                                            *
 * @param e : a pointer to a Employee struct/element. (Type void*).                                           *
 * @return A integer representing the ID field of the struct/element , or -1 if the input pointer is NULL.    *
 **************************************************************************************************************/
int getIdEmplyee(void *e);

/*************************************************************************************************************************************
 * @brief Returns the value of the working field of a given Employee struct/element.                                                 *
 * @param e : a pointer to a Employee struct/element. (Type void*).                                                                  *
 * @return An integer representing the value of the wroking field of the struct. 1 if the employee is wroking, 0 otherwise.          *
 *************************************************************************************************************************************/
int getStatusE(void *e);

/**************************************************************************************************************************************************************
 * @brief Sets the value of the working field of a given Employee struct/element to 1                                                                         *
 * @param e : a pointer to a Employee struct/element. (Type void*).                                                                                           *
 * @return None.                                                                                                                                              *
 **************************************************************************************************************************************************************/
void setToWork(void *e);

/**************************************************************************************************************************************************************
 * @brief Sets the value of the working field of a given Employee struct/element to 0                                                                         *
 * @param e : a pointer to a Employee struct/element. (Type void*).                                                                                           *
 * @return None.                                                                                                                                              *
 **************************************************************************************************************************************************************/
void setToRest(void *e);
// int PertenceClient(CLIENTE *c, void *X, int (*fcomp)(void *, void *));

#endif // FUNCIONARIOS_H_INCLUDED
