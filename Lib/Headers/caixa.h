#ifndef CAIXA_H_INCLUDED
#define CAIXA_H_INCLUDED


#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
//#include "clients.h"
#include "funcionarios.h"
#include "listaGenerica.h"
#include "utils.h"

typedef struct CAIXA {
    unsigned int status : 1; //0 fechada | 1 aberta
    char numero;
    //short int num_clientes_fila;
    int num_produtos_oferecidos;
    double valor_produtos_oferecidos;
    LG *QUEUE;
    Employee *funcionario;
}BOX, *ptr_caixa;


BOX *CriarCaixa(char _id);
void GenerateBoxes(LG *lcx);
void DestruirCaixa(void *b);
void ShowCaixa(void *b);
void setEmployerTo(void *b, void *E);
int getStatus(void *b);
void openCaixa(void *b);
void setRandomEmployee(void *b, LG *lg);
void closeCaixa(void *b);
void closeCaixa_if_min_not_satisfied(void *b);
int AddToQueue(void *b, void *c);


void AddFreeProd(void *b,void *p);


#endif // CAIXA_H_INCLUDED
