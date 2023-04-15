#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

#include <stdlib.h>
#include <stdlib.h>
#include <string.h>



typedef struct PRODUTO {
    int COD; //codigo
    char *name;
    double preco;
    char *marca;
    char *extra_info;
    /*
    int unit_size;
    char unit_type[3]; */

    float TCOMPRA;
    float TCAIXA;
    int stock;
    //struct produto *next;
}Product, *ptr_product;

Product *CriarProduct(int _id, char * _name, double _price, char * _marca, char * _info, float _tcp, float _tcx);
//Product *CriarProduct(int _id, char * _name, double _price, char * _marca, int _unit_size, char *_unit_type, float _tcp, float _tcx);
void DestruirProduct(void *p);
void ShowProduct(void *p);
int compProduct(void *x, void *y);
int SearchProduct(void *p, void *_ID);
int getIdProduct(void *p);
#endif // PRODUTO_H_INCLUDED


