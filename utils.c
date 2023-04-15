#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>

char *logging_file="Files/O/logs.csv";

//Logging function
void logging(char *datafile, char *funcname, char *info)
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
      fatal("in ec_malloc() on memory allocation");

   /*
   if(ptr == NULL)
      fatal("in ec_malloc() on memory allocation");
   return ptr; */
}
void wait ( int mlseconds )
{
    clock_t endwait;
    endwait = clock () + mlseconds;
    while (clock() < endwait);
}
void wait_segundos ( int seconds )
{
    wait(seconds * CLOCKS_PER_SEC);
}

// Devolve um numero aleatorio entre [min, max]
// Gera um numero aleatorio
int ger_rand(int min, int max)
{
    return min + rand() % (max - min + 1);
}


#endif // UTILS_H_INCLUDED