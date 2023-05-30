#include "Headers/utils.h"

/*
#ifdef _WIN32
#else
#include <sys/ioctl.h>
#include <termios.h>
#endif
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
*/

#ifdef _WIN32
char *logging_file = "Files\\O\\logs.csv";
#else
char *logging_file = "Files/O/logs.csv";
#endif

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
    while (clock() < T1)
        ;
}
void Wait(int s)
{
    WaitSegundos(s * CLOCKS_PER_SEC);
}

// #################################################################

// Logging function
void logging(char *datafile, const char *funcname, char *info, time_t time)
{
    if (!funcname || !info)
        return;
    if (datafile == NULL)
        datafile = "default.csv";
    // printf("%s",datafile);
    FILE *F = fopen(datafile, "a");
    if (!F)
        return;
    fprintf(F, "%s, [%s],[EXECUTING_FUNCTION]: %s,[SHORT-BRIEF]: %s\n", __DATE__, asctime(localtime(&time)), funcname, info);
    fclose(F);
}

void logging2(char *datafile, const char *funcname, char *info )
{
    if (!funcname || !info)
        return;
    if (datafile == NULL)
        datafile = "default.csv";
    // printf("%s",datafile);
    FILE *F = fopen(datafile, "a");
    if (!F)
        return;
    fprintf(F, "%s,%s,[EXECUTING_FUNCTION]: %s,[SHORT-BRIEF]: %s\n", __DATE__, __TIME__, funcname, info);
    fclose(F);
}
// A function to display an error message and then exit
void fatal(char *message)
{
    char error_message[100];

    strcpy(error_message, "[!!!] Fatal Error ");
    strncat(error_message, message, 83);
    perror(error_message);
    // abort();
    // exit(-1);
}
void *ec_malloc(unsigned int size)
{
    void *ptr;
    ptr = malloc(size);
    // ptr=NULL;
    if (ptr == NULL)
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
// new ger random since other was was bias
int getRandomInt(int min, int max)
{
    // Seed the random number generator with the current time
    // Calculate the range size and generate a random offset
    int range = max - min + 1;
    int offset = rand() % range;

    // Return the random number within the range
    return min + offset;
}

void beautify(const char *str)
{
    int length = strlen(str);
    int padding = (50 - length) / 2;
    printf("##################################################\n");
    for (int i = 0; i < padding; i++)
        printf("#");
    printf("%s", str);
    // printf("%*s%s%*s\n", padding, "", str,padding, "" );
    for (int i = 0; i < padding; i++)
        printf("#");
    printf("\n");
    printf("##################################################\n");
}

#ifdef _WIN32
#include <stdio.h>
#include <windows.h>

int kbhit()
{
    static HANDLE input_handle = NULL;
    INPUT_RECORD input_record;
    DWORD events_read;

    // Initialize the input handle on the first call
    if (input_handle == NULL)
    {
        input_handle = GetStdHandle(STD_INPUT_HANDLE);
        SetConsoleMode(input_handle, ENABLE_PROCESSED_INPUT);
    }

    // Check if there is any input available
    PeekConsoleInput(input_handle, &input_record, 1, &events_read);
    if (events_read != 0 && input_record.EventType == KEY_EVENT && input_record.Event.KeyEvent.bKeyDown)
    {
        return 1;
    }

    return 0;
}
#else
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int kbhit()
{
    struct termios oldt, newt;
    int oldf, newf;
    int ch;

    // Save the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    // Set the file status flags for stdin to non-blocking
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    // Set the terminal to raw mode
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read one character from stdin
    ch = getchar();

    // Restore the terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    // If a character was read, put it back on the input stream
    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
#endif
