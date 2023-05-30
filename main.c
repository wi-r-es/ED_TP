#include <time.h>
#include "Lib/Headers/listaGenerica.h"
#include "Lib/Headers/supermercado.h"
#include "Lib/Headers/hashing.h"

extern void logging2(char *datafile, const char *funcname, char *info);
extern void logging(char *datafile, const char *funcname, char *info, time_t time);
extern char *logging_file;
extern int getRandomInt(int min, int max);

#ifdef _WIN32
char *metrics_file = "Files\\O\\metrics.txt";
#else
char *metrics_file = "Files/O/metrics.txt";
#endif

void logging_metrics(char *datafile, SM *sm);
void LoadConfigs(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P, ListaGenerica *CX, char *l);
SM *LoadSuper(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P, ListaGenerica *CX, HASHING *hc, treeNode *r);
SM *INIT__();
void FreeMem(SM *sm);
int FreeAllMemory(SM *s);
// const to prevent accidental modification of data
int cmpChar(const void *a, const void *b);
void menu(SM *sm);

int main()
{
    srand(time(NULL));
    clock_t start_t, end_t;
    start_t = clock();
    SM *supermarket = INIT__();
    OpenSuperMarket(supermarket);
    int flag = 0; //flag para fechar supermercado
    while (1)
    {
        static int var = 0;

        if (var == 0)
            logging2(logging_file, __FUNCTION__, "Starting Simulation");
        if(flag==1 && supermarket->Population==0)
            break;
        run(supermarket, flag);

        if (kbhit())
        {
            menu(supermarket);
        }

        /**
        CHECK IF A KEY WAS PRESSED WITH KB_HIT AND IMPLEMENT FUNCTIONS BELOW :
        Colocar uma nova caixa em funcionamento,  por opção do utilizador,
         Num dado instante pode acontecer que uma caixa tenha de fechar, então as
pessoas devem ser distribuídas pelas restantes caixas;
        **/
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
        printf("\r\n\t-----> static var : %d\n\n", var);
        var++;
        time_t timeToClose = VerTimeRelogio(&supermarket->ROLEX);
        if (localtime(&timeToClose)->tm_hour == 23)
        {
            printf("It's time to close the supermarket... no more clients able to enter...");
            flag = 1;
            logging2(logging_file, __FUNCTION__, "Closing Supermarket");
        }
        printf("=================================================================================\n");
    }
    beautify("SIMULATION ENDED :)) !");
    printf("\n Total Clients Served: [%d]\n", supermarket->served);
    logging_metrics(metrics_file, supermarket);
    FreeMem(supermarket);
    logging2(logging_file, __FUNCTION__, "Ending Simulation");
    end_t = clock();
    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    char str[50];
    sprintf(str, "Time to execute->%lf", total_t);
    logging2(logging_file, str, "TOTAL TIME OF EXECUTION");
    return 0;
}

/*********************************************************************************************************************************************************************
 * @brief Loads Clients, employees, products and boxes from files. Generates hashing for clients based on the input.                                                 *
 *                                                                                                                                                                   *
 *      Receives a pointer to clients, employees, products and boxes lists and a char pointer to dynamically create a hashtable from the clients unique initials,\   *
 *      Loads the clients list from a file, aswell as the employees and products.\                                                                                   *
 *      Generates a random number of boxes.                                                                                                                          *
 *                                                                                                                                                                   *
 * @see logging()                                                                                                                                                    *
 * @see Load_Client()                                                                                                                                                *
 * @see Load_Funcionario()                                                                                                                                           *
 * @see Load_Produtos()                                                                                                                                              *
 * @see GenerateBoxes()                                                                                                                                              *
 * @param C : ListaGenerica* for clients/Clientes.                                                                                                                   *
 * @param F : ListaGenerica* for employees/Funcionarios.                                                                                                             *
 * @param P : ListaGenerica* for products/Produtos.                                                                                                                  *
 * @param CX : ListaGenerica* for boxes/Caixas.                                                                                                                      *
 * @param l : char* to get the number of different initials accross the clients list so it can create dynamically , a hashtable after.                               *
 * @return None.                                                                                                                                                     *
 *********************************************************************************************************************************************************************/
void LoadConfigs(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P, ListaGenerica *CX, char *l)
{
    logging2(logging_file, __FUNCTION__, "Loading supermarket configs\n");
    printf("Loading clients from file\n");
    Load_Client(C, l);
    printf("Loading employees from file\n");
    Load_Funcionario(F);
    printf("Loading produtos from file\n");
    Load_Produtos(P);
    printf("generating boxes\n");
    GenerateBoxes(CX);
    logging2(logging_file, __FUNCTION__, "Supermarket configs loaded");
}

