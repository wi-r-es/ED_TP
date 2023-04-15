#ifndef SUPERMERCADO_H_INCLUDED
#define SUPERMERCADO_H_INCLUDED

#include "listaGenerica.h"
#include "produto.h"
#include "clients.h"
#include "funcionarios.h"
#include "caixa.h"
#include "IO.h"

#define INT_MAX 10

typedef struct SUPERMERCADO {
    char *COMPANY;
    LG *clients;
    LG *employees;
    LG *produtos;
    LG *caixas;
}Supermercado, SM;

SM *CriarSM(char *_name, LG *C, LG *E, LG *P, LG *CX);
void DestruirSM(SM *s);
void ShowSM(void *s);
//int compSM(void *x, void *y);

#endif // SUPERMERCADO_H_INCLUDED
