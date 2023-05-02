#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "listaGenerica.h"
#include "produto.h"
#include "utils.h"

typedef struct node
{
    void *Data;
    int ID;
    struct node *left, *right;
    int height;
} treeNode;

int Height(treeNode *root);

treeNode *FindMin(treeNode *root);
treeNode *FindMax(treeNode *root);
treeNode *Find (treeNode *root, void *p);
treeNode *SingleRotateLeft(treeNode *X);
treeNode *SingleRotateRight(treeNode *W);
treeNode *DoubleRotateWithLeft(treeNode *Z);
treeNode *DoubleRotateWithRight(treeNode *Z);

//treeNode *newNode(int _id);
//int getBalance(treeNode *N);
treeNode *Insert(treeNode *root, void *p);

treeNode *CreateTree( LG *P);
int SubTreeSize(treeNode *root);
treeNode *GetAux(treeNode *root, int *x);
treeNode *SelectRandomNode(treeNode *root);
void ShowTreeNode ( treeNode *root);
void InOrder(treeNode *root);






#endif // BINARYTREE_H_INCLUDED
