#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaGenerica.h"
#include "clients.h"

/*
#define NUM_ENTRADAS 27 //Letras no alfabeto +1
*/
typedef struct
{
    char Faixa;
    ListaGenerica *Clientes;
}GROUP;
typedef struct
{
    //GROUP DADOS[NUM_ENTRADAS];
    GROUP *DADOS;
    int NEL;
}HASHING;


HASHING *CriarHASHING(char *str);
void DestruirHASHING(HASHING *H);
void ShowHASHING(HASHING *H);
int AddHASHING(HASHING *H, void *c);
int FuncaoHASHING(HASHING *H, void *c);
void LoadHashingFromLinkedList(HASHING *hash_table, LG *C);




#endif // HASHING_H_INCLUDED