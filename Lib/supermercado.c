#include "Headers/supermercado.h"

extern void logging2(char *datafile, const char *funcname, char *info);
extern void logging(char *datafile, const char *funcname, char *info, time_t time);
extern char *logging_file;

SM *CriarSM(char *_name, LG *C, LG *E, LG *P, LG *CX, HASHING *hc, treeNode *r)
{
    if (!P || !C || !E || !CX || !_name || !hc || !r)
    {
        printf("error in pointers SM");
        return NULL;
    }
    SM *sm = (SM *)ec_malloc(sizeof(SM));
    if (!sm)
    {
        fatal("in CriarSM(), allocation for supermercado failed... ");
        return NULL;
    }
    sm->COMPANY = (char *)ec_malloc(strlen(_name) + 1);
    if (!sm->COMPANY)
    {
        fatal("in CriarSM(), allocation for name in supermercado failed... ");
        return NULL;
    }
    sm->clients = C;
    sm->employees = E;
    sm->produtos = P;
    sm->caixas = CX;
    sm->prodTree = r;
    sm->clientsHash = hc;
    sm->Population = 0;
    sm->open = 0;
    sm->served = 0;
    sm->totalWaitingTime = 0;
    logging2(logging_file, __FUNCTION__, "Supermkater structure created.");
    return sm;
}
void DestruirSM(SM *sm)
{
    if (!sm)
    {
        fatal("freeing memory for supermercado failed... ");
        return;
    }
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Freeing Supermarket dynamic allocated memory. ",time );
    DestruirLG(sm->insideSuper, DestruirClient, 0);
    DestruirHASHING(sm->clientsHash);
    DestruirLG(sm->clients, DestruirClient, 1);
    DestruirLG(sm->employees, DestruirEmployee, 1);
    DestructTree(sm->prodTree);
    DestruirLG(sm->produtos, DestruirProduct, 1);
    DestruirLG(sm->caixas, DestruirCaixa, 1);
    // function to clear hash and tree needed
    free(sm->COMPANY);
    free(sm);
    logging(logging_file, __FUNCTION__, "Supermarket Deleted.", time);
}

void ShowSM(SM *sm)
{
    if (!sm)
    {
        fatal("Showing for supermercado failed... ");
        return;
    }
    // Show cliente apenas os que estao dentro do supermercado
    beautify("[CLIENTS INSIDE SUPERMARKET]");
    printf("**NUMBER OF CLIENTS -> [%d] <=> POPULATION [%d]\n", sm->insideSuper->NEL, sm->Population);
    // ShowLG(sm->insideSuper, ShowClient);
    beautify("[EMPLOYEES WORKING]");
    ShowLG(sm->employees, ShowEmployeeInSuper);
    ShowLG(sm->caixas, ShowCaixa);
    printf("Population ->[%d]\n", sm->Population);
    printf("Open boxes ->[%d]\n", sm->open);
    // InOrder(sm->prodTree);
}

// CLOCK
void startClock(SM *sm)
{
    if (!sm)
    {
        fatal("Starting clock for supermercado failed... ");
        return;
    }
    StartRelogio(&sm->ROLEX, 500, "8:30:00");
    //StartRelogio(&sm->ROLEX, 2000, "8:30:00");
}

