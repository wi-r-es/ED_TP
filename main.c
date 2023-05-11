#include <time.h>
#include "Lib/Headers/listaGenerica.h"
#include "Lib/Headers/supermercado.h"
#include "Lib/Headers/hashing.h"

extern void logging(char* datafile, const char *funcname, char *info);
extern char *logging_file;
extern int getRandomInt(int min, int max);

void LoadConfigs(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P, ListaGenerica *CX, char *l);
SM *LoadSuper(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P, ListaGenerica *CX, HASHING *hc, treeNode *r);
SM *INIT__();
void FreeMem(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P);
int FreeAllMemory(SM *s);
//const to prevent accidental modification of data
int cmpChar(const void* a, const void* b);
/* CLOCk
printf("Simulacao de um Relogio-Acelerado!\n");
    Relogio Rolex;
    StartRelogio(&Rolex, 500, "8:30:00");
    while (true)
    {
        time_t Simulada = VerTimeRelogio(&Rolex);
        printf("Simulada = %s", asctime(localtime(&Simulada)));
        //Wait(1);
        WaitSegundos(500);
    }
    return 0;
*/
int main()
{
   //srand(time(NULL));
    clock_t start_t, end_t;
    start_t = clock();

    //printf("\nDEABUG !!!!!!");
    SM *supermarket=INIT__();
/*
    Client *x= CriarClient(33, "Vitor Lafas");
    int p = FuncaoHASHING(supermarket->clientsHash, x);
    printf("\nPOSI->[%d]\n\n", p);
    //printf("\nlalalalalaa !!!!!!");
*/
    OpenSuperMarket(supermarket);


    //InOrder(supermarket->prodTree);
    //printf("SIM ENTRANCE");
    //ShowSM(supermarket);

    while(1){
            static int var =0;
              //break;
            //printf("1111111111111111111111111111111\n");
            // BREAKING IN THE FUNCTION RUN SOMEWHERE!!!!!!
            run(supermarket);

/*
            if (kbhit())
            {
                    char option = getchar();
                    // ENTER TO THE MENU FUCNTION...
            } */
            /**
            CHECK IF A KEY WAS PRESSED WITH KB_HIT AND IMPLEMENT FUNCTIONS BELOW :
            Colocar uma nova caixa em funcionamento,  por opção do utilizador,
             Num dado instante pode acontecer que uma caixa tenha de fechar, então as
pessoas devem ser distribuídas pelas restantes caixas;
            **/
            //break;
            printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\r\n\t-----> static var : %d\n\n", var);
    var++;
    time_t timeToClose = VerTimeRelogio(&supermarket->ROLEX);
    if (localtime(&timeToClose)->tm_hour == 23 )
    {
        printf("It's time to close the supermarket... no more clients able to enter...");
        /*something more to deal with the clients in the queue here.... */
        break;
    }
    /*
    if(var== 101)
        break; */
    //break;
    }
    printf("\n\n##################");

    //ShowHASHING(supermarket->clientsHash);
    //ShowLG(supermarket->caixas, ShowCaixa);

    int r= FreeAllMemory(supermarket);
    if(r)
        logging(logging_file, __FUNCTION__, "Memory Freed");
    else
        logging(logging_file, __FUNCTION__, "Error while Freeing all memory");



    printf("\vHello world!\n");
    end_t = clock();
    double total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
    char str[50];
    sprintf(str, "Time to execute->%lf", total_t);
    //har *s="Time to execute->";
    //strcat(s,str);
    logging(logging_file, str, "TOTAL TIME OF EXECUTION");

    return 0;
}



/** \brief
 *
 * \param C ListaGenerica*
 * \param F ListaGenerica*
 * \param P ListaGenerica*
 * \param CX ListaGenerica*
 * \param l char*
 * \return void
 *
 */
void LoadConfigs(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P, ListaGenerica *CX, char *l)
{
    logging(logging_file, __FUNCTION__, "Loading supermarket configs\n");
    printf("Loading clients from file\n");
    Load_Client(C, l);
    printf("Loading employees from file\n");
    Load_Funcionario(F);
    printf("Loading produtos from file\n");
    Load_Produtos(P);
    printf("generating boxes\n");
    GenerateBoxes(CX);
    logging(logging_file, __FUNCTION__, "Supermarket configs loaded");
}
SM *LoadSuper(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P, ListaGenerica *CX, HASHING *hc, treeNode *r)
{
    logging(logging_file, __FUNCTION__, "Creating Supermarket struct");
    char *sm_name="SUPERMERCADOS NOVA";
    printf("Creating super from LL\n\n\n");
    SM *s = CriarSM(sm_name,C,F,P,CX, hc, r);
    return s;
    logging(logging_file, __FUNCTION__, "Created");
}
SM *INIT__()
{
    //Initializing vars to use during simulation
    ListaGenerica *LC = CriarLG();
    ListaGenerica *LF = CriarLG();
    ListaGenerica *LP = CriarLG();
    ListaGenerica *LCX = CriarLG();

    //variable to compute hash later
    char *letras = malloc(27 * sizeof(char));
    LoadConfigs(LC, LF, LP, LCX, letras);
    // sort the array
    qsort(letras, strlen(letras), sizeof(char), cmpChar);
    HASHING *hash_table = CriarHASHING(letras);
    //for(int i=0; i<strlen(letras)+1; i++){
    //printf("LETRAS in string : [%c]\n", letras[i]);}
    free(letras);
    LoadHashingFromLinkedList(hash_table, LC);
    treeNode *_root = CreateTree(LP);
    SM *sm = LoadSuper(LC, LF, LP, LCX,hash_table, _root );
    //ShowHASHING(sm->clientsHash);
    return sm;
}



//void simulateEntrance()
   //printf("%d --> %d", random->ID, random->height);

    //InOrder(root);
    //ShowProduct(LP->head->info);
/*
    printf("\n\r[%d]#", strlen(letras));
    for(int i=0; i< strlen(letras); i++){
        printf("\n\r[%c]#", letras[i]);
    }
*/


        //void *ptr = LC->head->info;
    //ShowClient(ptr);
    //AddHASHING(hash_table, ptr);
        //ShowHASHING(hash_table);




    //ShowLG(LC, ShowClient);
int FreeAllMemory(SM *s)
{
    logging(logging_file, __FUNCTION__, "Freeing all memory");
    DestruirSM(s);
    return 1;
}
void FreeMem(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P)
{
    DestruirLG(C, DestruirClient,1);
    DestruirLG(F, DestruirClient,1);
    DestruirLG(P, DestruirClient,1);
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
