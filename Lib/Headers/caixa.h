#ifndef CAIXA_H_INCLUDED
#define CAIXA_H_INCLUDED

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
// #include "clients.h"
#include "funcionarios.h"
#include "listaGenerica.h"
#include "utils.h"

typedef struct CAIXA
{
    unsigned int status : 1; // 0 fechada | 1 aberta
    char numero;
    unsigned int in_service : 1;
    unsigned int closing : 1;
    // short int num_clientes_fila;
    int itemsInQueue;
    int num_produtos_oferecidos;
    double cashBox;
    double valor_produtos_oferecidos;
    LG *QUEUE;
    void *auxiliary;
    Employee *funcionario;
} BOX, *ptr_caixa;

BOX *CriarCaixa(char _id);
void GenerateBoxes(LG *lcx);
void DestruirCaixa(void *b);
void ShowCaixa(void *b);
void ShowOpenCaixa(void *b);
void setEmployerTo(void *b, void *E);
int getStatus(void *b);
int getService(void *b);
void setService(void *b);
void unService(void *b);
int getClosingStatus(void *b);
void setClosingStatus(void *b);
void unsetClosingStatus(void *b);
void openCaixa(void *b);
void setAux(void *b, void *c);
void setRandomEmployee(void *b, LG *lg);
void addCash(BOX *b, double money);
LG *InstantcloseCaixa(void *b);
void closeCaixa(void *b);
int AddToQueue(void *b, void *c);
int getTotalProducts(void *b);

void AddFreeProd(BOX *b, void *p);

#endif // CAIXA_H_INCLUDED