/**********************************************************************************************************************************************************
 * @brief Load Supermercado/supermarket structure from the loaded lists for clients, employees, products, boxes, clients hashtable and binary tree (AVL)  *
 *        If any of the pointers to the linked lists or hashtable or tree is null it wont create the new ADT (Abstract Data Structure).                   *
 * @see logging()                                                                                                                                         *
 * @see CriarSM()                                                                                                                                         *
 * @param C : ListaGenerica* of clients/Clientes.                                                                                                         *
 * @param F : ListaGenerica* of employees/Funcionarios.                                                                                                   *
 * @param P : ListaGenerica* of products/Produtos.                                                                                                        *
 * @param CX : ListaGenerica* of boxes/Caixas.                                                                                                            *
 * @param hc : hashtable of clients.                                                                                                                      *
 * @param r : root of the binary tree of products for a quicker search.                                                                                   *
 * @return s -> a pointer to the new supermarket structure.                                                                                               *
 **********************************************************************************************************************************************************/
SM *LoadSuper(ListaGenerica *C, ListaGenerica *F, ListaGenerica *P, ListaGenerica *CX, HASHING *hc, treeNode *r)
{
    logging2(logging_file, __FUNCTION__, "Creating Supermarket struct");
    char *sm_name = "SUPERMERCADOS NOVA";
    printf("Creating super from LL\n\n\n");
    SM *s = CriarSM(sm_name, C, F, P, CX, hc, r);
    logging2(logging_file, __FUNCTION__, "Created");
    return s;
}

/****************************************************************************************************************************************************************************************************
 * @brief Initialize supermarket ADT                                                                                                                                                                *
 *                                                                                                                                                                                                  *
 *        Creates generic linked lists for clients, employees, produtcs and boxes. Load elemets for clients, employees and products from files.                                                     *
 *        Creates an hashtable from the unique first letter in the clients names, using a char pointer intially created with 27 bytes to store each unique letter.(Based on the alphaber from A-Z)  *
 *        After loading the products from the file and generating the entire list, it uses that linked list to create an AVL binary tree of products.                                               *
 *        Finally it creates the supermarket ADT from all the generated linked lists, hashtable and AVL tree mentioned before.                                                                      *
 *                                                                                                                                                                                                  *
 * @see logging()                                                                                                                                                                                   *
 * @see LoadConfigs()                                                                                                                                                                               *
 * @see qsort()                                                                                                                                                                                     *
 * @see cmpChar()                                                                                                                                                                                   *
 * @see CriarHashing()                                                                                                                                                                              *
 * @see CreateTree()                                                                                                                                                                                *
 * @see Load Super()                                                                                                                                                                                *
 * @return sm -> a pointer to the supermarket ADT created.                                                                                                                                          *
 ****************************************************************************************************************************************************************************************************/
SM *INIT__()
{
    logging2(logging_file, __FUNCTION__, "Initializing Supermarket");
    // Initializing vars to use during simulation
    ListaGenerica *LC = CriarLG();
    ListaGenerica *LF = CriarLG();
    ListaGenerica *LP = CriarLG();
    ListaGenerica *LCX = CriarLG();
    // variable to compute hash later
    char *letras = malloc(27 * sizeof(char));
    LoadConfigs(LC, LF, LP, LCX, letras);
    // sort the array
    qsort(letras, strlen(letras), sizeof(char), cmpChar); /**< sorts the string/array_of_chars based on its size, so the hashtable is created in alphabetic order */
    logging2(logging_file, __FUNCTION__, "Creating Hashtable for clients");
    HASHING *hash_table = CriarHASHING(letras); /**< creates the hashtable based on the sorted string of unique initials, so its quicker to search/get a client */
    free(letras);                              /**< frees that memory regarding the string of initials since its now obsolete */
    LoadHashingFromLinkedList(hash_table, LC); /**< Loads the previously created hashtable with the elements in the Clients list */
    logging2(logging_file, __FUNCTION__, "Creating binary tree (AVL) for products");
    treeNode *_root = CreateTree(LP); /**< Creates and loads the tree from the products list */
    SM *sm = LoadSuper(LC, LF, LP, LCX, hash_table, _root);
    // ShowHASHING(sm->clientsHash);
    return sm;
}

/**************************************************
 * @brief Free all dynamic memory in the program  *
 * @see logging()                                 *
 * @see DestruirSM()                              *
 * @param s : supermarket ADT                     *
 * @return 1                                      *
 **************************************************/
