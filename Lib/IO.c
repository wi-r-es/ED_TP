#include "Headers/IO.h"

#ifdef _WIN32
char *clients_file = "Files\\I\\clientes.txt";
char *employees_file = "Files\\I\\funcionarios.txt";
char *products_file = "Files\\I\\produtos.txt";
#else
char *clients_file = "Files/I/clientes.txt";
char *employees_file = "Files/I/funcionarios.txt";
char *products_file = "Files/I/produtos.txt";
#endif

extern void logging(char *datafile, const char *funcname, char *info);
extern char *logging_file;
extern void fatal(char *message);

void Load_Client(LG *LC, char *letras)
{
    logging(logging_file, __FUNCTION__, "Loading clients from file");
    FILE *F = fopen(clients_file, "r");
    // printf("%p",F);
    if (!F)
    {
        logging(logging_file, __FUNCTION__, "Failed to Load from file");
        return;
    }
    // char letras[27];
    int letra_count = 0;
    char BUFFER[1024 + 1];
    while (!feof(F))
    {
        fgets(BUFFER, 1024, F);
        // printf("Linha: [%s]\n", BUFFER);

        char *NAME;
        int i = 0;
        char *CAMPOS[10];
        char *token = strtok(BUFFER, "\t");
        while (token != NULL)
        {
            // printf("[%s]", token);
            CAMPOS[i] = token;
            token = strtok(NULL, "\t\n");
            i++;
        }
        char *ID = CAMPOS[0];

        NAME = CAMPOS[1];
        // printf("[][][][][][][]->>>%s[[[[[[[[[[[[[[", NAME);

        int index = strcspn(NAME, "\r\n"); // procura o indice do char \r\n
        NAME[index] = '\0';                // troca o \r\n pelo null terminator byte \0
        // printf("NM-> %s", NAME);
        CLIENTE *C = CriarClient(ID, NAME);
        // ShowClient(C);
        // DestruirClient(C);
        if (!C)
            printf("ERROR client element wasnt successfully created...");
        else
            AddLGInicio(LC, C);

        char first_char = toupper(NAME[0]);
        // stores the char if its not already in the array
        /**< only stores unique initials so there are no duplicates, this way a dynamic hashtable can be created */
        if (isalpha(first_char))
        {
            int found = 0;
            for (int i = 0; i < letra_count; i++)
            {
                if (letras[i] == first_char)
                {
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                // first use the var then increments
                letras[letra_count++] = first_char;
                // printf("Letra not int hash-> [%c] -- NAME ->[%s]\n", first_char, NAME);
            }
        }
    }
    letras[letra_count] = '\0';
    fclose(F);
    logging(logging_file, __FUNCTION__, "Clients loaded");
}

void Load_Funcionario(LG *LF)
{
    logging(logging_file, __FUNCTION__, "Loading employees from file");
    FILE *F = fopen(employees_file, "r");
    if (!F)
    {
        logging(logging_file, __FUNCTION__, "Failed to Load from file");
        return;
    }

    char BUFFER[1024 + 1];
    while (!feof(F))
    {
        fgets(BUFFER, 1024, F);
        // printf("Linha: [%s]\n", BUFFER);
        int ID;
        char *NAME;
        int i = 0;
        char *CAMPOS[10];
        char *token = strtok(BUFFER, "\t");
        while (token != NULL)
        {
            // printf("[%s]", token);
            CAMPOS[i] = token;
            token = strtok(NULL, "\t\n");
            i++;
        }
        ID = atoi(CAMPOS[0]);
        NAME = CAMPOS[1];
        int index = strcspn(NAME, "\r\n"); // procura o indice do char \r\n
        NAME[index] = '\0';                // troca o \r\n pelo null terminator byte \0
        // printf("%s\n", NAME);

        Employee *E = CriarEmployee(ID, NAME);
        // ShowEmployee(E);
        // DestruirEmployee(E);
        AddLGFim(LF, E);
    }
    fclose(F);
    logging(logging_file, __FUNCTION__, "Employees loaded");
}
void Load_Produtos(LG *LP)
{
    logging(logging_file, __FUNCTION__, "Loading products from file");
    // static var = 0;
    FILE *F = fopen(products_file, "r");
    // printf("%p",F);
    if (!F)
    {
        logging(logging_file, __FUNCTION__, "Failed to Load from file");
        return;
    }

    char BUFFER[1024 + 1];
    while (!feof(F))
    {

        fgets(BUFFER, 1024, F);
        // printf("Linha: [%s]\n", BUFFER);
        int CODIGO;
        char *s, *s1, *s2, *s3;
        int i = 0;
        char *CAMPOS[10];
        char *token = strtok(BUFFER, "\t");
        while (token != NULL)
        {
            // printf("[%s]", token);
            CAMPOS[i] = token;
            token = strtok(NULL, "\t\n");
            i++;
        }
        CODIGO = atoi(CAMPOS[0]);
        // guardar S numa unica string
        s = CAMPOS[1];                   // string que contem nome+marca+peso|unidades
        s1 = CAMPOS[2];                  // string que contem TCOMPRA
        s2 = CAMPOS[3];                  //     "   q contem TCAIXA
        s3 = CAMPOS[4];                  //     "      com preco e caracter \r\n
        int index = strcspn(s3, "\r\n"); // procura o indice do char \r\n
        s3[index] = '\0';                // troca o \r\n pelo null terminator byte \0

        // printf("\t[-][%s_]\n", s);
        /*        printf("\t[-][%s]\n", s);
                printf("\t[-][%s]\n", s1);
                printf("\t[-][%s]\n", s2);
                printf("\t[-][%s]\n", s3);

                char *str, *str1, *str2;
                //str2 = strcat(s2,s3);
                //str1 = strcat(s,s1);
                //str=strcat(str1,str2);
                //str=strcat(str,"\n");
                str=strcat(s, "\n");
        */

        // GUARDAR NOME DO ARTIGO/PRODUTO
        token = strtok(s, "[");
        i = strlen(token);
        token[i - 1] = '\0'; // troca o " " pelo null terminator byte \0
        char *NAME = token;
        // GUARDAR A MARCA
        token = strtok(NULL, "[");
        char *MARCA = strtok(token, "]");
        token = strtok(NULL, "]");

        // GUARDAR TCAIXA TCOMPRA E PRECO
        char *_info;
        if (token == NULL) // vERIFICA SE EXISTE INFORMACAO ADICIONAL DO PRODUTO OU NAO
        {
            _info = "SEM INFORMACAO ADICIONAL";
        }
        else
        {
            _info = token;
        }
        float TCOMPRA = strtof(s1, NULL); /**< usar a funcao strtof para converter a string para um float tambem poderia ser a funcao atof e atod... */
        float TCAIXA = strtof(s2, NULL);
        double PRICE = strtod(s3, NULL); /**< e strtod para converter a string para um double */
        // printf("\n[][][]\t[%f]\t[%f]\t[%lf]\n\n",TCOMPRA, TCAIXA, PRICE); break;
        // printf("[][%d]\n[][%s]\n[][%lf]\n[][%s]\n[%d]\n[][%s]\n[][%f]\n[][%f]...",CODIGO, NAME, PRICE, MARCA, unit_size, unit_type,TCOMPRA, TCAIXA); break;

        Product *PR = CriarProduct(CODIGO, NAME, PRICE, MARCA, _info, TCOMPRA, TCAIXA);
        // Product *PR = CriarProduct(CODIGO, NAME, PRICE, MARCA, unit_size, unit_type,TCOMPRA, TCAIXA);

        // ShowProduct(PR);
        // DestruirProduct(PR);

        AddLGInicio(LP, PR);
        // var++;
        // printf("[%d]", var);
    }
    fclose(F);
    logging(logging_file, __FUNCTION__, "Products loaded");
    // printf("[%d]", var);
}

// for test purposes
void writeToFile(char *b)
{
    char *datafile = "newTEST";
    int fd; //= create(datafile, mode_t mode)

    fd = open(datafile, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    char *s = strcat(b, "\n");
    // printf("%d", fd);
    if (fd == -1)
        fatal("in main() while opening file");
    // printf("[DEBUG] file descriptor is %d\n",fd);
    // writting file
    if (write(fd, s, strlen(s)) == -1)
        fatal("in main() while writting buffer to file");
    // closing file
    if (close(fd) == -1)
        fatal("in main() while closing file");
}

void writeTesting(char *datafile, char *funcname, char *info)
{
    if (!funcname || !info)
        return;
    if (datafile == NULL)
        datafile = "testingHashing.txt";
    // printf("%s",datafile);
    FILE *F = fopen(datafile, "a");
    if (!F)
        return;
    fprintf(F, "%s,%s,[EXECUTING_FUNCTION]: %s,[SHORT-BRIEF]: %s\n", __DATE__, __TIME__, funcname, info);
    fclose(F);
}
