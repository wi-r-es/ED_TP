#ifndef SUPERMERCADO_H_INCLUDED
#define SUPERMERCADO_H_INCLUDED

#include "listaGenerica.h"
#include "produto.h"
#include "clients.h"
#include "funcionarios.h"
#include "caixa.h"
#include "IO.h"
#include "queue.h"
#include "hashing.h"
#include "binarytree.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TO lock random generator
#include <pthread.h>

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
} Supermercado, SM;

SM *CriarSM(char *_name, LG *C, LG *E, LG *P, LG *CX, HASHING *hc, treeNode *r);
void DestruirSM(SM *sm);
void ShowSM(SM *sm);
void startClock(SM *sm);
void *getLeastProductsInQueue(SM *sm);
void queueing(SM *sm, void *C); // for clients
void checkQueuesSize(SM *sm);
void *getClosed(LG *lcx);
void getItems(void *c);
// int compSM(void *x, void *y);
void trasverseList_checkTimes(SM *sm, time_t time_passed);
void trasverseQueueBox(SM *sm, time_t current_time);
void attend(SM *sm, time_t current_time);
void OpenSuperMarket(SM *sm);
void simulateOpenBoxes(SM *sm);
void *simulateEntrance(SM *sm);
void getItemsToBuy(void *c, treeNode *root);
void *getPricyProduct(Client *C);
void trasverseBoxes(SM *sm);
void *getBoxLesserQueue(SM *sm);
void caixaClose(SM *sm, void *b);
void run(SM *sm, int flag);

#endif // SUPERMERCADO_H_INCLUDED
