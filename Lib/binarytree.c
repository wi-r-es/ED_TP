#include "Headers/binarytree.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

int Height(treeNode *root)
{
    if (!root)
        return -2;
    return root->height;
}

treeNode *FindMin(treeNode *root)
{
    if (!root)
        return NULL;
    else if (root->left == NULL)
        return root;
    else
        return FindMin(root->left);
}

treeNode *FindMax(treeNode *root)
{
    if (!root)
        return NULL;
    else if (root->right == NULL)
        return root;
    else
        return FindMax(root->right);
}

// ############################################
// NOT USED YET NEED TOO TEST!!!!!!!!!!!!   //#
treeNode *Find(treeNode *root, void *p) // #
{                                       // #
    if (!root || !p)                    // #
        return NULL;                    // #
    int data = ((Product *)p)->COD;     // #
    // void *data = &_data;                    //#
    if (data < root->ID)             // #
        return Find(root->left, p);  // #
    else if (data > root->ID)        // #
        return Find(root->right, p); // #
    return root;                     // #
} // #
// ############################################

treeNode *SingleRotateLeft(treeNode *X)
{
    treeNode *W = X->left;
    X->left = W->right;
    W->right = X;
    X->height = max(Height(X->left), Height(X->right)) + 1;
    W->height = max(Height(W->left), X->height) + 1;
    return W; // New root
}
treeNode *SingleRotateRight(treeNode *W)
{
    treeNode *X = W->right;
    W->right = X->left;
    X->left = W;
    W->height = max(Height(W->right), Height(W->left)) + 1;
    X->height = max(Height(X->right), W->height) + 1;
    return X; // New root
}
treeNode *DoubleRotateWithLeft(treeNode *Z)
{
    Z->left = SingleRotateRight(Z->left);
    return SingleRotateLeft(Z);
}
treeNode *DoubleRotateWithRight(treeNode *Z)
{
    Z->right = SingleRotateLeft(Z->right);
    return SingleRotateRight(Z);
}
/*
treeNode *newNode(int _id)
{
    treeNode* no = (treeNode*)ec_malloc(sizeof(treeNode));
    if(!no)
        fatal("While allocating memory");
    no->ID   = _id;
    no->left   = NULL;
    no->right  = NULL;
    no->height = 1;  // new node is initially added at leaf
    return(no);
}
*/

// Get Balance factor of node N
/*
int getBalance(treeNode *N)
{
    if (!N)
        return 0;
    return Height(N->left) - Height(N->right);
} */

treeNode *Insert(treeNode *root, void *p)
{
    if (!p)
    {
        fatal("Null pointer given...");
        return NULL;
    }
    // Product
    int _id = ((Product *)p)->COD;
    if (!root)
    {
        root = (treeNode *)ec_malloc(sizeof(treeNode));
        if (!root) // mem error
        {
            fatal("in Inser(), allocation for treeNode failed... ");
            return NULL;
        }
        else
        {
            root->ID = _id;
            root->Data = p;
            root->height = 0;
            root->left = root->right = NULL;
        }
    }
    else if (_id < root->ID)
    {
        root->left = Insert(root->left, p);
        if ((Height(root->left) - Height(root->right)) == 2)
        {
            if (_id < root->left->ID)
                root = SingleRotateLeft(root);
            else
                root = DoubleRotateWithLeft(root);
        }
    }
    else if (_id > root->ID)
    {
        root->right = Insert(root->right, p);
        if ((Height(root->right) - Height(root->left)) == 2)
        {
            if (_id < root->right->ID)
                root = SingleRotateRight(root);
            else
                root = DoubleRotateWithRight(root);
        }
    }
    // Else data is already in the tree. do nothing
    // update Height
    root->height = max(Height(root->left), Height(root->right)) + 1;
    return root;
}

treeNode *CreateTree(LG *P)
{
    if (!P)
    {
        fatal("Null pointer given...");
    }
    treeNode *root = NULL;
    NODE *aux = P->head;
    while (aux)
    {
        root = Insert(root, aux->info);
        // break;
        aux = aux->next;
    }
    return root;
}
void DestructTree(treeNode *root)
{
    if (!root)
        return;
    DestructTree(root->left);
    DestructTree(root->right);
    free(root);
}

int SubTreeSize(treeNode *root)
{
    if (!root)
    {
        return 0;
    }
    return 1 + SubTreeSize(root->left) + SubTreeSize(root->right);
}
treeNode *GetAux(treeNode *root, int *x)
{
    // printf("\nx->[%d]\n", *x);
    if (!root)
    {
        // printf("DEBUUUUUG XYZ \n");
        return NULL;
    }
    // printf("DEBUUUUUG YYY \n");
    if (*x == 1)
    {
        // ShowTreeNode(root);
        return root;
    }
    --(*x);

    treeNode *k = GetAux(root->left, x);
    if (k)
        return k;

    return GetAux(root->right, x);
}
treeNode *SelectRandomNode(treeNode *root)
{
    if (!root)
    {
        fatal("Null pointer given...");
        return NULL;
    }
    int nel = SubTreeSize(root);
    // printf("\n\t########[%d]\n\n", nel);
    int choice = getRandomInt(1, nel);
    // printf("\n\t########[%d]\n\n", choice);
    treeNode *aux = NULL;
    // while (aux == NULL)
    {
        // printf("DEBUUUUUG xxxx\n ");
        aux = GetAux(root, &choice);
    }
    return aux;
    // printf("\nNode selected -> ");
    // ShowTreeNode(aux);
    // printf("[%d]\n\n", size);
    /*
        int choice = getRandomInt(1, nel);
        int left_size = SubTreeSize(root->left);
        if (choice == left_size + 1)
        { // if choice  is equal to the left_size + 1 , the node is the current one
            return root;
        } else if (choice <= left_size)
        { //if choice is less than or equal to the size of the left subtree, the node to be selected must be in the left subtree.

            return SelectRandomNode(root->left);
        } else
        { ////if choice is less than or equal to the size of the left subtree, the node to be selected must be in the left subtree.
            return SelectRandomNode(root->right);
        }

    */
}
void ShowTreeNode(treeNode *root)
{
    if (root != NULL)
    {
        printf("Tree node->[%d]\n", root->ID);
    }
}
void InOrder(treeNode *root)
{
    if (root != NULL)
    {
        InOrder(root->left);
        printf("\n\t[%d]\n", root->ID);
        // ShowProduct(root->Data);
        InOrder(root->right);
    }
}
