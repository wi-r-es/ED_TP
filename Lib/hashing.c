#include "Headers/hashing.h"

extern void *ec_malloc(unsigned int size);

HASHING *CriarHASHING(char *str)
{
    if (!str)
        return NULL;
    HASHING *Has = (HASHING *)ec_malloc(sizeof(HASHING));
     if(!Has)
    {
        fatal("in CriarHASHING(), allocation for client failed... ");
        return NULL;
    }
    int n = strlen(str);
    Has->DADOS = (GROUP *)ec_malloc(sizeof(GROUP) * n); // dynamically allocate DADOS
    if(!Has->DADOS)
    {
        fatal("in CriarHASHING(), allocation for client failed... ");
        return NULL;
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
        //printf("\n\tFAIXAAAAA-> [%c]", i);

    }
    getchar();
}
void ShowFaixa(HASHING *H, int p)
{
    if (!H) return;
    /*
    //printf("FUNCAO: <%s>\n", __FUNCTION__);
    printf("\n[*]<%s>[*]\n", __FUNCTION__);
    printf("\n\r   @FAIXA: [%c]\n", (H->DADOS + p) -> Faixa);
    //if((H->DADOS + i)->Clientes)
    */

    LG *lg = (H->DADOS + p) -> Clientes;
    printf("\n\tHASHING [%c] -> NEL-> [%d]\n",(H->DADOS+p) -> Faixa  ,lg->NEL );
    //printf("\n\r%p", lg->head);
    //ShowLG( lg ,ShowClient);
    //printf("FAIXA _> %d     ------- LETRA %c \n", p, (H->DADOS + p) -> Faixa) ; // a imprimir valor estranho na faixa ....
}
int AddHASHING(HASHING *H, void *c)
{
    if (!H)
        return -2; // null pointer
    int posicao = FuncaoHASHING(H, c);
    //printf("Posicao %d\n", posicao);
    if (posicao <0)
    {   //printf("Posicao %d\n", posicao);
        fatal("posicao menor que 0 calculada....");
         return -1;
    }
    AddLGInicio(H->DADOS[posicao].Clientes, c);
    return 1;

}
int FuncaoHASHING(HASHING *H, void *c)
{
    if (!H || !c) return -2;

    Client *C = (Client *)c;

    char ch = C->name[0];
    /*
    if (ch == 'U'|| ch == 'V')
        printf("UUUU|VVVV %s\n", C->name);
    */
    int hash = -1;
    for(int i=0; i<H->NEL; i++)
    {
        char f = (H->DADOS + i)->Faixa;
        //printf("\n\nFAIXA ->%c FIRST CHAR ->%c \n", f, ch);

        if (toupper(f) == toupper(ch))
        {
            hash  = i;
        }
    }

    //printf("HASH VALUE = %d----->LETER: [%c]", hash, ch);
    if ((hash >= 0) && (hash < H->NEL) )
        return hash;
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
        return;
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
    //printf("\nDEBUGG->1.....\n");
    LG *lg = hash_table->DADOS[f].Clientes;
    if(!lg || lg->NEL < p)
        return NULL;
    //printf("\nDEBUGG->2.....\n");
    if(f>hash_table->NEL)
        return NULL;
    //printf("\nDEBUGG->3.....\n");
    //GROUP *g = (hash_table->DADOS +f );
    //printf("\nDEBUGG->4.....\n");
    //ShowFaixa(hash_table, f);
    //ShowLG(lg, ShowClient);
    //LG *lg = g->Clientes;
    //printf("\n##[%d]    ---    [%d]\n##", f, p);
    //void *ptr = NULL;
    if (!lg->head)
    {
        fatal("error in list in faixa...");
        return NULL;
    }
    //printf("\nDEBUGG->5.....\n");
    NODE *aux=lg->head;

    void *ptr=aux->info;
    //printf("\nDEBUGG->6.....\n");
    for(int i=0; i<p; i++)
    {
        //ptr=aux->info;
        if(!aux->next){
            fatal("Error element not accessible...");
            //printf("\nDEBUGG->-1.....\n");
        }
        aux=aux->next;
        //printf("\nDEBUGG->7.....\n");

    }
    ptr=aux->info;
    //printf("\nPointing to inside function -> [%p]", ptr);

    //return aux->info;
    //printf("\nDEBUGG->8.....\n");
    if(!ptr)
    {
        fatal("Error while getting client in hash...");
        //printf("\nDEBUGG->-2.....\n");
        return NULL;
    }
    //printf("\nDEBUGG->9.....\n");
    //setEntry(ptr);
    //printf("\nDEBUGG->10.....\n");
    //ShowClient(ptr);

    //printf("Pointing to inside function -> [%p]\n\n\n\n", ptr);
    //printf("\nDEBUGG->11.....\n");
    return ptr;
}


