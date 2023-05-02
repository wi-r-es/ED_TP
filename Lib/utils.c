#include "Headers/utils.h"
char *logging_file="Files/O/logs.csv";

void StartRelogio(Relogio *R, int Vel, const char *H_Inicio)
{
    R->START = time(0);
    R->VELOCIDADE = Vel;
    struct tm *tmp = localtime(&R->START);
    sscanf(H_Inicio, "%d:%d:%d", &tmp->tm_hour, &tmp->tm_min, &tmp->tm_sec);
    R->Hora_Inicio = mktime(tmp);
    printf("Hora de Arranque = [%s]\n", asctime(localtime(&(R->Hora_Inicio))));
}
time_t VerTimeRelogio(Relogio *R)
{
    time_t Dif = difftime(time(0), R->START);
    time_t Simulada = R->Hora_Inicio + Dif * R->VELOCIDADE;
    return Simulada;
}

void WaitSegundos(int s)
{
    clock_t T0 = clock();
    clock_t T1 = T0 + s;
    while (clock() < T1);
}
void Wait(int s)
{
    WaitSegundos(s*CLOCKS_PER_SEC);
}




//#################################################################


//Logging function
void logging(char *datafile, const char *funcname, char *info)
{
    if( !funcname || !info ) return;
    if (datafile==NULL)
        datafile = "default.csv";
    //printf("%s",datafile);
    FILE *F = fopen(datafile, "a");
    if (!F)
        return;
    fprintf(F, "%s,%s,[EXECUTING_FUNCTION]: %s,[SHORT-BRIEF]: %s\n",__DATE__,__TIME__, funcname, info);
    fclose(F);
}

// A function to display an error message and then exit
void fatal(char *message) {
   char error_message[100];

   strcpy(error_message, "[!!!] Fatal Error ");
   strncat(error_message, message, 83);
   perror(error_message);
   //abort();
   //exit(-1);

}
void *ec_malloc(unsigned int size) {
   void *ptr;
   ptr = malloc(size);
   //ptr=NULL;
    if(ptr == NULL)
    {
        fatal("in ec_malloc() on memory allocation");
        return NULL;
    }

   return ptr;
}

// Devolve um numero aleatorio entre [min, max]
// Gera um numero aleatorio
int ger_rand(int min, int max)
{
    return min + rand() % (max - min + 1);
}
//new ger random since other was was bias
int getRandomInt(int min, int max)
{
    // Seed the random number generator with the current time
    // Calculate the range size and generate a random offset
    int range = max - min + 1;
    int offset = rand() % range;

    // Return the random number within the range
    return min + offset;
}

