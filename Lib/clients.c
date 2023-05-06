#include "Headers/clients.h"


extern void *ec_malloc(unsigned int size);
int getRandomInt(int min, int max);
extern void logging(char* datafile, const char *funcname, char *info);
extern char *logging_file;

Client *CriarClient(int _id, char * _name)
{
    //logging(logging_file, __FUNCTION__, "Creating client-element");
    Client *C = (Client *) ec_malloc(sizeof(Client));
    //Client *C = (Client *)malloc(sizeof(Client));
    if(!C)
    {
        fatal("in CriarClient(), allocation for client failed... ");
        return NULL;
    }

    C->ID = _id;
    C->name = (char *)ec_malloc(strlen(_name) + 1);

    if(!C->name)
    {
        fatal("in CriarClient(), allocation for name in client failed... ");
        return NULL;
    }

    strcpy(C->name, _name);
    //printf("NM-> %s", C->name);
    C->inQueue=0;
    C->inSuper=0;
    C->carrinho=NULL;
    C->tempo_medio_espera=0;
    C->numP=0;
    C->totalCaixa=0;
    C->totalCompra=0;
    C->totalCash=0;
    C->entrance=0;
    C->waiting=0;
    C->inqueue=0;
    //logging(logging_file, __FUNCTION__, "Client created");
    return C;
}
void DestruirClient(void *c)
{
    //logging(logging_file, __FUNCTION__, "Deleting client");
    CLIENTE *C = (CLIENTE *)c;
    free(C->name);
    free(C);
    //logging(logging_file, __FUNCTION__, "Client Deleted");
}
void ShowClient(void *c)
{
    //printf("DEGUB0");
    CLIENTE *C = (CLIENTE *)c;
    //printf("DEGUB1");
    printf("\n     [*]<%s>[*]\n", __FUNCTION__);
    //printf("DEGUB2");
    printf("\t[ ]CODIGO ID: [%d]\n\t[ ]NOME: [%s]\n", C->ID, C->name);
    //writeTesting("testingHash.txt", __FUNCTION__, C->name);
    //printf("DEGUB3");
    printf("\t[ ]INQUEUE: [%d]\n\t[ ]INSUPER: [%d]\n", C->inQueue, C->inSuper);
    time_t aux = C->entrance;
    //if(aux)
        printf("\t\t[$]TIME OF ENTRANCE: [%s]\n", asctime(localtime(&aux)));
    //printf("DEGUB4");
}
int compClient(void *x, void *y)
{
    CLIENTE *px = (CLIENTE *)x;
    CLIENTE *py = (CLIENTE *)y;
    if (px->ID == py->ID)
        return 1;
    return 0;

}

int SearchClient(void *c, int _id)
{
    CLIENTE *C = (CLIENTE *)c;
    int key = C->ID;
    if (key == _id){
        return 1;
    }
    return 0;
}

int SearchClientByName(void *c, void *_name)
{
    CLIENTE *C = (CLIENTE *)c;
    char *ptr_name = (char *)_name;
    char *key = C->name;
    if (strcmp(key, ptr_name)){
        return 1;
    }
    return 0;
}
int getIdClient(Client *c)
{
    if(!c) return 0;
    return c->ID;
}
int getFlagEntry(void *c)
{
    CLIENTE *C = (CLIENTE *)c;
    return C->inSuper;
}
//void gerProdutos()
void setEntry(void *c)
{
    if(!c)
        return;
    CLIENTE *C = (CLIENTE *)c;
    C->inSuper=1;
    C->carrinho = CriarLG();
}
void queued(void *c, time_t time)
{
    if(!c)
        return;
    CLIENTE *C = (CLIENTE *)c;
    C->inQueue=1;
    C->waiting=time;
}
void setQueueEntranceTime(void *c, time_t time)
{
    if(!c)
        return;
    CLIENTE *C = (CLIENTE *)c;
    C->inqueue = time;
}
time_t getQtime(void *c)
{
    if(!c)
        return;
    CLIENTE *C = (CLIENTE *)c;
    return C->waiting;
}

void setDisentry(void *c)
{
    if(!c)
        return;
    CLIENTE *C = (CLIENTE *)c;
    C->inSuper=0;
}
void setEntranceTime(void *c, time_t time)
{
    if(!c)
        return;
    CLIENTE *C = (CLIENTE *)c;
    C->entrance = time;
}

time_t getTime(void *c)
{
    if(!c)
        return;
    CLIENTE *C = (CLIENTE *)c;
    return C->entrance;
}
void takeFromWallet(Client *C, double amount)
{
    C->totalCompra += amount;
}
/*
void EntrarSuper(void *c)
{
    if (!c)
        return;
    CLIENTE *C = (CLIENTE *) c;
    C->carrinho = CriarLG();
    /*
    int num_produtos = getRandomInt(1,20);
    //Funcao para randomizar escolha de produtos
    for(int i=0; i<num_produtos; i++)
    {

    }
    /
} */



void SumTimes(void *c)
{
    //printf("SUMSUSMSUMSUMSUM 0 \n");
    if (!c)
        return;
    //printf("SUMSUSMSUMSUMSUM 01 \n");
    CLIENTE *C = (CLIENTE *) c;
   // printf("SUMSUSMSUMSUMSUM 02 \n");
    if (!C->carrinho)
    {
        printf("ERROR: Carrinho is empty");
        return ;
    }
     //printf("SUMSUSMSUMSUMSUM 03 \n");
    NODE *aux = C->carrinho->head;
    while (aux!= NULL)
    {
        // printf("SUMSUSMSUMSUMSUM 04 \n");
        Product *P = (Product *) aux->info;
        //printf("SUMSUSMSUMSUMSUM 55 \n");
        C->totalCaixa += P->TCAIXA;
        C->totalCompra += P->TCOMPRA;
       // printf("SUMSUSMSUMSUMSUM 6664 \n");
        aux = aux->next;
    }

}

