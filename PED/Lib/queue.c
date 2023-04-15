#include "Headers/queue.h"

#define MAX_SIZE 10

extern void *ec_malloc(unsigned int size);


int isEmptyQueue(LG *lg)
{
    if(!lg)
        return;
    // returns 1 if not empty 0 if empty
    return (lg->head==NULL);
}

int queueSize(LG *lg)
{
    if(!lg)
        return;
    // returns 1 if not empty 0 if empty
    return lg->NEL;
}
//ENQUEUE || addLGFim
int enQueue(LG *lg, void *x) //Adicionar no fim | Useful for queue
{
    //logging(logging_file, __FUNCTION__, "Adding to tail-genericList");
    if (!lg || !x)
        return;
    if (lg->NEL == MAX_SIZE)
    {
        printf("Queue is full... ");
        return 0; //BOX IS FULL
    }
    NODE *aux = (NODE *)ec_malloc(sizeof(NODE));
    if (!aux)
        return -1; // Erro de alocacao de memoria
    aux->info = x;
    aux->next = NULL;
    if (!lg->head)
        lg->head=aux;
    else
    {
        NODE *iterator = lg->head;
        while (iterator->next)
            iterator = iterator->next;
        iterator->next = aux;
        lg->tail = aux;
    }
    lg->NEL++;
    return 1;
    //logging(logging_file, __FUNCTION__, "Adding successfull");
}
void *deQueue(LG *lg)
{
    if (!lg) return;
    //NODE *aux = (NODE *) x;
    if (isEmptyQueue(lg))
    {
        printf("Error: Qeueu is empty");
        return;
    }

    NODE *aux = lg->head;

    lg->head = lg->head->next;

    // If front becomes NULL, then change rear also as NULL
    if (lg->head == NULL)
        lg->tail = NULL;

    void *c = aux->info;
    lg->NEL--;
    free(aux);
    return c;
}


//LATER
/*
void changeQueue(Client *client, Queue *currentQueue, Queue *newQueue) {
    if (currentQueue == newQueue) {
        return;
    }

    removeNode(currentQueue, client);
    Enqueue(newQueue, client);
    client->queue = newQueue;
}



void closeCaixa(void *b) {
    if (!b) {
        return;
    }
    BOX *B = (BOX *) b;

    B->status = 0;

    // If there are clients in queue, disperse them to other boxes
    while (B->queue->size > 0) {
        // Get next client from queue
        void *client = Dequeue(B->queue);

        // Find another box with the smallest queue size
        int min_size = INT_MAX;
        BOX *target_box = NULL;
        for (int i = 0; i < num_boxes; i++) {
            BOX *other_box = boxes[i];
            if (other_box->status == 1 && other_box != B && other_box->queue->size < min_size) {
                min_size = other_box->queue->size;
                target_box = other_box;
            }
        }

        // Enqueue client into target box's queue
        if (target_box != NULL) {
            Enqueue(target_box->queue, client);
        } else {
            // If there are no other open boxes, just free the client
            free(client);
        }
    }
}

void removeNode(Queue *q, Client *client) {
    Node *prev = NULL;
    Node *curr = q->front;

    while (curr != NULL && curr->data != client) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return;
    }

    if (prev == NULL) {
        q->front = curr->next;
    } else {
        prev->next = curr->next;
    }

    if (q->rear == curr) {
        q->rear = prev;
    }

    q->size--;
    free(curr);
}





*/
