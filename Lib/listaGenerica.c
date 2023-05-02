#include "Headers/listaGenerica.h"

extern void *ec_malloc(unsigned int size);
extern void logging(char* datafile, char *funcname, char *info);
extern char *logging_file;

ListaGenerica *CriarLG()
{
    logging(logging_file, __FUNCTION__, "Creating genericList");
    ListaGenerica *L = (ListaGenerica *)ec_malloc(sizeof(ListaGenerica));
    if (!L) return NULL;
    L->head = NULL;
    L->tail = NULL;
    L->NEL = 0;
    logging(logging_file, __FUNCTION__, "GenericList Created");
    return L;
}
void DestruirLG(ListaGenerica *lg, void (*fdest)(void *), int t) //fdest pointer to function
{
    logging(logging_file, __FUNCTION__, "Deleting genericList");
    if (!lg) return NULL;
    NODE *p = lg->head;
    NODE *aux;
    while(p)
    {
        aux = p->next;
        if (t == 1) fdest(p->info); // pointer to the function to clear the info inside LG
        free(p);
        p = aux;
    }
    free(lg);
    logging(logging_file, __FUNCTION__, "GenericList Deleted");
}
void ShowLG(ListaGenerica *lg, void (*f)(void *))
{
    logging(logging_file, __FUNCTION__, "Showing genericList");
    if (!lg) { printf("DEBUG");return;}
    NODE *p = lg->head;
    while(p)
    {

        f(p->info);
        p = p->next;
    }
    logging(logging_file, __FUNCTION__, "Showing genericList sucessfull");
}

void AddLGInicio(ListaGenerica *lg, void *X) // Adiciona elementos segundo uma pilha/stack
{
    //logging(logging_file, __FUNCTION__, "Adding to head-genericList");
    if (!lg || !X)
        return;
    NODE *p = (NODE *)ec_malloc(sizeof(NODE));
    if (!p)
        return;
    p->next = lg->head;
    p->prev = NULL;
    p->info = X;
    lg->head = p;
    lg->NEL++;
    //logging(logging_file, __FUNCTION__, "Adding successfull");
}

void AddLGFim(LG *lg, void *x) //Adicionar no fim
{
    //logging(logging_file, __FUNCTION__, "Adding to tail-genericList");
    if (!lg || !x)
        return;
    /*
    NODE *aux = (NODE *)ec_malloc(sizeof(NODE));
    if (!aux)
        return;
    aux->info = x;
    aux->next = NULL;

    if (!lg->head)
    {
        aux->prev = NULL;
        lg->head=aux;
    }

    else
    {
        NODE *iterator = lg->head;
        while (iterator->next)
            iterator = iterator->next;
        iterator->next = aux;
        aux->prev = iterator;
    }
    lg->NEL++; */

    NODE *aux = (NODE *)ec_malloc(sizeof(NODE));
    if (!aux)
        return ; // Erro de alocacao de memoria before it returned -4
    aux->info = x;
    aux->next = NULL;
    if (!lg->head)
        lg->head=aux;
    else
    {
        NODE *iterator = lg->head;
        while (iterator->next)
            iterator = iterator->next;
        iterator->next = aux;
        lg->tail = aux;
    }
    lg->NEL++;
    //printf("\n DEBUG el add");
    //logging(logging_file, __FUNCTION__, "Adding successfull");
}

int PertenceLG(ListaGenerica *lg, void *X, int (*fcomp)(void *, void *))
{
    //logging(logging_file, __FUNCTION__, "Checking if given element belongs to list");
    if (!lg || !X) return 0;
    NODE *p = lg->head;
    while(p)
    {
        if (fcomp(p->info, X) == 1) return 1;
        p = p->next;
    }
    return 0;
}

void* SearchLG(LG *lg, void *key, int (*fsearch)(void*, void*))
{
    //logging(logging_file, __FUNCTION__, "Searching for given element belongs in list");
    if (!lg || !key)
        return NULL;
    NODE *p = lg->head;
    while(p)
    {
        if (fsearch(p->info, key) == 1)
            return p->info;
        p = p->next;
    }
    return NULL;
}
