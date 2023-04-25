#include "Headers/binarytree.h"

extern void *ec_malloc(unsigned int size);
extern int getRandomInt(int min, int max);

int max( int a, int b)
{
    return a > b ? a : b;
}

int Height(treeNode *root)
{
    if(!root)
        return -1;
    return root->height;
}

treeNode *FindMin(treeNode *root)
{
    if(!root)
		return NULL;
	else if(root->left==NULL)
		return root;
	else return FindMin(root->left);
}

treeNode *FindMax(treeNode *root)
{
    if(!root)
		return NULL;
	else if(root->right==NULL)
		return root;
	else return FindMax(root->right);
}

treeNode *Find (treeNode *root, void *p)
{
    if (!root || !p)
		return NULL;
    int data = ((Product *)p)->COD;
	if (data < root->ID)
		return Find(root->left, data);
	else if (data>root->ID)
		return Find(root->right, data);
	return root;
}

treeNode *SingleRotateLeft(treeNode *X)
{
    treeNode *W = X -> left;
	X->left = W->right;
	W->right = X;
	X->height = max(Height(X->left), Height(X->right)) +1;
	W->height = max(Height(W->left), X->height) +1;
	return W; //New root
}
treeNode *SingleRotateRight(treeNode *W)
{
    treeNode *X = W -> right;
	W->right = X->left;
	X->left = W;
	W->height = max(Height(W->right), Height(W->left))+1;
	X->height = max(Height(X->right), W->height) +1;
	return X; //New root
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
    if(!p)
    {
        fatal("Null pointer given...");
    }
    //Product
    int _id = ((Product *)p)->COD;
    if (!root){
		root = (treeNode *) ec_malloc(sizeof (treeNode));
		if(!root) //mem error
        {
            fatal("in Inser(), allocation for treeNode failed... ");
            return NULL;
        }
		else
		{
		    root->ID = _id;
			root->Data=p;
			root->height =0;
			root->left = root->right = NULL;
		}
	}
	else if(_id<root->ID)
	{
		root->left = Insert (root->left,p);
		if( (Height(root->left) -Height(root->right)) == 2 ){
			if(_id<root->left->ID)
				root=SingleRotateLeft(root);
			else root = DoubleRotateWithLeft(root);
		}
	}
	else if(_id>root->ID){
		root->right = Insert (root->right,p);
		if( (Height(root->right) - Height(root->left)) == 2){
			if(_id<root->right->ID)
				root = SingleRotateRight(root);
			else root = DoubleRotateWithRight(root);
		}
	}
	//Else data is already in the tree. do nothing
	//update Height
	root->height = max(Height(root->left), Height(root->right)) +1;
	return root;
}

treeNode *CreateTree(LG *P)
{
     if(!P)
    {
        fatal("Null pointer given...");
    }
    treeNode *root = NULL;
    NODE *aux = P->head;
    while(aux)
    {
        root=Insert(root,aux->info);
        //break;
        aux = aux->next;
    }
    return root;
}

int SubTreeSize(treeNode *root) {
    if (!root) {
        return 0;
    }
    return 1 + SubTreeSize(root->left) + SubTreeSize(root->right);
}

treeNode *SelectRandomNode(treeNode *root)
{
    if(!root)
    {
        fatal("Null pointer given...");
    }
    int size = SubTreeSize(root);
    printf("[%d]\n\n", size);

    int choice = getRandomInt(1, size);
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



}
void InOrder(treeNode *root)
{
    if(root != NULL)
    {
        InOrder(root->left);
        printf("%d ---", root->ID);
        //ShowProduct(root->Data);
        InOrder(root->right);
    }
}
