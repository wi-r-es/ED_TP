#ifndef CLIENTS_H_INCLUDED
#define CLIENTS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listaGenerica.h"
#include "produto.h"
#include "utils.h"

#include "IO.h"



typedef struct CLIENTE {
    char ID[7];
    //char ID[6+1];
    char *name;
    unsigned int inQueue :1 ;
    unsigned int paying : 1;
    unsigned int inSuper :1 ;
    LG *carrinho; // LISTA GENERICA
    int numP;
    int tempo_medio_espera;
    float totalCompra;
    float totalCaixa;
    double totalCash;
    time_t entrance; //time getting products
    time_t waiting; //time getting attended
    time_t inqueue; //time in queue

   // struct Client *next;
}CLIENTE, Client, *ptr_client;




Client *CriarClient(char *_id, char * _name);
void DestruirClient(void *c);
void ShowClient(void *c);
int compClient(void *x, void *y);
int SearchClient(void *c, char *_id);
int SearchClientByName(void *c, void *_name);
char *getIdClient(Client *c);
int getFlagEntry(void *c);
void setEntry(void *c);
void setDisentry(void *c);

void setInQeueu(void *c);
int getFlaginQueue(void *c);


void setEntranceTime(void *c, time_t time);
void ShowClientsInSuper(LG *lg);
void SumTimes(void *c);

void queued(void *c, time_t time);
void setQueueEntranceTime(void *C, time_t time);
time_t getQtime(void *c);
time_t getTime(void *c);
void takeFromWallet(Client *C, double amount);

void removeByID(LG *lg,  char *_id);

//void EntrarSuper(void *c);
//int PertenceClient(CLIENTE *c, void *X, int (*fcomp)(void *, void *));


#endif // CLIENTS_H_INCLUDED
