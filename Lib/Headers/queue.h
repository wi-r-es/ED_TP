#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "listaGenerica.h"
#include "utils.h"
#define MAX_SIZE 10

int isEmptyQueue(LG *lg);
int queueSize(LG *lg);
int enQueue(LG *lg, void *x);
void *deQueue(LG *lg);


#endif // QUEUE_H_INCLUDED
