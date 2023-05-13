#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaGenerica.h"
#include "clients.h"

// FOR TESTING
#include "IO.h"

/*
#define NUM_ENTRADAS 27 //Letras no alfabeto +1
*/
typedef struct
{
    char Faixa;
    ListaGenerica *Clientes;
} GROUP;
typedef struct
{
    // GROUP DADOS[NUM_ENTRADAS];
    GROUP *DADOS;
    int NEL;
} HASHING;

HASHING *CriarHASHING(char *str);
void DestruirHASHING(HASHING *H);
void ShowHASHING(HASHING *H);
void ShowFaixa(HASHING *H, int p);
int AddHASHING(HASHING *H, void *c);
int FuncaoHASHING(HASHING *H, void *c);
void LoadHashingFromLinkedList(HASHING *hash_table, LG *C);
void *getElementInFaixa_Pos(HASHING *hash_table, int f, int p);

#endif // HASHING_H_INCLUDED
