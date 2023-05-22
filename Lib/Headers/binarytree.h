/*******************************************************************************
 *  @file binarytree.h                                                         *
 *  @brief Function prototypes to manage binary tree ADT (AVL type).           *
 *                                                                             *
 *  This contains the prototypes for managig AVL binary trees.                 *
 *                                                                             *
 *******************************************************************************/

#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
/* -- Includes -- */
/* libc includes. */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
/* listaGenerica header file */
#include "listaGenerica.h"
/* produto header file */
#include "produto.h"
/* utils header file */
#include "utils.h"

/****************************************************************************************************************
 * Binary Tree - AVL - ADT structure and vars description (Used for quicker searches)                           *
 * Data                    -> pointer to the ADT element in the tree node, for this use case the product ADT.   *
 * ID                      -> ID of the element it has. This case, the product COD.                             *
 * left                    -> left child of the node.                                                           *
 * right                   -> right child of the node.                                                          *
 * height                  -> height of the node.                                                               *
 ****************************************************************************************************************/
typedef struct node
{
    void *Data;
    int ID;
    struct node *left, *right;
    int height;
} treeNode;

/********************************************************************
 * @brief Returns the height of the given binary tree node.         *
 * @param root : binary tree node                                   *
 * @return Binary tree node height or -1 if root is a null pointer. *
 ********************************************************************/
int Height(treeNode *root);

/********************************************************************************************************
 * @brief Finds and returns the node with the minimum value in the binary tree root.                    *
 * @param root : binary tree node                                                                       *
 * @return Pointer to node with Minimum value in binary tree or NULL pointer if root is a null pointer. *
 ********************************************************************************************************/
treeNode *FindMin(treeNode *root);

/********************************************************************************************************
 * @brief Finds and returns the node with the maximum value in the binary tree root.                    *
 * @param root : binary tree node                                                                       *
 * @return Pointer to node with Maximum value in binary tree or NULL pointer if root is a null pointer. *
 ********************************************************************************************************/
treeNode *FindMax(treeNode *root);

/*******************************************************************************************************************************************
 * @brief Searches for a node in the binary tree root, and returns the tree node if it was found.                                          *
 *                                                                                                                                         *
 *        Searches for a node in the binary tree root based on a comparison with the value p.                                              *
 *        It assumes that the value p can be cast to a Product type, and it uses the COD field of the Product struct for the comparison.   *
 *        ~(wasnt used, so its not tested, but should work just fine as it is)~                                                            *
 *                                                                                                                                         *
 * @param root : binary tree node                                                                                                          *
 * @param p : element to look for in tree                                                                                                  *
 * @return Pointer to node if its found, NULL otherwise and if the root or p is a null pointer.                                            *
 *******************************************************************************************************************************************/
treeNode *Find(treeNode *root, void *p);

/******************************************************************************************************************************************
 *  When the tree structure changes (by insertion or deletion) we need to modify the tree to restore the AVL tree property                *
 *  This is the height of the Right and Left subtree of X node differ at most 1.                                                          *
 *  When the tree structure changes (by insertion or deletion) we need to modify the tree to restore the AVL tree, property.              *
 *  This can be achieved with single rotations or left rotations depending on the type of violation.                                      *
 *                                                                                                                                        *
 *  OBSERVATION: after an insertion, only nodes that are on the path from the insertion point to the root might have their                *
 * balances altered, because only those nodes have their subtrees altered. So only needs to go from the insertion point to the root node. *
 ******************************************************************************************************************************************/

/*******************************************************************************************************************************************
 * @brief Performs a single left rotation at the given node X in a binary tree.                                                            *
 *                                                                                                                                         *
 *        It adjusts the pointers and updates the heights of the affected nodes.                                                           *
 *        (In this case the following violation: An insertion into the left subtree of the left child of X.)                               *
 *        Start at the point of insertion and travel up the tree, updating the balance information at every node on the path.              *
 *                                                                                                                                         *
 * @param X : tree node of binary tree                                                                                                     *
 * @return New root of the tree.                                                                                                           *
 *******************************************************************************************************************************************/
treeNode *SingleRotateLeft(treeNode *X);

/*******************************************************************************************************************************************
 * @brief Performs a single right rotation at the given node W in a binary tree.                                                           *
 *                                                                                                                                         *
 *        It adjusts the pointers and updates the heights of the affected nodes.                                                           *
 *        (In this case the following violation: An insertion into the right subtree of the right child of X.)                             *
 *        Start at the point of insertion and travel up the tree, updating the balance information at every node on the path.              *
 *                                                                                                                                         *
 * @param X : tree node of binary tree                                                                                                     *
 * @return New root of the tree.                                                                                                           *
 *******************************************************************************************************************************************/
treeNode *SingleRotateRight(treeNode *W);

/*******************************************************************************************************************************************
 * @brief Performs a double rotation with the left child at the given node Z.                                                              *
 *                                                                                                                                         *
 *        It first performs a single right rotation at the left child, and then a single left rotation at Z.                               *
 *        It adjusts the pointers and updates the heights of the affected nodes.                                                           *
 *        (In this case the following violation: An insertion into the right subtree of the left child of X.)                              *
 *        Start at the point of insertion and travel up the tree, updating the balance information at every node on the path.              *
 *                                                                                                                                         *
 * @param X : tree node of binary tree                                                                                                     *
 * @see SingleRotateLeft()                                                                                                                 *
 * @see SingleRotateRight()                                                                                                                *
 * @return New root of the tree.                                                                                                           *
 *******************************************************************************************************************************************/
treeNode *DoubleRotateWithLeft(treeNode *Z);

