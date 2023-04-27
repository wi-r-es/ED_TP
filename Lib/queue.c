#include "Headers/queue.h"



int isEmptyQueue(LG *lg)
{
    if(!lg)
        return -2;
    // returns 1 if not empty 0 if empty
    return (lg->head==NULL);
}

int queueSize(LG *lg)
{
    if(!lg)
        return -2;
    // returns 1 if not empty 0 if empty
    return lg->NEL;
}
//ENQUEUE || addLGFim
int enQueue(LG *lg, void *x) //Adicionar no fim | Useful for queue
{
    //logging(logging_file, __FUNCTION__, "Adding to tail-genericList");
    if (!lg)
        return -2;
    if (lg->NEL == MAX_SIZE)
    {
        printf("Queue is full... ");
        return 0; //BOX IS FULL
    }

    AddLGFim(lg,x);

    return 1;
    //logging(logging_file, __FUNCTION__, "Adding successfull");
}
void *deQueue(LG *lg)
{
    if (!lg)
    {
        printf("NULL pointer given...");
        return NULL;
    }
    //NODE *aux = (NODE *) x;
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
