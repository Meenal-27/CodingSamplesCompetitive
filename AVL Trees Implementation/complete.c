
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
struct node * baladd(struct node*root,int val);//adding function keeping the balancing in mind
struct node *baldel(struct node *root, int val);//deleting function keeping the balancing in mind

struct node* return_node(struct node *x);
void InOrder(struct node *a);
// these are used for printing the entire tree inOrder sequence along with the balancefactors for each node
// for verifying the property of the AVL tree



int comp_bal_factor(struct node *root)
{
    int lh=0, rh=0;
    struct node *temp = root;
    while(temp!= NULL && temp->left!=NULL)
    {
        lh++;
        temp= temp->left;
    }
    temp = root;
    while(temp!= NULL && temp->right!=NULL)
    {
        rh++;
        temp= temp->right;
    }
    
    root->bal= lh-rh;
    return root->bal;
}

struct node* add(struct node *root, int val)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->value = val;
    new->left= NULL;
    new->right = NULL;
    comp_bal_factor(new);
    
    struct node *temp = root;
    struct node *par = NULL;
    while(temp!= NULL)
    {
        par = temp;
        if(val<= temp->value)
        {
            temp= temp->left;
        }
        else
        {
            temp= temp->right;
        }

    }
    if(par == NULL) root= new;
    else if(par->left== temp && par->value>=val)
    par->left = new;
    else 
    par->right = new;
    
    return root;

}

struct node* find(struct node *root, int val)
{
    struct node *temp = root;
    while(temp!= NULL && temp->value != val)
    {
        if(val< temp->value)
        {
            temp= temp->left;
        }
        else if(val>temp->value)
        {
            temp= temp->right;
        }
    }
    return temp;

}

struct node* del(struct node *root, int val)
{
    struct node *temp = root;
    struct node *par = NULL;

    while(temp!= NULL && temp->value!= val)
    {
        par = temp;
        if(val< temp->value)
        {
            temp= temp->left;
        }
        else if(val>temp->value)
        {
            temp= temp->right;
        }

    }
    
    if(temp == NULL) return root;
    else //par - holds the parent of the node to be actually spliced,temp holds node to be deleted
    // y denotes the node which is actually spliced out
    {
        struct node *y;
        if(temp->left == NULL || temp->right == NULL)
        y = temp;
        else // finds the in order successor
        {
            y = temp->right;
            par = temp;
            while(y!= NULL && y->left!= NULL)
            {
                par= y;
                y = y->left;
            }
             
        }

        struct node * x;
        if(y->right!= NULL)
        x = y->right;
        else x = y->left;
        if(par!= NULL)
        {
            if(par->right == y)
            par->right  = x;
            else 
            par->left = x;
        }
        
        
        else if(temp->right ==x || temp->left == x)
        root = x;

        if(y!= temp) temp->value = y->value;
        y->left = NULL;
        y->right = NULL;

        return root;
    }
}

struct node* pr(struct node *n, struct node *root)
{
    if(root == n || n == NULL || root == NULL) return NULL;
    while( root!= NULL && root->left!= n && root->right!= n)
    {
        if(n->value<root->value) root= root->left;
        else root = root->right;

    }
    return root;
}


struct node * rotate(struct node* x, struct node * y, struct node* z,struct node *root)
{
    struct node *a,*b, *c;
    if(x->value>= y->value  && x->value>= z->value)
    {
        c = x;
        if(y->value>=z->value)
        {
            b = y;
            a = z;
        }
        else
        {
            a = y;
            b = z;
        }
    }
    else if(y->value>= x->value  && y->value>= z->value)
    {
        c = y;
        if(x->value>=z->value)
        {
            b = x;
            a = z;
        }
        else
        {
            a = x;
            b = z;
        }
    }
    else
    {
        c = z;
        if(y->value>=x->value)
        {
            b = y;
            a = x;
        }
        else
        {
            a = y;
            b = x;
        }
    }
     // ordering x,y, z as a, b and c respectively

     struct node *t0, *t1, *t2, *t3;
     t0 = a->left;
     if(a->right!= b)
     t1 = a->right;
     else t1 = b->left;
     if(b->right!= c)
     t2= b->right;
     else t2 = c->left;
     t3 = c->right; 
    // assigning of the pointers to be done

    if(root == z)  
    {
        root = b;
    }
    
    struct node *p = pr(z,root);

    if(p!= NULL)
    {
        if(p->left == z) p->left = b;
        else p->right = b;
    }
    
    
    b->left = a; 
    b->right = c; 

    a->left = t0; 
    a->right = t1;
    c->left = t2;
    c->right = t3;

    //printf("%ud %ud %ud %ud %ud %ud %ud %ud %ud %ud",a,b,c,b->left,b->right,root,a->left,a->right,c->left,c->right);
    return root; // returns the tree which points to the root of the modifies tree
    // reallocation of the pointers which achieves the rotation to be achieved in the given 

}

struct node * baladd(struct node*root,int val)
{
    
    root = add(root, val);
    printf("added %d\n", val);
    
    struct node* x;
    x = find(root,val);
    
    //printf("%d\n",x->value);


    struct node *y = pr(x,root);
    
    //printf("%d\n",y->value);
    
    //(y== root)?printf("Yes\n"):printf("No\n");

    struct node *z = y;
    while(y!= root && y!= NULL)
    {
        
        z = pr(y,root);
        //printf("%ud\n",z);
        
        //printf("%d\n",z->value);
        comp_bal_factor(z);

        //printf("%d\n",z->bal);
        if(z->bal>1 || z->bal<-1)
        {
            root = rotate(x,y,z,root);
            
            //InOrder(root);
            //printf("Rotation done!\n");
        }
        x = y;
        y = z; 
        
    }
    return root;   
}


