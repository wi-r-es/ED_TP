#ifndef LISTAGENERICA_H_INCLUDED
#define LISTAGENERICA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

//#include "clients.h"
#include "funcionarios.h"
#include "produto.h"
//#include "supermercado.h"

typedef struct NODE
{
    void *info;
    struct NODE *next;
    struct NODE *prev;

}NODE;

typedef struct
{
    int NEL;
    NODE *head;
    NODE *tail;
}ListaGenerica, LG;

ListaGenerica *CriarLG();
void DestruirLG(ListaGenerica *lg, void (*fdest)(void *));
void ShowLG(ListaGenerica *lg, void (*f)(void *));
void AddLGFim(ListaGenerica *lg, void *X); // add stack
void AddLGInicio(ListaGenerica *lg, void *X);
void* SearchLG(LG *lg, void *key, int (*fsearch)(void*, void*));
int PertenceLG(ListaGenerica *lg, void *X, int (*fcomp)(void *, void *));

#endif // LISTAGENERICA_H_INCLUDED
