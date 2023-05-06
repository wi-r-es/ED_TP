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
    unsigned int in_service : 1;
    //short int num_clientes_fila;
    int itemsInQueue;
    int num_produtos_oferecidos;
    double cashBox;
    double valor_produtos_oferecidos;
    LG *QUEUE;
    void *auxiliary;
    Employee *funcionario;
}BOX, *ptr_caixa;


BOX *CriarCaixa(char _id);
void GenerateBoxes(LG *lcx);
void DestruirCaixa(void *b);
void ShowCaixa(void *b);
void setEmployerTo(void *b, void *E);
int getStatus(BOX *b);
int getService(BOX *b);
void setService(BOX *b);
void unService(BOX *b);
void openCaixa(void *b);
void setAux(void *b, void *c);
void setRandomEmployee(void *b, LG *lg);
void addCash(BOX *b, double money);
void closeCaixa(void *b);
void closeCaixa_if_min_not_satisfied(void *b);
int AddToQueue(void *b, void *c);
int getTotalProducts(void *b);


void AddFreeProd(BOX *b,void *p);


#endif // CAIXA_H_INCLUDED
