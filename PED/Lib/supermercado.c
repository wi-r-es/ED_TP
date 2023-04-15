#include "Headers/supermercado.h"

extern void *ec_malloc(unsigned int size);

SM *CriarSM(char *_name, LG *C, LG *E, LG *P, LG *CX)
{
    if( !P || !C || !E || !CX || !_name) { printf("error in pointers SM");return;}
    SM *sm = (SM *)ec_malloc(sizeof(SM));
    if(!sm)
    {
        fatal("in CriarSM(), allocation for supermercado failed... ");
        return;
    }

    sm->COMPANY = (char *)ec_malloc(strlen(_name) + 1);
    if(!sm->COMPANY)
    {
        fatal("in CriarSM(), allocation for name in supermercado failed... ");
        return;
    }
    sm->clients=C;
    sm->employees=E;
    sm->produtos=P;
    sm->caixas=CX;

    return sm;
}
void DestruirSM(SM *sm)
{
    DestruirLG(sm->clients, DestruirClient);
    DestruirLG(sm->employees, DestruirEmployee);
    DestruirLG(sm->produtos, DestruirProduct);
    DestruirLG(sm->caixas, DestruirCaixa);
    free(sm->COMPANY);
    free(sm);
}

void ShowSM(void *s)
{

}

//Queeing functions

void queueing(void *cx, int NUM_BOXES)
{
    if (!cx) {
        return;
    }
    ///check from here
    /*
    BOX *B = (BOX*) cx;
    LG *q = B->QUEUE;
    if (!q) {
        return;
    }
    BOX *selectedBox = NULL;
    int minQueueSize = INT_MAX;
    for (int i = 0; i < NUM_BOXES; i++) {
        BOX *B = &boxes[i];
        if (B->status == 1) {
            LG *q = B->QUEUE;
            int queueSize = QueueSize(q);
            if (queueSize < minQueueSize) {
                minQueueSize = queueSize;
                selectedBox = B;
            }
        }
    }
    if (selectedBox) {
        AddToQueue(selectedBox, C);
    }
    */
}
