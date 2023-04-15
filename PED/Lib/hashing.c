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
        DestruirLG( (H->DADOS + i)->Clientes, DestruirClient);
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
        printf("Faixa: [%c]\n", (H->DADOS + i) -> Faixa);
        //if((H->DADOS + i)->Clientes)
        LG *lg = (H->DADOS + i)->Clientes;
        printf("\n\r%n", lg);
        ShowLG( lg ,ShowClient);
    }
}
int AddHASHING(HASHING *H, void *c)
{
    if (!H)
        return -1; // null pointer
    int posicao = FuncaoHASHING(H, c);
    if (posicao >= 0)
    {
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
    int hash = (int) ch;
    if ((hash >= 0) && (hash < H->NEL))
        return hash;
    return -1;
}