int FreeAllMemory(SM *s)
{
    logging2(logging_file, __FUNCTION__, "Freeing all memory");
    DestruirSM(s);
    return 1;
}

/*********************************************************************************************************************
 * @brief Calls the FreeAllMemory() function to check if no errors occured and then logs a message according to that *
 * @param sm -> supermarket ADT                                                                                      *
 * @return None.                                                                                                     *
 *********************************************************************************************************************/
void FreeMem(SM *sm)
{
    int r = FreeAllMemory(sm);
    if (r)
        logging2(logging_file, __FUNCTION__, "Memory Freed");
    else
        logging2(logging_file, __FUNCTION__, "Error while Freeing all memory");
}

/*****************************************************************************************
 * @brief Compares two strings received as parameters too see if they are equal or not.  *
 *        Const to prevet accidental modification of data                                *
 * @param a : first string/char pointer                                                  *
 * @param b : second string/char pointer                                                 *
 * @return The result of the comparisson. 0 if they are equal.                           *
 *****************************************************************************************/
int cmpChar(const void *a, const void *b)
{
    return (*(char *)a - *(char *)b);
}

/****************************************************************************************************
 * @brief Menu for when the simulation is running and the user pressed a keyboard key.              *
 *                                                                                                  *
 *        Can Show the Supermarket ADT                                                              *
 *        Open a box, Close a box                                                                   *
 *        Shutdown Current Simulation and exit the program                                          *
 *        Exit the Menu and return the flow control to the function that starts the simulation      *
 *                                                                                                  *
 * @param sm -> supermarket ADT.                                                                    *
 * @see logging()                                                                                   *
 * @see ShowSM()                                                                                    *
 * @see getClosed()                                                                                 *
 * @see openCaixa()                                                                                 *
 * @see setRandomEmployee()                                                                         *
 * @see ShowCaixa()                                                                                 *
 * @see ShowLG()                                                                                    *
 * @see beautify()                                                                                  *
 * @see traverseBoxesForInstantClose()                                                              *
 * @see FreeMem()                                                                                   *
 * @see sleep()                                                                                     *
 * @return None.                                                                                    *
 ****************************************************************************************************/
void menu(SM *sm)
{
    int choice;
    time_t time = VerTimeRelogio(&sm->ROLEX);
    logging(logging_file, __FUNCTION__, "ACCESSED", time);
    while ((getchar()) != '\n')
        ;

    do
    {
        beautify("<MENU>");
        printf("###   $<1> Show information in Supermarket\n");
        printf("###   $<2> Open a new box\n");
        printf("###   $<3> Close box\n");
        printf("###   $<4> Check the time it is\n");
        printf("###   $<5> Show Products tree and hash table of clients\n");
        printf("###   $<9> Shutdown current simulation\n");
        printf("###   $<0> Exit the menu and return the flow control to run\n");
        printf("\n\n\t <Enter your choice>: ");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);
        while ((getchar()) != '\n');
        printf("CHOICE -> %c\n", choice);
        switch (choice)
        {
        case 1:
            printf("You selected Option 1 - Show Supermarket information\n");
            ShowSM(sm);
            logging(logging_file, __FUNCTION__, "SHOWING SUPERMARKET", time);
            break;
        case 2:
            logging(logging_file, __FUNCTION__, "OPENING NEW BOX",time);
            printf("You selected Option 2 - Open new Box \n");
            void *ptr = getClosed(sm->caixas);
            openCaixa(ptr);
            BOX *B = (BOX *)ptr;
            if (B->funcionario == NULL)
                setRandomEmployee(ptr, sm->employees);
            ShowCaixa(ptr);
            sm->open++;
            printf("NEW BOX OPENENED, From the menu options...\n");

            break;
        case 3:
            logging(logging_file, __FUNCTION__, "CLOSING A BOX",time);
            printf("You selected Option 3 - Close Box\n");
            ShowLG(sm->caixas, ShowOpenCaixa);
            beautify("PLEASE READ INSTRUCTION BELOW CAREFULLY!");
            printf("Please enter an Upper case letter for the ID of the box, otherwise it wont work...\n");
            printf("ID of box to close: ");
            char c = getchar();
            printf("Caixa to be closed: [%c]", c);
            char test = 'A';
            short int flag = 0;
            for (int i = 0; i < sm->caixas->NEL; i++)
            {
                if (c == test)
                    flag = 1;
                test++;
            }
            if (flag)
            {
                traverseBoxesForInstantClose(sm, c);
                printf("Box was closed successfully\n");
            }

            else
                printf("\nOption entered was incorrect....\n");
            // Perform action for Option 3
            break;
        case 4:
            printf("You selected Option 4\n");
            time_t currentTime = VerTimeRelogio(&sm->ROLEX);
            printf("CURRENT TIME: [%d]:[%d]:[%d]", localtime(&currentTime)->tm_hour, localtime(&currentTime)->tm_min, localtime(&currentTime)->tm_sec);
            //Perform action for Option 3
            break;
        case 5:
            printf("You selected Option 5\n");
            printf("TREE\n");
            InOrder(sm->prodTree);
            printf("HASH TABLE\n");
            ShowHASHING(sm->clientsHash);
            // Perform action for Option 3
            break;
        case 9:
            logging(logging_file, __FUNCTION__, "EXITING THE SIMULATION",time);
            logging_metrics(metrics_file, sm);
            FreeMem(sm);
            exit(1);
        case 0:
            logging(logging_file, __FUNCTION__, "EXITING THE MENU->RETURNING FLOW CONTROL TO SIMULATION",time);
            printf("Exiting the menu and return the flow control to run...\n");
            sleep(2);
            break;
        default:
            logging(logging_file, __FUNCTION__, "INVALID CHOICE GIVEN",time);
            printf("Invalid choice. Please try again.\n");
            break;
        }

        printf("\n");
    } while (choice != 0);
}

