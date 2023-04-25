#include "Headers/supermercado.h"

extern void *ec_malloc(unsigned int size);
extern int getRandomInt(int min, int max);

SM *CriarSM(char *_name, LG *C, LG *E, LG *P, LG *CX, HASHING *hc, treeNode *r)
{
    if( !P || !C || !E || !CX || !_name || !hc || !r ) { printf("error in pointers SM");return;}
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
    sm->prodTree = r;
    sm->clientsHash = hc;

    return sm;
}
void DestruirSM(SM *sm)
{
    DestruirLG(sm->clients, DestruirClient, 1);
    DestruirLG(sm->employees, DestruirEmployee,1 );
    DestruirLG(sm->produtos, DestruirProduct,1 );
    DestruirLG(sm->caixas, DestruirCaixa,1 );

    //function to clear hash and tree needed
    free(sm->COMPANY);
    free(sm);
}

void ShowSM(void *s)
{

}

//Queeing functions

void queueing(LG *cx, void *C)
{
    if (!cx) {
        return;
    }
    NODE *box_node = (BOX *) cx->head;
    NODE *aux;
    void *ptr_selected_box=NULL;
    int nInQueue, minInQueue=0;
    while (box_node)
    {
        aux= box_node->next;
        int status = getStatus(box_node->info);
        if (status == 0)
            box_node =aux;
        else if (status==1)
        {
            BOX *B = (BOX*) box_node->info;
            nInQueue = queueSize(B->QUEUE);
            if (nInQueue == MAX_SIZE)
                box_node = aux;
            else if (nInQueue < MAX_SIZE && nInQueue < minInQueue)
            {
                minInQueue = nInQueue;
                ptr_selected_box = box_node->info;
                box_node = aux;
            }
        }
    }
    if (ptr_selected_box)
    {
        AddToQueue(ptr_selected_box, C);
    }
}
//Select random client to enter supermarket;
void simulateEntrance(SM *sm)
{
    int entries = sm->clientsHash->NEL;
    int ni = getRandomInt(1,entries) - 1;
    int nel = sm->clientsHash->DADOS[ni].Clientes->NEL;
    int pos = getRandomInt(1, nel);
    //printf("%d]    ---    %d]", ni, pos);
    void *ptr=getElementInFaixa_Pos(sm->clientsHash, ni, pos);
    //Client *c= getElementInFaixa_Pos(sm->clientsHash, ni, pos);

    //ShowClient(client_ptr);
    //GETTING ERROR HERE BUT WHY??????
    //Client *c= (Client *) client_ptr;
    //printf("%d", c->ID);

}


