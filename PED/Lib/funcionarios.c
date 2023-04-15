#include "Headers/funcionarios.h"

extern void *ec_malloc(unsigned int size);

Employee *CriarEmployee(int _id, char * _name)
{
    Employee *E = (Employee *)ec_malloc(sizeof(Employee));
    if(!E)
    {
        fatal("in CriarEmployee(), allocation for Employee failed... ");
        return;
    }
    E->ID = _id;
    E->name = (char *)ec_malloc(strlen(_name) + 1);
    if(!E->name)
    {
        fatal("in CriarEmployee(), allocation for name in Employee failed... ");
        return;
    }

    E->working=0;
    strcpy(E->name, _name);
    return E;
}
void DestruirEmployee(void *e)
{
    Employee *E = (Employee *)e;
    free(E->name);
    free(E);
}
void ShowEmployee(void *e)
{
    Employee *E = (Employee *)e;
    printf("\n[*][%s][*]\n", __FUNCTION__);
    printf("\t[ ]CODIGO ID: [%d]\n\t[ ]NOME: [%s]\n", E->ID, E->name);

}
int compEmployee(void *x, void *y)
{

    Employee *ex = (Employee *)x;
    Employee *ey = (Employee *)y;
    if (ex->ID == ey->ID)
        return 1;
    return 0;

}
int SearchEmployee(void *e, void *_ID)
{
    Employee *E = (Employee *)e;
    int  *Pt_ID = (int *)_ID;
    int key = E->ID;
    if (key == *Pt_ID){
        return 1;
    }
    return 0;
}
int getIdEmployee(void *e)
{
    Employee *E = (Employee *)e;
    return E->ID;
}

