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
 * CLients ADT structure and vars description                                                                                                               *
 * ID                      -> char Array/string of the ID of each client.                                                                                   *
 * name                    -> full name.                                                                                                                    *
 * working                 -> bit field variable. 0 = not in queue; 1 = in queue.                                                                           *
 ************************************************************************************************************************************************************/

typedef struct FUNCIONARIO
{
  int ID;
  char *name;
  // char cargo;
  unsigned int working : 1;
  // funcionario *next;
} Employee, *ptr_emp;

Employee *CriarEmployee(int _id, char *_name);
void DestruirEmployee(void *e);
void ShowEmployee(void *e);
void ShowEmployeeInSuper(void *e);
int compEmployee(void *x, void *y);
int SearchEmployee(void *e, void *_ID);
int getIdEmplyee(void *e);
int getStatusE(void *e);
void setToWork(void *e);
void setToRest(void *e);
// int PertenceClient(CLIENTE *c, void *X, int (*fcomp)(void *, void *));

#endif // FUNCIONARIOS_H_INCLUDED
