#include "Headers/caixa.h"

#define MINQUEUE=3


BOX *CriarCaixa(char _id)
{
    BOX *B = (BOX *) ec_malloc(sizeof(BOX));
    if(!B){return NULL;}
    B->numero = _id;
    B->status =0;
    B->funcionario = NULL;
    B->QUEUE=NULL;
    B->num_produtos_oferecidos=0;
    B->valor_produtos_oferecidos=0;
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
    printf("\t[ ]NUMERO CAIXA: [%c]\n", B->numero);
    printf("\t[ ]STATUS: [%s]\n", B->status==0 ? "FECHADA" : "ABERTA" );
    printf("\t[ ]FUNCIONARIO DA CAIXA: [%s]\n", B->funcionario==NULL ? "SEM FUNCIONARIO DESIGNADO" : "A IR BUSCAR INFORMACAO FUNCIONARIO");
    if (B->funcionario)
        ShowEmployee(( (void *)B->funcionario ));


      // printf("\t[ ]NUMERO CLIENTES FILA: [%d]\n", B->num_clientes_fila);
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

int getStatus(void *b)
{
    if(!b)
        return -2;
    BOX *B = (BOX *) b;
    return B->status;
}
void openCaixa(void *b)
{
    if(!b)
        return;
    BOX *B = (BOX *) b;
    B->QUEUE = CriarLG();
    B->status=1;
}
void setRandomEmployee(void *b, LG *lg)
{
    if(!b || !lg)
        return;
    BOX *B = (BOX *) b;
    int pos = getRandomInt(1,lg->NEL);
    NODE *aux = lg->head;
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

    }
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

void AddFreeProd(void *b,void *p)
{
    if(!b || !p)
        return;
    BOX *B = (BOX *) b;
    Product *P = (Product *) p;
}