void *getClosed(LG *lcx)
{
    if (!lcx)
        return NULL;
    NODE *box_node = (NODE *)lcx->head;
    NODE *aux;
    void *selected;
    int count = 0;
    while (box_node)
    {
        aux = box_node->next;
        int status = getStatus(box_node->info);
        if (status == 0 && count == 0)
        {
            selected = box_node->info;
            count++;
        }
        box_node = aux;
    }
    return selected;
}
// Queeing functions
void checkQueuesSize(SM *sm)
{
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Checking Queue sizes on boxes",time);
    if (!sm)
        return;
    NODE *box_node = (NODE *)sm->caixas->head;
    NODE *aux;
    int count, total = 0, median = 0;
    int op = 0;
    while (box_node)
    {
        aux = box_node->next;
        int status = getStatus(box_node->info);
        if (status == 0)
        {
            box_node = aux;
        }
        else if (status == 1)
        {
            op++;
            BOX *B = (BOX *)box_node->info;
            if (queueSize(B->QUEUE) == 10)
                count++;
            if (queueSize(B->QUEUE) > 0)
                total += queueSize(B->QUEUE);
            printf("QUEUESIZE ->%d\n", queueSize(B->QUEUE));
            box_node = aux;
        }
    }
    printf("SMOPEN -> [%d]\n", sm->open);
    median = total / sm->open;
    time_t medianWaiting = sm->totalWaitingTime / (float)sm->served;
    printf("TOTAL -> [%d] MEDIAN -> [%d]\n", total, median);
    if (op == sm->caixas->NEL)
    {
        printf("MAX NUMBERS OF BOXES OPEN....\nCANNOT OPEN WHATS NOT THERE...\n");
        return;
    }
    else if ((median >= 4 || count == sm->open) && (op < sm->caixas->NEL))
    {
        logging(logging_file, __FUNCTION__, "Openning a new box", time);
        void *ptr = getClosed(sm->caixas);
        openCaixa(ptr);
        BOX *x = (BOX *)ptr;
        if (x->funcionario == NULL)
            setRandomEmployee(ptr, sm->employees);
        ShowCaixa(ptr);
        sm->open++;
        printf("NEW BOX OPENENED, TOO MANY CLIENTS INSTORE...\n");
        return;
    }
    else if (medianWaiting > 400)
    {
        logging(logging_file, __FUNCTION__, "Openning a new box", time);
        void *ptr = getClosed(sm->caixas);
        openCaixa(ptr);
        BOX *x = (BOX *)ptr;
        if (x->funcionario == NULL)
            setRandomEmployee(ptr, sm->employees);
        ShowCaixa(ptr);
        sm->open++;
        printf("NEW BOX OPENENED, TOO MANY CLIENTS INSTORE...\n");
        return;
    }
}

