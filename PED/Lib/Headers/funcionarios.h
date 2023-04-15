#ifndef FUNCIONARIOS_H_INCLUDED
#define FUNCIONARIOS_H_INCLUDED

#include <stdlib.h>
#include <stdlib.h>
#include <string.h>


typedef struct FUNCIONARIO{
    int ID;
    char *name;
    //char cargo;
    unsigned int working :1 ;
  // funcionario *next;
} Employee, *ptr_emp;

Employee *CriarEmployee(int _id, char * _name);
void DestruirEmployee(void *e);
void ShowEmployee(void *e);
int compEmployee(void *x, void *y);
int SearchEmployee(void *e, void *_ID);
int getIdEmplyee(void *e);
//int PertenceClient(CLIENTE *c, void *X, int (*fcomp)(void *, void *));

#endif // FUNCIONARIOS_H_INCLUDED