/*********************************************************************************
 * @brief Appends a log entry of the metrics of the simulation.                  *
 *                                                                               *
 * @param datafile : String representing the datafile                            *
 * @param sm : a pointer to the supermarket                                      *
 * @return None.                                                                 *
 *********************************************************************************/
void logging_metrics(char *datafile, SM *sm)
{
    if (!sm)
        return;
    if (datafile == NULL)
        datafile = "default_metrics.txt";
    // printf("%s",datafile);
    FILE *F = fopen(datafile, "a");
    if (!F)
        return;
    fprintf(F, "**[Simulation Metrics - Date:%s]**\n", __DATE__);
    fprintf(F, "==================================\n");
    fprintf(F, "[]Simulation End Time: [%s]\n", __TIME__);
    fprintf(F, "[]Total costumers served: [%d]\n", sm->served);
    fprintf(F, "[][]Per cashier Box plus extra metrics \n");
    NODE *box_node = (NODE *)sm->caixas->head;
    while(box_node)
    {
        BOX *b = (BOX *) box_node->info;
        fprintf(F, "\t[+]BOX: [%c]\n", b->numero );
        if(b->funcionario)
        {
            fprintf(F, "\t<>[**]Designated Employee: Identification:[%d]<=>Name:[%s]\n", b->funcionario->ID, b->funcionario->name);
            fprintf(F, "\t   <>[+]Total costumers served: [%d]\n", b->served );
            fprintf(F, "\t   <>[+]Total products sold: [%d]\n", (b->totalProducts - b->num_produtos_oferecidos) );
            fprintf(F, "\t   <>[+]Total products offered: [%d] with total value: [%lf]\n", b->num_produtos_oferecidos, b->valor_produtos_oferecidos );
        }
        else fprintf(F, "\t[---]BOX DIDN'T OPENED...., NO INFORMATION TO BE LOGGED.\n");

        box_node = box_node->next;
    }
    BOX *b = getServedMore(sm);
    fprintf(F, "\n[ ]Statistics for better and worst\n");
    fprintf(F, "\t[#]Cashier Box that attended more clients: [%c]\n", b->numero);
    fprintf(F, "\t   >>>Served [%d] clients.\n", b->served);
    fprintf(F, "\t\t[#][-]Employee: [%d]<=>[%s]\n", b->funcionario->ID, b->funcionario->name);
    b = getSoldMore(sm);
    fprintf(F, "\t[#]Cashier Box that sold more products: [%c]\n", b->numero);
    int x = b->totalProducts - b->num_produtos_oferecidos;
    fprintf(F, "\t   >>>Sold [%d] products.\n", x );
    fprintf(F, "\t\t[#][-]Employee: [%d]<=>[%s]\n", b->funcionario->ID, b->funcionario->name);
    Employee *e = getServedLess(sm);
    fprintf(F, "\t[#]Employee who had the worst performance and served less clients:\n\t\t<>[$]Identification:[%d]<=>Name:[%s]\n\n",e->ID, e->name );
    float average = sm->totalWaitingTime/(float) sm->served ;
    fprintf(F, "[]Average waiting time in queue: [%.2f] minutes\n", average/60 );
    fclose(F);
}