void *getLeastProductsInQueue(SM *sm)
{
    if (!sm)
        return NULL;
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Getting least products in queues.", time);

    NODE *box_node = (NODE *)sm->caixas->head;
    NODE *aux;
    void *ptr_selected_box = NULL;
    int temp = 1000;
    while (box_node)
    {
        aux = box_node->next;
        int status = getStatus(box_node->info);
        if (status == 0)
        {
            box_node = aux;
        }
        else if (status == 1)
        {
            int nTotalProducts = getTotalProducts(box_node->info); // total number of products in the queue
            if (nTotalProducts < temp)
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
    if (!sm || !C)
    {
        return;
    }
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Queueing Client.", time);

    NODE *box_node = (NODE *)sm->caixas->head;
    NODE *aux;
    void *ptr_selected_box = NULL;
    void *ptr_selected_box_aux = NULL;
    int nInQueue = 0;
    int minInQueue = MAX_SIZE;
    int allClosed = 1; // flag to check if all boxes are closed
    int count = 0;
    int i = 0;
    while (box_node)
    {
        if (i == sm->caixas->NEL) // why in the hell do i need this now !??? WTAF
            break;
        ShowCaixa(box_node->info);
        aux = box_node->next;
        int status = getStatus(box_node->info);
        int closingStatus = getClosingStatus(box_node->info);
        if (status == 0)
        {
            box_node = aux;
        }
        else if (status == 1 && closingStatus == 0)
        {
            allClosed = 0;
            BOX *B = (BOX *)box_node->info;
            nInQueue = queueSize(B->QUEUE);
            if (nInQueue == 0)
            {
                ptr_selected_box = box_node->info;
                break;
            }
            int nTotalProducts = getTotalProducts(box_node->info); // total number of products in the queue
            if (nInQueue == MAX_SIZE)
            {
                box_node = aux;
                count++;
            }
            else if (nInQueue < MAX_SIZE && (nInQueue < minInQueue || nTotalProducts < getTotalProducts(ptr_selected_box)))
            {
                minInQueue = nInQueue;
                ptr_selected_box = box_node->info;
                box_node = aux;
            }
            box_node = aux;
        }
        i++;
    }
    if (count == sm->open)
    {
        ptr_selected_box_aux = getLeastProductsInQueue(sm);
        if (AddToQueue(ptr_selected_box_aux, C) )
        {setInQeueu(C);
        setQueueEntranceTime(C, VerTimeRelogio(&sm->ROLEX));
        BOX *B = (BOX *)ptr_selected_box_aux;
        B->itemsInQueue += ((Client *)C)->numP;
        logging(logging_file, __FUNCTION__, "Client Queued", time);
        }
    }
    else if (ptr_selected_box)
    {
        BOX *B = (BOX *)ptr_selected_box;
        if (getClosingStatus(B) == 1)
        {
            queueing(sm, C);
            return;
        }
        if(AddToQueue(ptr_selected_box, C) )
        {setInQeueu(C);
        setQueueEntranceTime(C, VerTimeRelogio(&sm->ROLEX));
        B->itemsInQueue += ((Client *)C)->numP;
        logging(logging_file, __FUNCTION__, "Client Queued",time);}
    }
    else if (allClosed) // added condition to check if all boxes are closed
    {
        fatal(" All boxes are closed\n");
        return;
    }
}
// Open random number of Boxes
void simulateOpenBoxes(SM *sm)
{
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Opening random number of boxes.", time);
    LG *lb = sm->caixas;
    int size_ = lb->NEL;
    int NB;
    if (size_ == 3)
        NB = 1;
    else
        NB = getRandomInt(1, 3); // 3 porque e o numero minimo de caixas
    int count = 0;
    NODE *b = lb->head;
    LG *employees = sm->employees;
    while (b && count < NB)
    {
        void *ptr = b->info;
        if (getStatus(ptr) == 0)
        {
            openCaixa(ptr);
            setRandomEmployee(ptr, employees);
            count++;
        }
        b = b->next;
    }
    sm->open = NB;
}
// Select random client to enter supermarket;
void *simulateEntrance(SM *sm)
{
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Simulating Client entering the supermarket.", time);
    int entries = sm->clientsHash->NEL;
    int ni = getRandomInt(0, entries - 1);
    int nel = sm->clientsHash->DADOS[ni].Clientes->NEL;
    int pos;

    if (nel == 1)
    {
        pos = 0;
    }
    else
    {
        pos = getRandomInt(1, nel) - 1;
    }
    // pick a random client
    void *selected_ = getElementInFaixa_Pos(sm->clientsHash, ni, pos);
    if (!selected_)
        printf("NULL POINTER");
    else if (getFlagEntry(selected_) == 1)
    {
        return NULL;
    }
    setEntry(selected_);
    sm->Population++;
    return selected_;
}
void getItemsToBuy(void *c, treeNode *root)
{
    logging2(logging_file, __FUNCTION__, "Simulating random number of products to buy..");
    Client *C = (Client *)c;
    int randItems = getRandomInt(1, 10);
    for (int i = 0; i < randItems; i++)
    {
        treeNode *random = SelectRandomNode(root);
        void *p = random->Data;
        if (C->carrinho->head == NULL)
        {
            AddLGInicio(C->carrinho, p);
            C->totalCaixa += getProductTimeToBuy((Product *)p);
            C->totalCompra += getProductTimeToGet((Product *)p);
        }
        else
        {
            int res = PertenceLG(C->carrinho, &random->ID, SearchProduct);
            if (res == 0)
            {
                AddLGInicio(C->carrinho, p);
                takeFromWallet(C, ((Product *)p)->preco);
            }
            else
            {
                i--;
                continue;
            }
        }
        C->numP++;
    }
    printf("NUM OF PRODUCTS ADDED ->[%d]\n", C->numP);
}

void OpenSuperMarket(SM *sm)
{
    if (!sm)
        return;
    logging2(logging_file, __FUNCTION__, "Opening Supermarket");
    simulateOpenBoxes(sm);
    ShowLG(sm->caixas, ShowCaixa);
    sm->insideSuper = CriarLG();
    startClock(sm);
}
void traverseList_checkTimes(SM *sm, time_t time_passed)
{
    logging(logging_file, __FUNCTION__, "Transversing Clients inside Supermarket List",time_passed);
    if (!sm)
        return;
    LG *lg = sm->insideSuper;
    NODE *aux = lg->head;
    while (aux)
    {
        void *ptr = aux->info;
        ShowClient(ptr);
        time_t auxiliary_clock = time_passed - ((Client *)ptr)->entrance;
        printf("TIME PASSED: %d, VALUE IN FLAG %d, TIME TO GET PROD: %f]...\n ", auxiliary_clock, getFlaginQueue(ptr),   ((Client *)ptr)->totalCompra      );
        if (auxiliary_clock >= ((Client *)ptr)->totalCompra && getFlaginQueue(ptr) == 0)
        {
            queueing(sm, ptr);
            char *id = ((Client *)ptr)->ID;
            char str[100] = "Client entered queue: ";
            strcat(str, id);
            logging(logging_file, __FUNCTION__, str, time_passed);
            //logging(logging_file, __FUNCTION__, id);
            printf("ENTERED QUEUE\n");
        }
        aux = aux->next;
    }
}
void traverseQueueBox(SM *sm, time_t current_time)
{
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Traverse Queues",time);
    if (!sm)
        return;
    NODE *aux = sm->caixas->head;
    while (aux)
    {
        BOX *b = (BOX *)aux->info;
        if (getStatus((void *)b))
        {
            if (queueSize(b->QUEUE) > 0 && getService((void *)b) == 0)
            {
                void *ptr = deQueue(b->QUEUE);
                setService((void *)b, ptr);
                unqueued(ptr, current_time);
                //setAux(aux->info, ptr);
                printf("CLIENTE QUEUED\n");
            }
            else if (queueSize(b->QUEUE) == 0 && getClosingStatus((void *)b) == 1)
            {
                closeCaixa((void *)b);
                unsetClosingStatus((void *)b);
                /** < commenting the following code since i need to know which employee had the best performance and dont have time or patience to change the whole structure and functions logic. */
                // ShowEmployee(x);
                // setToRest((void *)x);
                unService((void *)b);
                sm->open--;
            }
        }
        aux = aux->next;
    }
}
void attend(SM *sm, time_t current_time)
{
    if (!sm)
        return;
    NODE *aux = sm->caixas->head;
    int count = 0;
    while (aux)
    {
        printf("ENTERING ATTEND\n");
        ShowCaixa(aux->info);
        BOX *b = (BOX *)aux->info;
        if (getStatus(b))
        {
            if (getService( (void *)b))
            {
                ShowOpenCaixa((void *)b);
                Client *ptr = (Client *)(b->auxiliary);
                if (b->auxiliary == NULL)
                {
                    //unService((void *)b);
                    printf("B AUXILIARY IS NULL >>>>>\n"); getchar();
                }
                if (b->auxiliary != NULL)
                {
                    //ShowClient(b->auxiliary);
                    time_t auxiliary_clock = current_time - ptr->waiting;
                    time_t timeinQueue = ptr->waiting - ptr->inqueue;
                    sm->totalWaitingTime += timeinQueue;
                    if (timeinQueue > 300) // time waiting to get out of the queue greater than 600seconds => 5 mins offers the highest price product
                    {
                        logging(logging_file, __FUNCTION__, "Offering a free product to a client", current_time);
                        void *free_product = getPricyProduct(ptr);
                        if (free_product)
                        {
                            AddFreeProd(b, free_product);
                            printf("\t FREE PRODUCT OFFERED....\n");
                        }
                    }
                    if (auxiliary_clock >= ptr->totalCaixa)
                    {
                        logging(logging_file, __FUNCTION__, "Serving a client",current_time);
                        printf("Client being served\n");
                        addCash(b, ptr->totalCash);
                        printf("CLIENTE SERVED\n");
                        b->totalProducts += ptr->carrinho->NEL;
                        unService((void *)b);
                        //ptr->inQueue=0;
                        char *id = getIdClient(ptr);
                        removeByID(sm->insideSuper, id);
                        b->served++;
                        sm->Population--;
                        sm->served++;
                    }
                }
            }
        }
        count++;
        aux = aux->next;
    }
}
void *getPricyProduct(Client *C)
{
    logging2(logging_file, __FUNCTION__, "Getting clients highest cost product to be offered. ");
    if (!C)
        return NULL;
    if (!C->carrinho)
    {
        printf("ERROR: Carrinho is empty");
        return NULL;
    }
    int price = 0;
    NODE *aux = C->carrinho->head;
    void *ptr = NULL;
    while (aux != NULL)
    {
        if (getPrice(aux->info) > price)
        {
            price = getPrice(aux->info);
            ptr = aux->info;
        }
        aux = aux->next;
    }
    C->totalCash -= price;
    return ptr;
}

void traverseBoxes(SM *sm)
{
    if (!sm)
    {
        return NULL;
    }
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Traversing Boxes to check if one needs to close", time);
    NODE *box_node = (NODE *)sm->caixas->head;
    NODE *aux;
    void *ptr_selected_box = NULL;
    int nInQueue = 0;
    int condition = 5;
    int flag = 0;
    while (box_node && !flag)
    {
        aux = box_node->next;
        int status = getStatus(box_node->info);
        if (status == 0)
        {
        }
        else if (status == 1)
        {
            BOX *B = (BOX *)box_node->info;
            nInQueue = queueSize(B->QUEUE);
            if (nInQueue < condition && sm->open > 2)
            {
                setClosingStatus((void *)B);
                flag = 1;
            }
        }
        box_node = aux;
    }
}

void traverseBoxesForInstantClose(SM *sm, char x)
{
    if (!sm)
    {
        return;
    }
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Closing a box instantly.", time);

    NODE *box_node = (NODE *)sm->caixas->head;
    NODE *aux;
    void *ptr_selected_box = NULL;
    while (box_node)
    {
        aux = box_node->next;
        BOX *B = (BOX *)box_node->info;
        if (B->numero == x)
            ptr_selected_box = box_node->info;
        if (ptr_selected_box)
        {
            int status = getStatus(box_node->info);
            if (status == 1)
            {
                caixaClose(sm, ptr_selected_box);
                return;
            }
            else if (status == 0)
            {
                printf("Box already closed....\n");
                return;
            }
        }
        box_node = aux;
    }
    return;
}
// make a function for get box biggerQueue
void *getBoxLesserQueue(SM *sm)
{
    if (!sm)
    {
        return NULL;
    }
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Getting Box with lesser queue size.",time);
    NODE *box_node = (NODE *)sm->caixas->head;
    NODE *aux;
    void *ptr_selected_box = NULL;
    int nInQueue = 0;
    int condition = 20;
    while (box_node)
    {
        aux = box_node->next;
        int status = getStatus(box_node->info);
        if (status == 1)
        {
            BOX *B = (BOX *)box_node->info;
            nInQueue = queueSize(B->QUEUE);
            if (nInQueue < condition)
            {
                ptr_selected_box = box_node->info;
            }
        }
        box_node = aux;
    }
    if (ptr_selected_box)
    {
        return ptr_selected_box;
    }
    return NULL;
}

void caixaClose(SM *sm, void *b)
{
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Closing a box.", time);
    if (!b)
        return;
    LG *q = InstantcloseCaixa(b);
    for (int i = 0; i < q->NEL; i++)
    {
        void *c = deQueue(q);
        void *aux = getBoxLesserQueue(sm);
        AddToQueue(aux, c);
        BOX *B = (BOX *)aux;
        B->itemsInQueue += ((Client *)c)->numP;
    }
    closeCaixa(b);
    sm->open--;
}

void run(SM *sm, int flag)
{
    int population = sm->Population;
    time_t fiveMinsClock = VerTimeRelogio(&sm->ROLEX);
    if (sm->Population < 100 && flag == 0)
    {
        logging(logging_file, __FUNCTION__, "Getting Random Client", fiveMinsClock);
        void *c = NULL;
        while (c == NULL)
        {
            c = simulateEntrance(sm);
            printf("POPULATION [%d]\n", population);
        }
        time_t _time = VerTimeRelogio(&sm->ROLEX);
        printf("\t\t\t\t TIME = %s", asctime(localtime(&_time)));
        setEntranceTime(c, _time);
        getItemsToBuy(c, sm->prodTree);
        SumTimes(c);
        AddLGInicio(sm->insideSuper, c);
    }
    if (flag == 1)
    {
        static int runned = 0;
        if (runned == 0)
            OpenPreviousClosedBox(sm);
        printf("##############################################################################################\n");
        ShowSM(sm);

        ClosingSuper(sm);
        runned++;

        ShowLG(sm->caixas, ShowCaixa);
        ShowLG(sm->insideSuper, ShowClient);
        printf("NEL IN LIST :%d]\n", sm->insideSuper->NEL);
        printf("POPULATION :%d]\n", sm->Population);
        //getchar();
        system("clear");

    }
    else
    {
        time_t auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
        traverseList_checkTimes(sm, auxiliary_clock);
        auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
        checkQueuesSize(sm);
        if (sm->open > 1 && (auxiliary_clock - fiveMinsClock >= 300) && sm->Population > 3)
        {
            changeQueues(sm);
        }
        traverseQueueBox(sm, auxiliary_clock);
        auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
        attend(sm, auxiliary_clock);
        traverseBoxes(sm);
        printf("ENTER TO CONTINUE: \n");
    }
}

void changeQueues(SM *sm)
{
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Changing queues.",time);
    if (!sm)
    {
        return;
    }
    NODE *cx = sm->caixas->head;
    NODE *selected = NULL;
    int nProd = 0;
    int nQueue = 0;
    while (cx != NULL)
    {
        BOX *B = (BOX *)cx->info;
        if (getStatus((void *)B))
            if (queueSize(B->QUEUE) > nQueue && getClosingStatus((void *)B) == 0)
            {
                nQueue = queueSize(B->QUEUE);
                selected = cx->info;
            }
        cx = cx->next;
    }
    if (selected)
    {
        ShowCaixa(selected);
        BOX *B = (BOX *)selected;
        if(queueSize(B->QUEUE == 1))
            return;
        void *cl = getTail(B->QUEUE);
        void *newBox;
        newBox = getBoxLesserQueue(sm);
        if (newBox)
        {
            ShowCaixa(newBox);
            AddToQueue(newBox, cl);
        }
    }
}

BOX *getServedMore(SM *sm)
{
    if (!sm)
    {
        return NULL;
    }
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Getting box that served more clients.",time);
    NODE *node_box = sm->caixas->head;
    BOX *served_more = NULL;
    int temp = 0;
    while (node_box)
    {
        BOX *b = (BOX *)node_box->info;
        if (b->served > temp)
        {
            served_more = b;
            temp = b->served;
            // ShowCaixa(node_box->info); getchar();
        }
        node_box = node_box->next;
    }
    return served_more;
}
Employee *getServedLess(SM *sm)
{
    if (!sm)
    {
        return NULL;
    }
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Getting client that served less clients.", time);
    NODE *node_box = sm->caixas->head;
    Employee *served_less = NULL;
    int temp = 1000;
    while (node_box)
    {
        BOX *b = (BOX *)node_box->info;
        if (b->served < temp && b->funcionario != NULL)
        {
            served_less = b->funcionario;
            temp = b->served;
            // ShowCaixa(node_box->info); getchar();
        }
        node_box = node_box->next;
    }
    return served_less;
}
BOX *getSoldMore(SM *sm)
{
    if (!sm)
    {
        return NULL;
    }
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Getting box that sold more products.",time);
    NODE *node_box = sm->caixas->head;
    BOX *sold_more = NULL;
    int temp = 0;
    while (node_box)
    {
        // printf("HERE?\n");
        BOX *b = (BOX *)node_box->info;
        if (b->totalProducts > temp)
        {
            sold_more = b;
            temp = b->totalProducts;
            // ShowCaixa(node_box->info); getchar();
        }
        node_box = node_box->next;
    }
    return sold_more;
}

void OpenPreviousClosedBox(SM *sm)
{
    if (!sm)
    {
        return;
    }
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Open boxes that got closed so its faster", time);
    NODE *aux = sm->caixas->head;
    while (aux)
    {
        BOX *b = (BOX *)aux->info;
        if (b->funcionario && getStatus(aux->info) == 0)
        {
            openCaixa((void *)b); //(printf("Opened one box\n")); getchar();
        }
        else if (getStatus(aux->info) && getClosingStatus(aux->info))
            unsetClosingStatus(aux->info);
        aux = aux->next;
    }
    return;
}

void ClosingSuper(SM *sm)
{

    time_t auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "Last functions to close super.", auxiliary_clock);
    printf("FINAAAAAAAAAAALLL 00000000000000\n");
    traverseList_checkTimes(sm, auxiliary_clock);
    printf("FINAAAAAAAAAAALLL 1111111111111111111111\n");
    auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
    if (sm->open > 1 && sm->Population > 3)
    {
        changeQueues(sm);
    }
    auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
    printf("FINAAAAAAAAAAALLL 2222222222222222\n");
    traverseQueueBox(sm, auxiliary_clock);
    auxiliary_clock = VerTimeRelogio(&sm->ROLEX);
    printf("FINAAAAAAAAAAALLL 3333333333333333333333\n");
    attend(sm, auxiliary_clock);
    printf("RUNNING SMOOTHLY\n");
}