struct node *baldel(struct node *root, int val)
{
    struct node *temp = root;
    struct node *par = NULL;

    while(temp!= NULL && temp->value!= val)
    {
        par = temp;
        if(val< temp->value)
        {
            temp= temp->left;
        }
        else if(val>temp->value)
        {
            temp= temp->right;
        }

    }
    
    if(temp == NULL) return root; //par - holds the parent of the node to be actually spliced,temp holds node to be deleted
    // y denotes the node which is actually spliced out
    
    struct node *y;
    if(temp->left == NULL || temp->right == NULL)
    y = temp;
    else // finds the in order successor
    {
        y = temp->right;
        par = temp;
        while(y!= NULL && y->left!= NULL)
        {
            par= y;
            y = y->left;
        }
             
    }

    struct node * x;
    if(y->right!= NULL)
    x = y->right;
    else x = y->left;
    if(par!= NULL)
    {
        if(par->right == y)
        par->right  = x;
        else 
        par->left = x;
    }
        
        
    else if(temp->right ==x || temp->left == x)
    root = x;

    if(y!= temp) temp->value = y->value;
    y->left = NULL;
    y->right = NULL;
    
    
    printf("%d deleted\n",val);
    
    struct node *x1,*y1,*z1;
    x= (x== NULL)? par: x;
    if(x!= NULL && (comp_bal_factor(x)>1 || comp_bal_factor(x)<-1))
    {
        //printf("1\n");
        z1 =x;
        if(comp_bal_factor(z1)>0)
        y1 = z1->left;
        else y1 = z1->right;
        if(comp_bal_factor(y1)>0)
        x1 = y1->left;
        else z1= y1->right;
    }
    else
    {
        //printf("2\n");
        z1 =pr(par,root);
        if(comp_bal_factor(z1)>1 || comp_bal_factor(z1)<-1)
        {
            if(comp_bal_factor(z1)>0)
            y1 = z1->left;
            else y1 = z1->right;
            if(comp_bal_factor(y1)>0)
            x1 = y1->left;
            else z1= y1->right;
        }
        else
        {
            x1= par; 
            y1 = pr(x1,root);
            z1 = pr(y1,root);
        }
    }
    while(y1!= root && y1!= NULL)
    {
        comp_bal_factor(z1);
        if(z1->bal>1 || z1->bal<-1)
        {
            if(z1 == root)
            root = rotate(x1,y1,z1,root);
            else rotate(x1,y1,z1,root);
            printf("%d Rotation done!\n");
        }
        
        x1 = y1;
        y1 = z1;
        z1 = pr(y1,root);
        
    }
    return root;   
}


struct node* return_node(struct node *x)
{
    struct node* new = (struct node*)malloc(sizeof(struct node));
    new->value= x->value;
    new->left= x->left;
    new->right= x->right;
    new->bal = x->bal;
    return new;
}


void InOrder(struct node *a)
{
    int top = -1;
    struct node *stack[100];
    comp_bal_factor(a);
    stack[++top]= return_node(a);
    while(top>-1)
    {
        if(stack[top]->left!= NULL || stack[top]->right!= NULL)
        {
            if(stack[top]->right!= NULL)
            {
                struct node * temp = stack[top];
                comp_bal_factor(temp->right);
                stack[top] = return_node(temp->right);
                stack[++top] = temp;
                temp->right = NULL;
            }
            if(stack[top]->left!= NULL)
            {
                struct node * temp = stack[top];
                comp_bal_factor(temp->left);
                stack[++top] = return_node(temp->left);
                temp->left= NULL;
            }
        }
        else
        {
            printf("key : %d bf :%d\n",stack[top]->value,stack[top]->bal);
            top--;
        }
    }

}


void main() //  used for testing the above code by using the InOrder function for printing the elements of the tree
{
    
    struct node* tree = (struct node*)malloc(sizeof(struct node));
    tree->value =1;
    tree->left = NULL;
    tree->right= NULL;
    tree->bal = 0;

    tree = baladd(tree,2);
    tree = baladd(tree,3); 
    tree= baladd(tree,4);
    tree= baladd(tree,5);
    tree= baladd(tree,6);
    tree = baladd(tree,7);
    tree= baladd(tree,8);
    tree = baladd(tree,9);
    tree = baladd(tree,10);
    tree = baladd(tree,11);
    tree = baladd(tree,12);
    tree = baladd(tree,13);
    tree = baladd(tree,14);
    tree = baladd(tree,15);
    tree = baladd(tree,16);
    tree = baladd(tree,17);
    tree = baladd(tree,18);
    tree = baladd(tree,19);
    tree = baladd(tree,20);
    tree = baladd(tree,21);
    tree = baladd(tree,22);
    tree = baladd(tree,23);
    tree = baladd(tree,24);
    tree = baladd(tree,25);
    tree = baladd(tree,26);
    tree = baladd(tree,27);
    tree = baladd(tree,28);
    tree = baladd(tree,29);
    tree = baladd(tree,30);
    tree = baladd(tree,31);
    InOrder(tree);
    
    tree = baldel(tree,26);
    InOrder(tree);

     tree = baldel(tree,27);
    InOrder(tree);

    tree = baldel(tree,28);
    InOrder(tree);

    tree = baldel(tree,29);
    InOrder(tree);

    tree = baldel(tree,30);
    InOrder(tree);
    
    tree = baldel(tree,31);
    InOrder(tree);

    tree = baldel(tree,25);
    InOrder(tree);

     tree = baldel(tree,24);
    InOrder(tree);



}