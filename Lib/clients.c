#include "Headers/clients.h"


extern void *ec_malloc(unsigned int size);
int ger_rand(int min, int max);
extern void logging(char* datafile, char *funcname, char *info);
extern char *logging_file;

Client *CriarClient(int _id, char * _name)
{
    //logging(logging_file, __FUNCTION__, "Creating client-element");
    Client *C = (Client *) ec_malloc(sizeof(Client));
    //Client *C = (Client *)malloc(sizeof(Client));
    if(!C)
    {
        fatal("in CriarClient(), allocation for client failed... ");
        return;
    }

    C->ID = _id;
    C->name = (char *)ec_malloc(strlen(_name) + 1);

    if(!C->name)
    {
        fatal("in CriarClient(), allocation for name in client failed... ");
        return;
    }

    strcpy(C->name, _name);
    //printf("NM-> %s", C->name);
    C->inQueue=0;
    C->carrinho=NULL;
    C->tempo_medio_espera=0;
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
    CLIENTE *C = (CLIENTE *)c;
    printf("\n     [*]<%s>[*]\n", __FUNCTION__);
    printf("\t[ ]CODIGO ID: [%d]\n\t[ ]NOME: [%s]\n", C->ID, C->name);
}
int compClient(void *x, void *y)
{
    CLIENTE *px = (CLIENTE *)x;
    CLIENTE *py = (CLIENTE *)y;
    if (px->ID == py->ID)
        return 1;
    return 0;

}

int SearchClient(void *c, void *_ID)
{
    CLIENTE *C = (CLIENTE *)c;
    int  *Pt_ID = (int *)_ID;
    int key = C->ID;
    if (key == *Pt_ID){
        return 1;
    }
    return 0;
}

int SearchClientByName(void *c, void *_name)
{
    CLIENTE *C = (CLIENTE *)c;
    char  *ptr_name = (char *)_name;
    char key = C->name;
    if (strcmp(key, ptr_name)){
        return 1;
    }
    return 0;
}
int getIdClient(void *c)
{
    CLIENTE *C = (CLIENTE *)c;
    return C->ID;
}

//void gerProdutos()

void EntrarSuper(void *c)
{
    if (!c)
        return;
    CLIENTE *C = (CLIENTE *) c;
    C->carrinho = CriarLG();
    int num_produtos = ger_rand(1,20);
    //Funcao para randomizar escolha de produtos
    for(int i=0; i<num_produtos; i++)
    {

    }
}



