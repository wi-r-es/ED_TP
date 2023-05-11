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
    sm->open=0;

    return sm;
}
void DestruirSM(SM *sm)
{
     if(!sm)
    {
        fatal("freeing memory for supermercado failed... ");
        return;
    }
    DestruirLG(sm->insideSuper,DestruirClient, 0);
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
    printf("[CLIENTS INSIDE SUPERMARKET]>>>\n");
    printf("NUMBER OF CLIENTS -> [%d] <=> POPULATION [%d]\n", sm->insideSuper->NEL, sm->Population);
    //ShowLG(sm->insideSuper, ShowClient);
    printf("[EMPLOYEES WORKING ]>>>\n");
    ShowLG(sm->employees, ShowEmployeeInSuper);
    ShowLG(sm->caixas, ShowCaixa);
    printf("Population ->[%d]\n", sm->Population);
    printf("Open boxes ->[%d]\n", sm->open);
    //InOrder(sm->prodTree);

}

//CLOCK
void startClock(SM *sm)
{
     if(!sm)
    {
        fatal("Starting clock for supermercado failed... ");
        return;
    }

    //Relogio temp = sm->ROLEX;
    StartRelogio(&sm->ROLEX, 500, "8:30:00");
}

void *getClosed(LG *lcx)
{
    if(!lcx)
        return NULL;
    NODE *box_node = (NODE *) lcx->head;
    NODE *aux;
    void *selected;
    while (box_node)
    {
        aux= box_node->next;
        int status = getStatus(box_node->info);
        if (status == 0){
            selected = box_node->info;
            break;
        }
        box_node = aux;
    }
    return selected;
}
//Queeing functions
void checkQueuesSize(SM *sm)
{
    if(!sm)
        return;
    NODE *box_node = (NODE *) sm->caixas->head;
    NODE *aux;
    int count ,total=0 , median =0;
    int op=0;
    while (box_node)
    {
        aux= box_node->next;
        int status = getStatus(box_node->info);
        if (status == 0){
            box_node =aux;
        }
        else if (status==1)
        {
            op++;
            BOX *B = (BOX*) box_node->info;
            if (queueSize(B->QUEUE) == 10)
                count++;
            if ( queueSize(B->QUEUE) >0 )
                total += queueSize(B->QUEUE);
            printf( "QUEUESIZE ->%d\n", queueSize(B->QUEUE));
            box_node = aux;
        }

    }
    printf("SMOPEN -> [%d]\n", sm->open);
    median = total / sm->open;

    printf("TOTAL -> [%d] MEDIAN -> [%d]\n", total, median);
   // getchar();
    if( op == sm->caixas->NEL)
    {
        printf("MAX NUMBERS OF BOXES OPEN....\nCANNOT OPEN WHATS NOT THERE...\n");
    }
    else if((median >= 6 || count == sm->open) && (op < sm->caixas->NEL) )
    {

        void *ptr = getClosed(sm->caixas);
        openCaixa(ptr);
        ShowCaixa(ptr);
        setRandomEmployee(ptr, sm->employees);
        sm->open++;
        printf("NEW BOX OPENENED, TOO MANY CLIENTS INSTORE...\n");
       // getchar();
    }

}

void *getLeastProductsInQueue(SM *sm)
{
    NODE *box_node = (NODE *) sm->caixas->head;
    NODE *aux;
    void *ptr_selected_box = NULL;
    int temp=1000;
    while (box_node)
    {
        aux= box_node->next;
        int status = getStatus(box_node->info);
        if (status == 0){
            box_node =aux;
        }
        else if (status==1)
        {
            BOX *B = (BOX*) box_node->info;
            int nTotalProducts = getTotalProducts(box_node->info); // total number of products in the queue
            if (nTotalProducts < temp )  // )
            {
                ptr_selected_box = box_node->info;
            }
            box_node = aux;

        }
    }
    return ptr_selected_box;

}

