#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node // it denotes a node in the tree 
{
    int value ; // the key value which is stored in the tree
    struct node *left; // pointer to the left child of the node
    struct node *right; // pointer to the right child of the node
    int bal : 4; // negative if the left subtree is taller
                // positive if the right subtree is taller
                // zero if both the subtrees have equal height   

};

int comp_bal_factor(struct node *root); // this function computes the balance factor of the given node

struct node* add(struct node *root, int val); //this function adds the node to the tree and returns the modifies tree

struct node* find(struct node *root, int val); // this function finds the passed element and returns a pointer to it
//or returns a null value if the element is not found

struct node* del(struct node *root, int val); // this function searches for a key in the tree and if the key is found
//it deletes the key and returns the modified tree(VI) as the root of the tree can also change during the deletion operation

struct node * rotate(struct node* x, struct node * y, struct node* z, struct node *root);
void InOrder(struct node *a);

struct node* return_node(struct node *x);
