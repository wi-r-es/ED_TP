#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>

//Logging function

void logging(char *datafile, char *funcname, char *info);
// A function to display an error message and then exit
void fatal(char *message);
//Error-check malloc
void *ec_malloc(unsigned int size);
//clock wait
void wait ( int mlseconds );

void wait_segundos ( int seconds );

// Devolve um numero aleatorio entre [min, max]
// Gera um numero aleatorio
int ger_rand(int min, int max); //not random enough
//new ger random since other was was bias
int getRandomInt(int min, int max);


#endif // UTILS_H_INCLUDED
