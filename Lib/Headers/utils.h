#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>

// Logging function

typedef struct
{
    time_t START;
    int VELOCIDADE;
    time_t Hora_Inicio;
} Relogio;

void StartRelogio(Relogio *R, int Vel, const char *H_Inicio);
time_t VerTimeRelogio(Relogio *R);
void Wait(int s);
void WaitSegundos(int s);

void logging(char *datafile, const char *funcname, char *info);
// A function to display an error message and then exit
void fatal(char *message);
// Error-check malloc
void *ec_malloc(unsigned int size);
// clock wait

// Devolve um numero aleatorio entre [min, max]
// Gera um numero aleatorio
int ger_rand(int min, int max); // not random enough
// new ger random since other was was bias
int getRandomInt(int min, int max);
void beautify(const char *str);

#endif // UTILS_H_INCLUDED