/*******************************************************************************************************************************************
 * @brief Performs a double rotation with the right child at the given node Z.                                                             *
 *                                                                                                                                         *
 *        It first performs a single left rotation at the right child, and then a single right rotation at Z.                              *
 *        It adjusts the pointers and updates the heights of the affected nodes.                                                           *
 *        (In this case the following violation: An insertion into the left subtree of the right child of X.)                              *
 *        Start at the point of insertion and travel up the tree, updating the balance information at every node on the path.              *
 *                                                                                                                                         *
 * @param X : tree node of binary tree                                                                                                     *
 * @see SingleRotateLeft()                                                                                                                 *
 * @see SingleRotateRight()                                                                                                                *
 * @return New root of the tree.                                                                                                           *
 *******************************************************************************************************************************************/
treeNode *DoubleRotateWithRight(treeNode *Z);

// treeNode *newNode(int _id);
// int getBalance(treeNode *N);
/********************************************************************************************************************************************************
 * @brief Inserts a new node with the value p into the binary tree root.                                                                                *
 *                                                                                                                                                      *
 *       Casts the value p to a Product type, and it uses the COD field of the Product struct/element for comparison.                                   *
 *       It recursively finds the appropriate position to insert the node and performs rotations if necessary to maintain the AVL balance property.     *
 *                                                                                                                                                      *
 * @param root : pointer to binary tree root. (Type treeNode*)                                                                                          *
 * @param p : pointer to product. (Type void*)                                                                                                          *
 * @see SingleRotateLeft()                                                                                                                              *
 * @see SingleRotateRight()                                                                                                                             *
 * @see DoubleRotateWithLeft()                                                                                                                          *
 * @see DoubleRotateWithRight()                                                                                                                         *
 * @return Pointer to the root of the modified tree. If p is a null pointer, it prints an error message and returns NULL.                               *
 ********************************************************************************************************************************************************/
treeNode *Insert(treeNode *root, void *p);

/********************************************************************************************************************************************************
 * @brief Creates a binary tree (AVL) from the elements in the linked list P.                                                                           *
 *                                                                                                                                                      *
 *        It iterates over the linked list and inserts each element into the tree using the Insert() function.                                          *
 *                                                                                                                                                      *
 * @param P : Products LL. (Type LG*)                                                                                                                   *
 * @see Insert()                                                                                                                                        *
 * @return Pointer to the root of the newly created binary tree. If P is a null pointer, it prints an error message and returns NULL.                   *
 ********************************************************************************************************************************************************/
treeNode *CreateTree(LG *P);

/********************************************************************************************************************************************************
 * @brief Destructs the binary tree root by recursively freeing the memory allocated for each node.                                                     *
 *                                                                                                                                                      *
 *         Starts from the root and recursively visits each node in post-order (left subtree, right subtree, current node).                             *
 *         It does nothing if root is a null pointer.                                                                                                   *
 *                                                                                                                                                      *
 * @param root : root node of binary tree                                                                                                               *
 * @see Insert()                                                                                                                                        *
 * @return None.                                                                                                                                        *
 ********************************************************************************************************************************************************/
void DestructTree(treeNode *root);

/************************************************************************************************************************************
 * @brief Calculates and returns the number of nodes in the subtree rooted at root.                                                 *
 *                                                                                                                                  *
 *        Recursively counts the nodes by adding one for the current node and the number of nodes in the left and right subtrees.   *
 *                                                                                                                                  *
 * @param root : node of binary tree                                                                                                *
 * @return The size of subtree or 0 if null pointer was given as root.                                                              *
 ************************************************************************************************************************************/
int SubTreeSize(treeNode *root);

/*****************************************************************************************************
 * @brief Helper function for selecting a random node from the binary tree.                          *
 *                                                                                                   *
 *        Recursively traverses the tree and finds the x-th node in an in-order traversal.           *
 *        It updates x as it traverses the tree, and when x becomes 1, it returns the current node   *
 *                                                                                                   *
 * @param root : node of binary tree                                                                 *
 * @param x : number of times to run the function, this is, the "position" of the element to get.    *
 * @return Random element or Null if root is a null pointer.                                         *
 *****************************************************************************************************/
treeNode *GetAux(treeNode *root, int *x);

/***************************************************************************************************
 * @brief Selects a random node from the binary tree root.                                         *
 *                                                                                                 *
 *        Calculates the number of nodes in the tree using the SubTreeSize function and            *
 *        generates a random number choice between 1 and the number of nodes.                      *
 *        It then calls the GetAux function to find the choice-th node in an in-order traversal.   *
 *                                                                                                 *
 * @param root : root of binary tree                                                               *
 * @see GetAux()                                                                                   *
 * @see SubTreeSize()                                                                              *
 * @return Random element or Null if root is a null pointer.                                       *
 ***************************************************************************************************/
treeNode *SelectRandomNode(treeNode *root);

/************************************************************
 * @brief Prints information about the given node root.     *
 *                                                          *
 * @param root : node of binary tree to be printed.         *
 * @return None.                                            *
 ************************************************************/
void ShowTreeNode(treeNode *root);

/*********************************************************************************************************************************
 * @brief Performs an in-order traversal of the binary tree root and prints the value of each node.                              *
 *                                                                                                                               *
 *        Recursively visits the nodes in the left subtree, then the current node, and finally the nodes in the right subtree.   *
 *                                                                                                                               *
 * @param root : root of binary tree to be printed.                                                                              *
 * @return None.                                                                                                                 *
 *********************************************************************************************************************************/
void InOrder(treeNode *root);

#endif // BINARYTREE_H_INCLUDED
