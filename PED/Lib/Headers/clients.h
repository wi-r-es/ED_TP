#ifndef CLIENTS_H_INCLUDED
#define CLIENTS_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "listaGenerica.h"
#include "produto.h"


typedef struct CLIENTE {
    int ID;
    //char ID[6+1];
    char *name;
    unsigned int inQueue :1 ;
    ListaGenerica *carrinho;
    int tempo_medio_espera;

   // struct Client *next;
}CLIENTE, Client, *ptr_client;




Client *CriarClient(int _id, char * _name);
void DestruirClient(void *c);
void ShowClient(void *c);
int compClient(void *x, void *y);
int SearchClient(void *c, void *_id);
int SearchClientByName(void *c, void *_name);
int getIdClient(void *c);

void EntrarSuper(void *c);
//int PertenceClient(CLIENTE *c, void *X, int (*fcomp)(void *, void *));


#endif // CLIENTS_H_INCLUDED
