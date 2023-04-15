#include <time.h>
#include "Lib/Headers/listaGenerica.h"
#include "Lib/Headers/supermercado.h"
#include "Lib/Headers/hashing.h"

extern void logging(char* datafile, char *funcname, char *info);
extern char *logging_file;

void LoadConfigs(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P, ListaGenerica *CX, char *l);
void FreeMem(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P);
SM *LoadSuper(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P, ListaGenerica *CX);
int FreeAllMemory(SM *s);
//const to prevent accidental modification of data
int cmpChar(const void* a, const void* b);

int main()
{
    clock_t start_t, end_t;
    start_t = clock();

    //Initializing vars to use during simulation
    ListaGenerica *LC = CriarLG();
    ListaGenerica *LF = CriarLG();
    ListaGenerica *LP = CriarLG();
    ListaGenerica *LCX = CriarLG();

    //variable to compute hash later
    char *letras = malloc(27 * sizeof(char));
    LoadConfigs(LC, LF, LP, LCX, letras);
    SM *super = LoadSuper(LC, LF, LP, LCX);
/*
    printf("\n\r[%d]#", strlen(letras));
    for(int i=0; i< strlen(letras); i++){
        printf("\n\r[%c]#", letras[i]);
    }
*/
    // sort the "array
    qsort(letras, strlen(letras), sizeof(char), cmpChar);
    HASHING *hash_table = CriarHASHING(letras);
    void *ptr = LC->head;
    AddHASHING(hash_table, ptr);
    ShowHASHING(hash_table);





    ShowLG(LCX, ShowCaixa);
    int r= FreeAllMemory(super);
    if(r)
        logging(logging_file, __FUNCTION__, "Memory Freed");
    else
        logging(logging_file, __FUNCTION__, "Error while Freeing all memory");
    //ShowLG(LC, ShowClient);


    printf("\vHello world!\n");
    end_t = clock();
    double total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
    char *str[50];
    sprintf(str, "Time to execute->%lf", total_t);
    //har *s="Time to execute->";
    //strcat(s,str);
    logging(logging_file, str, "TOTAL TIME OF EXECUTION");

    return 0;
}



void LoadConfigs(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P, ListaGenerica *CX, char *l)
{
    logging(logging_file, __FUNCTION__, "Loading supermarket configs");
    Load_Client(C, l);
    Load_Funcionario(F);
    Load_Produtos(P);
    GenerateBoxes(CX);
    logging(logging_file, __FUNCTION__, "Supermarket configs loaded");
}
SM *LoadSuper(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P, ListaGenerica *CX)
{
    logging(logging_file, __FUNCTION__, "Creating Supermarket struct");
    char *sm_name="SUPERMERCADOS NOVA";
    SM *s = CriarSM(sm_name,C,F,P,CX);
    return s;
    logging(logging_file, __FUNCTION__, "Created");
}
int FreeAllMemory(SM *s)
{
    logging(logging_file, __FUNCTION__, "Freeing all memory");
    DestruirSM(s);
    return 1;
}
void FreeMem(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P)
{
    DestruirLG(C, DestruirClient);
    DestruirLG(F, DestruirClient);
    DestruirLG(P, DestruirClient);
}

//const to prevent accidental modification of data
int cmpChar(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}



    /*
    int key= 129617;
    void *ptr =&key;
    void *xx = SearchLG(LC, ptr, SearchClient);
    ShowClient(xx);
    */
    /*
    int key= 7547;
    void *ptr =&key;
    void *xx = SearchLG(LF, ptr, SearchEmployee);
    ShowEmployee(xx);

    //key= 50825;

    //void *ptr =&key;
    void *yy = SearchLG(LP, ptr, SearchProduct);
    ShowProduct(yy);
    */


    //char *str="Ola o mew nome e pedro";
    //char *n = (char *) ec_malloc (strlen(str)+1);
