#include "Headers/caixa.h"

#define MINQUEUE = 3


BOX *CriarCaixa(char _id)
{
    BOX *B = (BOX *) ec_malloc(sizeof(BOX));
    if(!B){return NULL;}
    B->numero = _id;
    B->status =0;
    B->in_service=0;
    B->funcionario = NULL;
    B->QUEUE=NULL;
    B->cashBox=0;
    B->num_produtos_oferecidos=0;
    B->valor_produtos_oferecidos=0;
    B->auxiliary=NULL;
    B->itemsInQueue=0;
    return B;

}

void GenerateBoxes(LG *lcx)
{
    int ger = getRandomInt(3,10);
    //printf("[%d]\n", ger);
    char id_caixa='A';

    for(int i=0; i<ger; i++){
        BOX *cc= CriarCaixa(id_caixa);
        if (!cc)
        {
            fatal("In generating boxes...");
            break;
        }
        AddLGFim(lcx, cc);
        id_caixa++;
    }
}

void DestruirCaixa(void *b)
{
    BOX *B = (BOX *)b;
    free(B);
}
void ShowCaixa(void *b)
{

    BOX *B = (BOX *)b;
    printf("\n[*]<%s>[*]\n", __FUNCTION__);
    //printf("error   000000\n");
    printf("\t[ ]NUMERO CAIXA: [%c]\n", B->numero);
    printf("\t[ ]STATUS: [%s]\n", B->status==0 ? "FECHADA" : "ABERTA" );
    //printf("error   #################################33\n");
    printf("\t[ ]FUNCIONARIO DA CAIXA: [%s]\n", B->funcionario==NULL ? "SEM FUNCIONARIO DESIGNADO" : "A IR BUSCAR INFORMACAO FUNCIONARIO");
    //printf("error   11111111111\n");
    if (B->funcionario &&  B->status)
        ShowEmployee(( (void *)B->funcionario ));
    /*

    printf("error   222222\n");
    if(B->status)
    {
        if(queueSize(B->QUEUE)>0 )
        printf("\t[ ]CLIENTS IN  QUEUE: [%d]\n", queueSize(B->QUEUE));
    }
    */
//    printf("\t[ ]NUMERO CLIENTES FILA: [%d]\n", B->num_clientes_fila);
    printf("\t[ ]PRODUTOS OFERECIDOS:\n");
    printf("\t\t[+][-]QUANTIDADE->[%d]\n", B->num_produtos_oferecidos);
    printf("\t\t[+][-]VALOR TOTAL->[%lf]\n", B->valor_produtos_oferecidos);
}
void setEmployerTo(void *b, void *e)
{
    if (!b || !e)
        return;
    Employee *E = (Employee *) e;
    BOX *B = (BOX *) b;
    B->funcionario = E;

}

int getStatus(BOX *b)
{
    if(!b)
        return -2;
    BOX *B = (BOX *) b;
    return B->status;
}

int getService(BOX *b)
{

    BOX *B = (BOX *) b;
    return B->in_service;
}
void setService(BOX *b)
{
    if(!b)
        return;
    BOX *B = (BOX *) b;
    B->in_service=1;
}
void unService(BOX *b)
{
    if(!b)
        return;
    BOX *B = (BOX *) b;
    B->in_service=0;
}
void openCaixa(void *b)
{
    if(!b)
        return;
    BOX *B = (BOX *) b;
    B->QUEUE = CriarLG();
    B->status=1;
}
void setAux(void *b, void *c)
{
    if(!b || !c)
        return;
    BOX *B = (BOX *) b;
    B->auxiliary = c;
}
void setRandomEmployee(void *b, LG *lg)
{
    if(!b || !lg)
        return;
    BOX *B = (BOX *) b;
    int pos = getRandomInt(0,lg->NEL-1);
    /*
    NODE *aux = lg->head;
    for(int i=0; i<pos; i++)
    {
         aux = aux->next;
    }
    return aux;

    if (pos ==1 )
    {
        if(getStatusE(aux->info)==1)
        {
            setRandomEmployee(b,lg);
            return;
        }
        setToWork(aux->info);
        B->funcionario = aux->info;
    }
    else
    {
        int count =0;
        while (aux && count < pos)
        {
            aux = aux->next;
            count++;
        }
        */
        NODE *aux = getByPos(lg, pos);
        if(!aux)
        {
            setRandomEmployee(b, lg);
            return;
        }
        if(getStatusE(aux->info)==1)
        {
            setRandomEmployee(b,lg);
            return;
        }
        setToWork(aux->info);
        B->funcionario = aux->info;

   // }
}
void addCash(BOX *b, double money)
{
    if (!b)
        return;
    b->cashBox+= money;
}
void closeCaixa(void *b)
{
    if(!b)
        return;
    BOX *B = (BOX *) b;
}
void closeCaixa_if_min_not_satisfied(void *b)
{
    if(!b)
        return;
    BOX *B = (BOX *) b;

    B->status=0;
}
int AddToQueue(void *b, void *c)
{
    if(!b || !c)
        return -2;
    BOX *B = (BOX *) b;
    LG *q = B->QUEUE;
    return enQueue(q,c);
}

void AddFreeProd(BOX *b,void *p)
{
    if(!b || !p)
        return;
    b->num_produtos_oferecidos++;
    b->valor_produtos_oferecidos += getPrice(p);
}
int getTotalProducts(void *b)
{
     if(!b)
        return -2;
    BOX *B = (BOX *) b;

   return B->itemsInQueue;
}
