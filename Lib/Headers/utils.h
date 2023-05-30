/**********************************************************************************
 *  @file utils.h                                                                 *
 *  @brief Function prototypes of useful functions used across the program.       *
 *                                                                                *
 **********************************************************************************/


#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
/* -- Includes -- */
/* libc includes. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>

/******************************************************************************************************
 * Clock/Relogio ADT structure and vars description                                                   *
 * START                      -> Time of the current system time.                                     *
 * VELOCIDADE                 -> Velocity of the clock, this is, how fast or slow the time passes.    *
 * Hora_Inicio                -> Time when the clock starts.                                          *
 ******************************************************************************************************/
typedef struct
{
    time_t START;
    int VELOCIDADE;
    time_t Hora_Inicio;
} Relogio;

// Logging function
/****************************************************************************************************************************************
 * @brief Initializes the clock R with a given starting time and speed.                                                                 *
 *                                                                                                                                      *
 *        It sets the START field of R to the current system time using time(0).                                                        *
 *        The clock speed is set using the Vel parameter.                                                                               *
 *        The starting time is parsed from the H_Inicio string in the format "hh:mm:ss" and converted to a time_t value using mktime(). *
 *                                                                                                                                      *
 * @param R : a pointer to a Relogio (clock) structure                                                                                  *
 * @param vel : speed of the clock                                                                                                      *
 * @param H_Inicio : Starting time of the clock                                                                                         *
 * @see time()                                                                                                                          *
 * @see localtime()                                                                                                                     *
 * @see mktime()                                                                                                                        *
 * @see asctime()                                                                                                                       *
 * @return None.                                                                                                                        *
 ****************************************************************************************************************************************/
void StartRelogio(Relogio *R, int Vel, const char *H_Inicio);

/****************************************************************************************************************************************
 * @brief Calculates the simulated time based on the current system time, clock speed, and the starting time of the clock R.            *
 *                                                                                                                                      *
 *        It calculates the time difference in seconds between the current system time and the START time of R using difftime().        *
 *        Then, it calculates the simulated time by adding the time difference multiplied by the clock speed to the Hora_Inicio of R.   *
 *                                                                                                                                      *
 * @param R : a pointer to a Relogio (clock) structure.                                                                                 *
 * @see difftime()                                                                                                                      *
 * @return Simulated time in time_t.                                                                                                    *
 ****************************************************************************************************************************************/
time_t VerTimeRelogio(Relogio *R);

/*********************************************************************
 * @brief Pauses the execution for the specified number of seconds.  *
 *********************************************************************/
void Wait(int s);
/*********************************************************************
 * @brief Pauses the execution for the specified number of seconds.  *
 *********************************************************************/
void WaitSegundos(int s);

/*********************************************************************************
 * @brief Appends a log entry to a data file.                                    *
 *                                                                               *
 *       It takes the data file path (datafile),                                 *
 *       the name of the executing function (funcname),                          *
 *       and a brief description of the log message (info).                      *
 *       If the datafile is NULL, it uses a default file name "default.csv".     *
 *       The function opens the file in append mode using fopen(),               *
 *       writes the log entry in the format date,time,function,brief,            *
 *       and then closes the file using fclose().                                *
 *                                                                               *
 * @param datafile : String representing the datafile                            *
 * @param funcname : String represening the name of the funciton                 *
 * @param info : String representing the descriptions of the log message         *
 * @param time : current time in the supermarket
 * @return None.                                                                 *
 *********************************************************************************/
void logging(char *datafile, const char *funcname, char *info, time_t time);
void logging2(char *datafile, const char *funcname, char *info );
// A function to display an error message and then exit
/****************************************************************************************
 * @brief Displays an error message and terminates the program.(NOT ANYMORE FOR NOW)    *
 *                                                                                      *
 * @param message : String representing the error message to be printed                 *
 * @see perror()                                                                        *
 * @return None.                                                                        *
 ****************************************************************************************/
void fatal(char *message);
// Error-check malloc

/********************************************************************************************************************
 * @brief An error-checking wrapper for the malloc() function.                                                      *
 *                                                                                                                  *
 *        It attempts to allocate memory of the specified size (size) using malloc().                               *
 *        If the memory allocation fails, it calls the fatal() function with an error message and returns NULL.     *
 *        If the allocation is successful, it returns a pointer to the allocated memory.                            *
 *                                                                                                                  *
 *                                                                                                                  *
 * @param size : size to be allocated                                                                               *
 * @see fatal()                                                                                                     *
 * @return Pointer to the allocated memory if allocation was successful, NULL otherwise.                            *
 ********************************************************************************************************************/
void *ec_malloc(unsigned int size);
// clock wait

// Devolve um numero aleatorio entre [min, max]
// Gera um numero aleatorio
/********************************************************************
 * @brief Generates a random integer within the range [min, max].   *
 *                                                                  *
 * @param min : minimum number to be generated                      *
 * @param max : maximum number to be generated                      *
 * @see rand()                                                      *
 * @return Random integer within the range.                         *
 ********************************************************************/
int ger_rand(int min, int max); /**< not random enough */
// new ger random since other was bias
/********************************************************************************************************************
 * @brief Generates a random integer within the range [min, max].                                                   *
 *                                                                                                                  *
 *        It calculates the range size and generates a random offset within that range using rand().                *
 *        The random offset is added to the minimum value to obtain a random number within the specified range.     *
 *        This function is an improved version that avoids bias compared to the previous implementation.            *
 *                                                                                                                  *
 * @param min : minimum number to be generated                                                                      *
 * @param max : maximum number to be generated                                                                      *
 * @see rand()                                                                                                      *
 * @return Random integer within the range.                                                                         *
 ********************************************************************************************************************/
int getRandomInt(int min, int max);

/******************************************************************************************************
 * @brief Prints a formatted string surrounded by a decorative frame.                                 *
 *                                                                                                    *
 *       It calculates the padding required to center the string in a frame of width 50 characters.   *
 *       It prints a top frame line consisting of '#' characters.                                     *
 *       It prints the padded string in the center of the frame.                                      *
 *       It prints a bottom frame line consisting of '#' characters.                                  *
 *       The resulting frame visually separates the string from the surrounding content.              *
 *                                                                                                    *
 * @param str : string to be printed withing the decorative frame                                     *
 * @return None.                                                                                      *
 ******************************************************************************************************/
void beautify(const char *str);

#endif // UTILS_H_INCLUDED
