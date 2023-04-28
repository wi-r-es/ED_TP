#include "Headers/supermercado.h"

SM *CriarSM(char *_name, LG *C, LG *E, LG *P, LG *CX, HASHING *hc, treeNode *r)
{
    if( !P || !C || !E || !CX || !_name || !hc || !r ) { printf("error in pointers SM");return NULL;}
    SM *sm = (SM *)ec_malloc(sizeof(SM));
    if(!sm)
    {
        fatal("in CriarSM(), allocation for supermercado failed... ");
        return NULL;
    }

    sm->COMPANY = (char *)ec_malloc(strlen(_name) + 1); //(uintptr_t) add betwen malloc and cast if warning persists
    if(!sm->COMPANY)
    {
        fatal("in CriarSM(), allocation for name in supermercado failed... ");
        return NULL;
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
    DestruirHASHING(sm->clientsHash);
    DestructTree(sm->prodTree);


    //function to clear hash and tree needed
    free(sm->COMPANY);
    free(sm);
}

void ShowSM(SM *sm)
{
    //Show cliente apenas os que estao dentro do supermercado
    ShowLG(sm->clients, ShowClient);
    ShowLG(sm->employees, ShowEmployee);
    ShowLG(sm->caixas, ShowCaixa);
    InOrder(sm->prodTree);

}

//Queeing functions

void queueing(LG *cx, void *C)
{
    if (!cx) {
        return;
    }
    NODE *box_node = (NODE *) cx->head;
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
     printf("\nDEBUGG GER->111111111.....\n");
    int entries = sm->clientsHash->NEL;

    printf("\nDEBUGG GER->2222222.....\n");
    int ni = getRandomInt(0,entries-1) ;
    printf("\nDEBUGG GER->3333333.....\n");
    int nel = sm->clientsHash->DADOS[ni].Clientes->NEL;
    printf("\nDEBUGG GER->444444444.....\n");
    int pos;

    if (nel == 1)
    {
        pos = 0; return;
    }
    else{
            printf("\n\nNEEEEEEEL -> %d\n", nel);
        pos = getRandomInt(0, nel-1);}
    printf("\nDEBUGG GER->55555555555.....\n");
    //printf("NEL-> [%d] ", sm->clientsHash->DADOS[0].Clientes->NEL);
    //printf("%d]    ---    %d]/t [%d]", ni, pos, entries);
    printf("\n\tNUM OF KEYS --> [%d]\n", entries);
    printf("\n\tNUM OF KEYS selected --> [%d]\n", ni);
    printf("\n\tNUM OF elements --> [%d]\n", nel);
    void *selected_=getElementInFaixa_Pos(sm->clientsHash, ni, pos);
    //printf("Pointing to after return -> [%p]", selected_);
    //Client *c= getElementInFaixa_Pos(sm->clientsHash, ni, pos);
    printf("\nDEBUGG->111111111.....\n");
    if(!selected_)
        printf("NULL POINTER");
    printf("\nDEBUGG- on simulate function>1.....\n");
    printf("\nPointing to outside function -> [%p]", selected_);
    printf("\nDEBUGG- on simulate function>22222.....\n");

    ShowClient(selected_);

    //printf("DEGUB");
    //GETTING ERROR HERE BUT WHY??????
    //Client *c= (Client *) client_ptr;
    //printf("%d", c->ID);

}

void run(SM *sm)
{
    simulateEntrance(sm);
}
