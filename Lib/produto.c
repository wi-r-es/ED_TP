#include "Headers/produto.h"

extern void *ec_malloc(unsigned int size);

Product *CriarProduct(int _id, char * _name, double _price, char * _marca, char * _info, float _tcp, float _tcx)
{
    Product *P = (Product *)ec_malloc(sizeof(Product));
    if(!P)
    {
        fatal("in CriarProduct(), allocation for product failed... ");
        return NULL;
    }
    P->COD = _id;
    P->name = (char *)ec_malloc(strlen(_name) + 1);
    if(!P->name)
    {
        fatal("in CriarProduct(), allocation for name in product failed... ");
        return NULL;
    }
    strcpy(P->name, _name);
    P->preco = _price;
    P->marca = (char *)ec_malloc(strlen(_marca)+1);
    if(!P->marca)
    {
        fatal("in CriarProduct(), allocation for marca in product failed... ");
        return NULL;
    }
    strcpy(P->marca, _marca);
    P->extra_info = (char *)ec_malloc(strlen(_info)+1);
    if(!P->extra_info)
    {
        fatal("in CriarProduct(), allocation for extra_info in product failed... ");
        return NULL;
    }
    strcpy(P->extra_info,_info);
    P->TCOMPRA = _tcp;
    P->TCAIXA = _tcx;
    P->stock = ger_rand(10,20);
    return P;
}
void DestruirProduct(void *p)
{
    Product *P = (Product *)p;
    free(P->name); //Fazer free do name && marca && info adicional
    free(P->marca);
    free(P->extra_info);
    //free(P->)
    free(P);
}
void ShowProduct(void *p)
{
    Product *P = (Product *) p;
    printf("\n[-][-]<%s]>-][-]\n", __FUNCTION__);
    printf("\t[ ]CODIGO ID: [%d]\n\t[ ]NOME ARTIGO: [%s]\n", P->COD, P->name);
    printf("\t[ ][]MARCA: [%s]\n", P->marca);
    printf("\t[ ][][][+]PRECO: [%lf]\n", P->preco);
    printf("\t[ ][*]INFORMACAO ADICIONAL[*]\n");
    printf("\t[#][*]%s[*]\n", P->extra_info);

    //printf("\t[ ][][]UNIT SIZE: [%d]\t[]UNIT TYPE: [%s]\n", P->unit_size, P->unit_type);
    printf("\t[ ][]TEMPO_COMPRA: [%f]\tTEMPO_CAIXA: [%f]\n", P->TCOMPRA, P->TCAIXA);
    printf("\t[ ][][]stock: [%d]\n\n\n", P->stock);

}
int compProduct(void *x, void *y)
{
    Product *px = (Product *)x;
    Product *py = (Product *)y;
    if (px->COD == py->COD)
        return 1;
    return 0;
}
int SearchProduct(void *p, void *_ID)
{
    Product *P = (Product *)p;
    int  *Pt_ID = (int *)_ID;
    int key = P->COD;
    if (key == *Pt_ID){
        return 1;
    }
    return 0;
}

int getIdProduct(void *p)
{
    if(!p) return -2;
    Product *P = (Product *)p;
    return P->COD;
}
float getProductTimeToGet(void *p)
{
    if(!p) return -2;
    Product *P = (Product *)p;
    return P->TCOMPRA;
}
float getProductTimeToBuy(void *p)
{
    if(!p) return -2;
    Product *P = (Product *)p;
    return P->TCAIXA;
}
