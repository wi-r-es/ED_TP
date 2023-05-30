#include "Headers/queue.h"

int isEmptyQueue(LG *lg)
{
    if (!lg)
        return -2;
    // returns 1 if not empty 0 if empty
    return (lg->head == NULL);
}

int queueSize(LG *lg)
{
    if (!lg)
        return -2;
    // returns 1 if not empty 0 if empty
    return lg->NEL;
}
// ENQUEUE || addLGFim
int enQueue(LG *lg, void *x) // Adicionar no fim | Useful for queue
{
    // logging(logging_file, __FUNCTION__, "Adding to tail-genericList");
    if (!lg || !x)
        return -2;
    AddLGFim(lg, x);
    return 1;
    // logging(logging_file, __FUNCTION__, "Adding successfull");
}
void *deQueue(LG *lg)
{
    if (!lg)
    {
        printf("NULL pointer given...");
        return NULL;
    }
    // NODE *aux = (NODE *) x;
    if (isEmptyQueue(lg))
    {
        printf("Error: Qeueu is empty");
        return NULL;
    }
    NODE *aux = lg->head;
    lg->head = lg->head->next;
    // If front becomes NULL, then change tail also as NULL
    if (lg->head == NULL)
        lg->tail = NULL;
    void *_el = aux->info;
    lg->NEL--;
    free(aux);
    return _el;
}

void *getTail(LG *lg)
{
    if (!lg)
    {
        printf("NULL pointer given...");
        return NULL;
    }
    if (isEmptyQueue(lg))
    {
        printf("Error: Qeueu is empty");
        return NULL;
    }
    NODE *aux = lg->tail;
    NODE *newtail = aux->prev;
    void *_el = aux->info;
    newtail->next=NULL;
    lg->tail=newtail;
    lg->NEL--;
    free(aux);
    return _el;
}
