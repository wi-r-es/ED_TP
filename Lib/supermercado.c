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
    sm->Population =0;

    return sm;
}
void DestruirSM(SM *sm)
{
     if(!sm)
    {
        fatal("freeing memory for supermercado failed... ");
        return;
    }
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
     if(!sm)
    {
        fatal("Showing for supermercado failed... ");
        return;
    }
    //Show cliente apenas os que estao dentro do supermercado
    ShowLG(sm->clients, ShowClient);
    ShowLG(sm->employees, ShowEmployee);
    ShowLG(sm->caixas, ShowCaixa);
    InOrder(sm->prodTree);

}

//CLOCK
void startClock(SM *sm)
{
     if(!sm)
    {
        fatal("Starting clock for supermercado failed... ");
        return;
    }
    sm->insideSuper = CriarLG();
    //Relogio temp = sm->ROLEX;
    StartRelogio(&sm->ROLEX, 500, "8:30:00");
}


//Queeing functions

void queueing(LG *cx, void *C)
{
    if (!cx) {
        return;
    }
    printf("QUEUEING 11111111\n");
    NODE *box_node = (NODE *) cx->head;
    NODE *aux;
    void *ptr_selected_box=NULL;
    int nInQueue=0;
    int minInQueue=MAX_SIZE;
    int allClosed = 1; // flag to check if all boxes are closed
    printf("QUEUEING 22222\n");
    while (box_node)
    {
        printf("QUEUEING 333333\n");
        //ShowCaixa(box_node->info);
        aux= box_node->next;
        int status = getStatus(box_node->info);
        if (status == 0)
            box_node =aux;
        else if (status==1)
        {
            printf("QUEUEING 44444444\n");
            allClosed = 0;
            BOX *B = (BOX*) box_node->info;
            nInQueue = queueSize(B->QUEUE);
            printf("QUEUEEUEUEU SIZE [%d]\n,", nInQueue);
            if (nInQueue == MAX_SIZE)
                box_node = aux;
            else if (nInQueue < MAX_SIZE && nInQueue <= minInQueue)
            {
                printf("QUEUEING 555555\n");
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
    else if (allClosed) // added condition to check if all boxes are closed
    {
        fatal(" All boxes are closed\n");
        return;
    }
}

//Open random number of Boxes
void simulateOpenBoxes(SM *sm)
{
    LG *lb = sm->caixas;
    int size_ = lb->NEL;
    int NB;
    if (size_ == 3 )
        NB = 1;
    else NB = getRandomInt(1,3); // 3 porque e o numero minimo de caixas
    int count = 0;
    NODE *b = lb->head;
    LG *employees = sm->employees;
    while (b && count < NB)
    {
       void *ptr = b->info;
        if ( getStatus(ptr)==0 )
        {
            openCaixa(ptr);
            setRandomEmployee(ptr, employees);
            count++;
        }
        b = b->next;
    }
}
//Select random client to enter supermarket;
void *simulateEntrance(SM *sm)
{

    int entries = sm->clientsHash->NEL;

    //printf("\nDEBUGG GER->2222222.....\n");
    int ni = getRandomInt(0,entries-1) ;

    //printf("\nDEBUGG GER->3333333.....\n");
    int nel = sm->clientsHash->DADOS[ni].Clientes->NEL;

    //printf("\nDEBUGG GER->444444444.....\n");
    int pos;

    if (nel == 1)
    {
        pos = 0;
    }
    else
    {
        pos = getRandomInt(1, nel)-1;
    }
    //printf("\nDEBUGG GER->55555555555.....\n");

     //printf("\n\tNUM OF KEYS --> [%d]\n", entries);
    //printf("\n\tNUM OF KEYS selected --> [%d]\n", ni);
    //printf("\n\tNUM OF elements --> [%d]\n", nel);
    //printf("NEL-> [%d] ", sm->clientsHash->DADOS[0].Clientes->NEL);
    /*
    printf("%d]    ---    %d]/t [%d]\n", ni, pos, entries);
    printf("\n\tNUM OF KEYS --> [%d]\n", entries);
    printf("\n\tNUM OF KEYS selected --> [%d]\n", ni);
    printf("\n\tNUM OF elements --> [%d]\n", nel);
    */

    // pick a random client
    void *selected_=getElementInFaixa_Pos(sm->clientsHash, ni, pos);
    //printf("Pointing to after return -> [%p]", selected_);
    //Client *c= getElementInFaixa_Pos(sm->clientsHash, ni, pos);
    //printf("\nDEBUGG->111111111.....\n");
    if(!selected_)
        printf("NULL POINTER");
    else if( getFlagEntry(selected_)==1 )
    {
        return NULL;
    }
    //printf("\nDEBUGG- on simulate function>1.....\n");
    //printf("\nPointing to outside function -> [%p]", selected_);
    //printf("\nDEBUGG- on simulate function>22222.....\n");

    setEntry(selected_);
    //ShowClient(selected_);
    sm->Population+=1;
    //EntrarSuper(selected_);
    return selected_;
    //printf("DEGUB");
    //GETTING ERROR HERE BUT WHY??????
    //Client *c= (Client *) client_ptr;
    //printf("%d", c->ID);

}
void getItemsToBuy(void *c, treeNode *root)
{
    Client *C = (Client *)c;
    //printf("DEBUUUUUG 11 ");

    int randItems = getRandomInt(1,10);
    //printf("DEBUUUUUG 12 ");

    for(int i=0; i<randItems; i++)
    {
        //printf("DEBUUUUUG 21 ");
        treeNode *random= SelectRandomNode(root);
        void *p = random->Data;
        if(C->carrinho->head== NULL)
        {
            AddLGInicio(C->carrinho, p);
            C->totalCaixa += getProductTimeToBuy((Product *)p);
            C->totalCompra += getProductTimeToGet((Product *)p);
        //printf("DEBUUUUUG 23242 ");
        //ShowTreeNode(random);
        }
        else
        {
            //printf("DEBUUUUUG 22 \n");
            int res = PertenceLG(C->carrinho, &random->ID  ,SearchProduct);
            //printf("DEBUUUUUG 3 \n");
            printf("\n RES -> [%d]\n", res);
            if (res == 0)
            {
                //printf("DEBUUUUUGasffdafa2 \n");
                 AddLGInicio(C->carrinho, p);
                 //C->totalCaixa += ((Product *)p)->TCAIXA;
                //C->totalCompra += ((Product *)p)->TCOMPRA;
                 //printf("DEBUUUUUG 4 \n");
            }
            else
            {
                i--;
                //printf("DDSgfhdgjdts2 \n");
                continue;
            }
            //break;

        }

        //printf("\nRES ->[%d] \n", res);
        //if ()
           // random = SelectRandomNode(root);



    }

    //printf("\n DEBUG 11");


    //printf("\n##############\n\t Products Selected\n");
    //ShowLG(C->carrinho, ShowProduct);


    //printf("\n DEBUG 22");
}


void OpenSuperMarket(SM *sm)
{
    simulateOpenBoxes(sm);
    ShowLG(sm->caixas, ShowCaixa);
    startClock(sm);

}
void trasverseList_checkTimes(SM *sm , LG *lg, time_t time_passed)
{

    if(!lg)
        return;
    NODE *aux = lg->head;
    printf("DEBUUUUUG RUUUUN0 \n");
    while (aux)
    {
        printf("DEBUUUUUG 11111111111111111 \n");
        void *ptr = aux->info;
        time_t auxiliary_clock = time_passed - ((Client *)ptr)->entrance;
        printf("DEBUUUUUG 222222222222222 \n");
        if (auxiliary_clock >= ((Client *)ptr)->totalCompra){
            queueing(sm->caixas, ptr);
            printf("ENTERED QUEUE\n");}
        printf("DEBUUUUUG 3333 \n");
        aux = aux->next;
    }
}
void trasverseQueueBox(SM *sm , LG *lg, time_t current_time)
{

    if(!lg)
        return;
    NODE *aux = lg->head;
    while (aux)
    {
        BOX *b = (BOX *)aux->info;
        if( !getStatus(b) )
            break;
        else{

            if(queueSize(b->QUEUE) > 0 && !getService((void*)b) )
            {
                setService((void*)b);
                void *ptr = deQueue(b->QUEUE);
                queued(ptr, current_time);
                setAux((void*)b, ptr);
                printf("CLIENTE QUEUED\n");
            }

        }

        aux = aux->next;
    }
}
void attend(LG *lg, time_t current_time)
{
    if(!lg)
        return;
    NODE *aux = lg->head;
    while (aux)
    {
        BOX *b = (BOX *)aux->info;
        if( !getStatus(b) )
            break;
        else{

            if(getService((void*)b) )
            {
                setService((void*)b);
                void *ptr = b->auxiliary;
                time_t auxiliary_clock = current_time - ((Client *)ptr)->waiting;
                if (auxiliary_clock >= ((Client *)ptr)->totalCaixa){
                    printf("being served\n");
                    printf("CLIENTE SERVED\n");
                }
                //printf("CLIENTE SERVED\n");
            }

        }

        aux = aux->next;
    }
}
void run(SM *sm)
{

    int population = sm->Population;
    //printf("ALOALOALOALAO %d \n", population);
    //relogio create

    if (sm->Population < 100)
    {
        void *c= NULL;
        //printf("DEBUUUUUG RUUUUN0 \n");
        while (c==NULL){
            //printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
            c = simulateEntrance(sm);

             printf("POPULATION [%d]\n", population);
             //getchar();
        }
        //Relogio aux = sm->ROLEX;
        time_t _time = VerTimeRelogio(&sm->ROLEX);
        printf("\t\t\t\tTEST = %s", asctime(localtime(&_time)));
        setEntranceTime(c, _time);
        //clientRelogio(R);
        //printf("NEW DEBUG 0 \n");
        getItemsToBuy(c, sm->prodTree);
        //printf("NEW NE DEVUG 0 \n");
        SumTimes(c);
        AddLGInicio(sm->insideSuper, c);
        //printf("NEW NEW GASHT 0 \n");
        ShowClient(c);

    }
    time_t auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
    LG *clients = sm->insideSuper;
    trasverseList_checkTimes(sm , clients, auxiliary_clock);
    auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
    trasverseQueueBox(sm, sm->caixas,auxiliary_clock);
    auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
    attend(sm->caixas, auxiliary_clock);
    printf("ENTER TO CONTINUE: \n");
    //getchar();
    //printf("POPULATION FULL\n");










}

