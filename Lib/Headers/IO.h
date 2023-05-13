#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <ctype.h>
#include "clients.h"
#include "funcionarios.h"
#include "produto.h"
#include "listaGenerica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>

void Load_Client(LG *LC, char *letras);
void Load_Funcionario(LG *LF);
void Load_Produtos(LG *LP);

// for tests purposes
void writeToFile(char *b);
void writeTesting(char *datafile, char *funcname, char *info);

#endif // IO_H_INCLUDED
