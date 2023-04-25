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

typedef struct SUPERMERCADO {
    char *COMPANY;
    LG *clients;
    LG *employees;
    LG *produtos;
    LG *caixas;
    treeNode *prodTree; //arvore de produtos
    HASHING *clientsHash;
}Supermercado, SM;

SM *CriarSM(char *_name, LG *C, LG *E, LG *P, LG *CX, HASHING *hc, treeNode *r);
void DestruirSM(SM *s);
void ShowSM(void *s);
void queueing(LG *cx, void *C); // for clients
void getItems(void *c);
//int compSM(void *x, void *y);

#endif // SUPERMERCADO_H_INCLUDED