void queueing(SM *sm, void *C)
{
    if (!sm || !C) {
        return;
    }
    //printf("QUEUEING 11111111\n");
    NODE *box_node = (NODE *) sm->caixas->head;
    NODE *aux;
    void *ptr_selected_box=NULL;
    void *ptr_selected_box_aux=NULL;
    int nInQueue=0;
    int minInQueue=MAX_SIZE;
    int allClosed = 1; // flag to check if all boxes are closed
    //printf("QUEUEING 22222\n");
    int count = 0;
    while (box_node)
    {
        //printf("QUEUEING 333333\n");
        //ShowCaixa(box_node->info);
        aux= box_node->next;
        int status = getStatus(box_node->info);
        if (status == 0){
            box_node =aux;
            //printf("QUEUEING 4444444444444444\n");

        }
        else if (status==1)
        {
            //printf("QUEUEING 5555555555555555555\n");
            allClosed = 0;
            BOX *B = (BOX*) box_node->info;
            nInQueue = queueSize(B->QUEUE);
            //printf("QUEUEEUEUEU SIZE [%d]\n,", nInQueue);
            /*
            if (nInQueue==0){
                ptr_selected_box = box_node->info;
                printf("QUEUEING 6666666666666666666666\n");

            } */
            int nTotalProducts = getTotalProducts(box_node->info); // total number of products in the queue

            if (nInQueue == MAX_SIZE){
               // box_node = aux;
                count++;
                //printf("QUEUEING 7777777777777777777777777\n");

            } //maybe change this to only check for num of products in the condition after the OR statement
            else if (nInQueue < MAX_SIZE && (nInQueue < minInQueue ||/* (nInQueue == minInQueue && */ nTotalProducts < getTotalProducts(ptr_selected_box)))  // )
            {
                //printf("QUEUEING 888888888888888888888\n");
                minInQueue = nInQueue;
                ptr_selected_box = box_node->info;
               // box_node = aux;
                //printf("QUEUEING 999999999999999999999999999999999\n");
            }
            // se nInQueue < MAX_SIZE && population/ncaixasaberta != 10 openNew..
            box_node = aux;

        }

    }
    if(count == sm->open)
    {
        void *B = getLeastProductsInQueue(sm);

    }
    else if (ptr_selected_box)
    {
        AddToQueue(ptr_selected_box, C);
        setQueueEntranceTime(C, VerTimeRelogio(&sm->ROLEX));
        BOX *B = (BOX *) ptr_selected_box;
        B->itemsInQueue += ((Client *)C)->numP;
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
    sm->open=NB;
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
    sm->Population++;
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
                 takeFromWallet(C, ((Product *)p)->preco);
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
        C->numP++;

        //printf("\nRES ->[%d] \n", res);
        //if ()
           // random = SelectRandomNode(root);



    }

    printf("NUM OF PRODUCTS ADDED ->[%d]\n", C->numP);

    //printf("\n DEBUG 11");


    //printf("\n##############\n\t Products Selected\n");
    //ShowLG(C->carrinho, ShowProduct);


    //printf("\n DEBUG 22");
}


