#include "Headers/hashing.h"

extern void *ec_malloc(unsigned int size);

HASHING *CriarHASHING(char *str)
{
    if (!str)
        return;
    HASHING *Has = (HASHING *)ec_malloc(sizeof(HASHING));
     if(!Has)
    {
        fatal("in CriarHASHING(), allocation for client failed... ");
        return;
    }
    int n = strlen(str);
    Has->DADOS = (GROUP *)ec_malloc(sizeof(GROUP) * n); // dynamically allocate DADOS
    if(!Has->DADOS)
    {
        fatal("in CriarHASHING(), allocation for client failed... ");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        (Has->DADOS + i)->Faixa = str[i];
        (Has->DADOS + i)->Clientes = CriarLG();
        // (H->DADOS + i) <=> &H->DADOS[i]
    }
    Has->NEL = n;
    return Has;
}
void DestruirHASHING(HASHING *H)
{
    for (int i = 0; i < H->NEL ; i++)
    {
        DestruirLG( (H->DADOS + i)->Clientes, DestruirClient, 0);
    }
    free(H);
}
void ShowHASHING(HASHING *H)
{
    if (!H) return;
    //printf("FUNCAO: <%s>\n", __FUNCTION__);
    printf("\n[*]<%s>[*]\n", __FUNCTION__);
    for (int i = 0; i < H->NEL; i++)
    {
        ShowFaixa(H, i);
    }
}
void ShowFaixa(HASHING *H, int p)
{
    if (!H) return;
    //printf("FUNCAO: <%s>\n", __FUNCTION__);
    printf("\n[*]<%s>[*]\n", __FUNCTION__);
        printf("\n\r   @FAIXA: [%c]\n", (H->DADOS + p) -> Faixa);
        //if((H->DADOS + i)->Clientes)
        LG *lg = (H->DADOS + p) -> Clientes;
        //printf("\n\r%p", lg->head);
        ShowLG( lg ,ShowClient);
}
int AddHASHING(HASHING *H, void *c)
{
    if (!H)
        return -1; // null pointer
    int posicao = FuncaoHASHING(H, c);
    //printf("Posicao %d\n", posicao);
    if (posicao >=0)
    {   //printf("Posicao %d\n", posicao);
        AddLGInicio(H->DADOS[posicao].Clientes, c);
        return 1;
    }
    return 0;
}
int FuncaoHASHING(HASHING *H, void *c)
{
    if (!H || !c) return -1;

    Client *C = (Client *)c;
    char ch = C->name[0];
    int hash = (int) ch-'A';
    if ((hash >= 0) && (hash < H->NEL) )
        return hash-1 ; // i wonder why ??????
    return -1;

    //printf("\n[%c]\n", ch);
    //int hash = (int) ch - (int)"A" ;
    /*
    if ((hash >= 0) && (hash < H->NEL))
        return hash;
    return -1; */
}

void LoadHashingFromLinkedList(HASHING *hash_table, LG *C)
{
    if (!hash_table || !C)
        return NULL;
    NODE *current = C->head;
    while(current != NULL)
    {
        void *_c = current->info;
        AddHASHING(hash_table,_c);
        current = current->next;
    }
}
void *getElementInFaixa_Pos(HASHING *hash_table, int f, int p)
{
    if (!hash_table)
        return NULL;
    LG *lg = hash_table->DADOS[f].Clientes;
    GROUP g = hash_table->DADOS[f];
    //ShowFaixa(hash_table, f);
    //ShowLG(lg, ShowClient);
    //LG *lg = g.Clientes;
    //printf("%d]    ---    %d]", f, p);
    void *ptr = NULL;
    NODE *aux=lg->head;
    for(int i=0; i<p; i++)
    {
        ptr=aux->info;
        if(aux->next)
            aux->next;
    }
    if(!ptr)
       fatal("Error while getting client in hash...");
    ShowClient(ptr);
    return ptr;
}


