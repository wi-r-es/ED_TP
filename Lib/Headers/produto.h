/*******************************************************************************
 *  @file produto.h                                                            *
 *  @brief Function prototypes for the Product ADT.                            *
 *                                                                             *
 *  This contains the prototypes for the managing of products elements.        *
 *                                                                             *
 *******************************************************************************/

#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED
/* -- Includes -- */
/* libc includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* utils header file */
#include "utils.h" /* for useful functions, and ec_malloc() used to check errors during allocation */

/************************************************************************************************************************************************************
 * Product ADT structure and vars description                                                                                                               *
 * COD                     -> integer of the identification code of each product.                                                                           *
 * name                    -> name of the product.                                                                                                          *
 * preco                   -> double value that represents the price of the product.                                                                        *
 * marca                   -> product brand.                                                                                                                *
 * extra_info              -> aditional information about the product, if it exists in the input file from where the product is loaded.                     *
 * TCOMPRA                 -> float representing the time a client takes to get/search for the product.                                                     *
 * TCAIXA                  -> float representing the time a a product takes to get "scanned" on boxes.                                                      *
 * stock                   -> represents the quantity of products on store. not really used in the simulation                                               *
 ************************************************************************************************************************************************************/
typedef struct PRODUTO
{
    int COD; // codigo
    char *name;
    double preco;
    char *marca;
    char *extra_info;
    float TCOMPRA;
    float TCAIXA;
    int stock;
} Product, *ptr_product;

/**********************************************************************************************************************************
 * @brief Creates a new instance of the Product struct/element, and initializes its fields with the given arguments.              *
 * @param _id : integer representing the identification code of the product.                                                      *
 * @param _name : string representing the name of the product.                                                                    *
 * @param _price : double representing the price/cost of the product.                                                             *
 * @param _marca : string representing the brand of the product.                                                                  *
 * @param _info : string contianing the extra information about the product.                                                      *
 * @param _tcp : float representing the time it takes to get the product.                                                         *
 * @param _tcx :  float representing the time it takes for the product to get scanned.                                            *
 * @see ec_malloc()                                                                                                               *
 * @see fatal()                                                                                                                   *
 * @see ger_rand()                                                                                                                *
 * @return A pointer to a newly created Client struct/element.                                                                    *
 **********************************************************************************************************************************/
Product *CriarProduct(int _id, char *_name, double _price, char *_marca, char *_info, float _tcp, float _tcx);
// Product *CriarProduct(int _id, char * _name, double _price, char * _marca, int _unit_size, char *_unit_type, float _tcp, float _tcx);

/**************************************************************************
 * @brief Frees the memory allocated to a given product struct/element.   *
 * @param p : a pointer to a product struct/element. (Type void*)         *
 * @return None.                                                          *
 **************************************************************************/
void DestruirProduct(void *p);

/*************************************************************************
 * @brief Prints out the fields of a given product struct/element.       *
 * @param p : a pointer to a product struct/element. (Type void*)        *
 * @return None.                                                         *
 *************************************************************************/
void ShowProduct(void *p);

/**********************************************************************************
 * @brief Compares two given products structs/elements based on their COD field.  *
 * @param x : a pointer to a product struct/element. (Type void*).                *
 * @param y : a pointer to a product struct/element. (Type void*).                *
 * @return 1 if the COD fields of the two structs are equal, 0 otherwise.         *
 **********************************************************************************/
int compProduct(void *x, void *y);

/*********************************************************************************************
 * @brief Checks if a given product struct has the same COD field as the given _id string.   *
 * @param  p : a pointer to a product struct/element.(Type void*)                            *
 * @param _id : a void pointer pointing to the identification code to be searched.           *
 * @return 1 if the COD field of the struct is equal to the given _id, 0 otherwise.          *
 *********************************************************************************************/
int SearchProduct(void *p, void *_id);

/**************************************************************************************************************
 * @brief Returns the value of the COD field of a given product struct/element.                               *
 * @param p : a pointer to a product struct/element.(Type void*)                                              *
 * @return An integer representing the value of the COD field of the element, or 0 if the pointer was NULL.   *
 **************************************************************************************************************/
int getIdProduct(void *p);

/**************************************************************************************************************
 * @brief Returns the value of the preco field of a given product struct/element.                             *
 * @param p : a pointer to a product struct/element.(Type void*)                                              *
 * @return Double representing the value of the price of the product element, or 0 if the pointer was NULL.   *
 **************************************************************************************************************/
double getPrice(void *p);

/*********************************************************************************************************
 * @brief Returns the value of the TCOMPRA field of a given product struct/element.                      *
 * @param p : a pointer to a product struct/element.(Type void*)                                         *
 * @return float representing the time it takes to get/find the product, or -2 if the pointer was NULL.  *
 *********************************************************************************************************/
float getProductTimeToGet(void *p);

/*******************************************************************************************************************
 * @brief Returns the value of the TCAIXA field of a given product struct/element.                                 *
 * @param p : a pointer to a product struct/element.(Type void*)                                                   *
 * @return float representing the time it takes the product to get scanned on box, or -2 if the pointer was NULL.  *
 *******************************************************************************************************************/
float getProductTimeToBuy(void *p);
#endif // PRODUTO_H_INCLUDED