void OpenSuperMarket(SM *sm)
{
    if(!sm)
        return;
    simulateOpenBoxes(sm);
    ShowLG(sm->caixas, ShowCaixa);
    sm->insideSuper = CriarLG();
    startClock(sm);

}
void trasverseList_checkTimes(SM *sm, time_t time_passed)
{

    if(!sm)
        return;
    LG *lg = sm->insideSuper;
    NODE *aux = lg->head;

    //printf("trasverseList_checkTimes RUUUUN0 \n");
    while (aux)
    {
        //printf("trasverseList_checkTimes 11111111111111111 \n");
        void *ptr = aux->info;

        time_t auxiliary_clock = time_passed - ((Client *)ptr)->entrance;
        //printf("trasverseList_checkTimes 222222222222222 \n");



        if (auxiliary_clock >= ((Client *)ptr)->totalCompra && getFlaginQueue(ptr)==0){
            queueing(sm, ptr);
            setInQeueu(ptr);
            printf("ENTERED QUEUE\n");}
       // printf("trasverseList_checkTimes 3333 \n");
        aux = aux->next;
    }
}
void trasverseQueueBox(SM *sm , time_t current_time)
{

    if(!sm)
        return;
    //printf("trasverseQueueBox 0000000000000\n");
    NODE *aux = sm->caixas->head;
    while (aux)
    {
        BOX *b = (BOX *)aux->info;
        //printf("trasverseQueueBox 111111111111111111\n");
        if( getStatus(b) ) {
           // printf("trasverseQueueBox 333333333333333333333\n");
            if(queueSize(b->QUEUE) > 0 && !getService((void*)b) )
            {
                //printf("trasverseQueueBox 4444444444444444444444444444\n");
                setService((void*)b);
                //printf("trasverseQueueBox 555555555555555555\n");
                void *ptr = deQueue(b->QUEUE);
                //printf("trasverseQueueBox 666666666666666\n");
                queued(ptr, current_time);
                //printf("trasverseQueueBox 777777777777777777777\n");
                setAux((void*)b, ptr);
                //printf("trasverseQueueBox 8888888888888888888888\n");
                printf("CLIENTE QUEUED\n");
            }
            //printf("trasverseQueueBox 999999999999999999999999999\n");

        }
        printf("trasverseQueueBox ##############################\n");

        aux = aux->next;
    }
}
void attend(SM *sm, time_t current_time)
{
    if(!sm)
        return;
    NODE *aux = sm->caixas->head;
    printf("[][][][][][][][][][][][][][][][][][][][][FUCNTION CALLED -> [%s][][][][][][][][][][][][][]\n", __FUNCTION__);
    while (aux)
    {
        BOX *b = (BOX *)aux->info;
        if( getStatus(b) ){

            if( getService(b) )
            {
                //printf("attend 11111111111111\n");
                Client *ptr =(Client *)b->auxiliary;
                time_t auxiliary_clock = current_time - ptr->waiting;
                time_t timeinQueue = ptr->inqueue - ptr->waiting;
                if (timeinQueue > 300) // time waiting to get out of the queue greater than 600seconds => 5 mins offers the highest price product
                {
                       // printf("error   11111111111\n");
                    void *free_product = getPricyProduct( ptr);
                    if(free_product)
                    {
                        AddFreeProd(b,free_product);
                        printf("\t FREE PRODUCT OFFERED....\n");
                    }
                }
                if (auxiliary_clock >= ptr->totalCaixa)
                {
                    //if (auxiliary_clock )
                    printf("Client being served\n");
                    addCash(b,  ptr->totalCash);
                    printf("CLIENTE SERVED\n");
                    //printf("TESTESTESTEST 11111111111\n");
                    printf("#####################################################\n");
                    printf("######CLIENT TO BE SERVED AND REMOVED FROM LIST######\n");
                    printf("#####################################################\n");
                    ShowClient(b->auxiliary);
                    unService(b);
                    //printf("TESTESTESTEST 222222222222\n");
                    b->auxiliary=NULL;
                    printf("#####################################################\n");
                    printf("##########SHOW CLIENTS IN LIST INSIDE SUPER##########\n");
                    printf("#####################################################\n");
                    ShowLG(sm->insideSuper, ShowClient);
                    //printf("TESTESTESTEST 333333333333333333\n");
                    char *id =  getIdClient(ptr);

                    removeByID(sm->insideSuper,id );
                    ShowCaixa(aux->info);
                    printf("#####################################################\n");
                    printf("##########SHOW CLIENTS IN LIST INSIDE SUPER##########\n");
                     printf("##########SHOW CLIENTS AFTER REMOVE#################\n");
                    printf("#####################################################\n");
                    ShowLG(sm->insideSuper, ShowClient);
                    //printf("TESTESTESTEST 33333333333333333
                    //printf("TESTESTESTEST 44444444444444444\n");
                    sm->Population--;
                    //rest of the code needed to implement missing
                }
                //printf("CLIENTE SERVED\n");
            }

        }

        aux = aux->next;
    }
}
void *getPricyProduct(Client *C)
{
    //printf("SUMSUSMSUMSUMSUM 0 \n");
    if (!C)
        return NULL;
   // printf("SUMSUSMSUMSUMSUM 02 \n");
    if (!C->carrinho)
    {
        printf("ERROR: Carrinho is empty");
        return NULL;
    }
     //printf("SUMSUSMSUMSUMSUM 03 \n");
    int price=0;
    NODE *aux = C->carrinho->head;
    void *ptr=NULL;
    while (aux!= NULL)
    {
        if(getPrice(aux->info) > price)
        {
            price = getPrice(aux->info);
            ptr = aux->info;
        }
        aux = aux->next;
    }
    C->totalCash -= price;
    return ptr;

}
void run(SM *sm)
{

    int population = sm->Population;
    printf("ALOALOALOALAO %d \n", population);
    //relogio create
  //  removeByID(sm->clients, "581612");
    //ShowLG(sm->clients);
   // return;

    if (sm->Population < 100)
    {
        //printf("RUUUUUUUUUUUN-GETRANDOMCLIENT 1111111\n");
        void *c= NULL;
        //printf("DEBUUUUUG RUUUUN0 \n");
        while (c==NULL){
            //printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
            c = simulateEntrance(sm);
           // printf("RUUUUUUUUUUUN-GETRANDOMCLIENT \n");

            printf("POPULATION [%d]\n", population);
             //getchar();
        }
        //Relogio aux = sm->ROLEX;
        time_t _time = VerTimeRelogio(&sm->ROLEX);
        //printf("RUUUUUUUUUUUN-GETRANDOMCLIENT 2222222222222\n");
        printf("\t\t\t\t TIME = %s", asctime(localtime(&_time)));
        setEntranceTime(c, _time);
        //clientRelogio(R);
        //printf("NEW DEBUG 0 \n");
       // printf("RUUUUUUUUUUUN-GETRANDOMITEEEEEMS 1111111\n");
        getItemsToBuy(c, sm->prodTree);
        //printf("RUUUUUUUUUUUN-GETRANDOMITEEEEEMS 2222222222\n");
        //printf("NEW NE DEVUG 0 \n");
        SumTimes(c);
        //printf("RUUUUUUUUUUUN-SUM 1111111\n");
        AddLGInicio(sm->insideSuper, c);
        //printf("RUUUUUUUUUUUN-ADDEDTOLIST 1111111\n");
        //printf("NEW NEW GASHT 0 \n");
        ShowClient(c);

    }
    //printf("RUUUUUUUUUUUN 000000000\n");
    //getchar();
    //printf("RUUUUUUUUUUUN 1111111\n");
    time_t auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
    //LG *clients = sm->insideSuper;
    //printf("RUUUUUUUUUUUN 2222222222\n");
    trasverseList_checkTimes(sm , auxiliary_clock);
    //printf("RUUUUUUUUUUUN 33333333333\n");
    auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
    //printf("RUUUUUUUUUUUN 44444444444444\n");
    checkQueuesSize(sm);
    trasverseQueueBox(sm,auxiliary_clock);
    printf("RUUUUUUUUUUUN 5555555555555\n");
    //function to client change queue


    //check num of clients in queue if < min and timepassed == 10 then closes box

    // CHECK THE QUEUE SIZE AND IF NINQUEUE IS > MAX  quando o número médio de clientes por fila ultrapassa um determinado valor;
    auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
    printf("RUUUUUUUUUUUN 666666666666666\n");

    attend(sm, auxiliary_clock);
    printf("RUUUUUUUUUUUN 77777777777777777777777777777\n");
    ShowSM(sm);
    printf("ENTER TO CONTINUE: \n");
    //ShowLG(sm->insideSuper, ShowClient);
   // getchar();

    //printf("POPULATION FULL\n");
}

