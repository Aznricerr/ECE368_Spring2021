#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "packed.h"
void printTree(Tree *root, int space);
void free_list(Node *head);
void destroyTree(Tree* root); 
void printCordTree(Tree *root, int space);
void print_List(Node*head);
void printPreCord(Tree * root);


int main(int argc, char * argv[]) {
    char filename[] = "./pa3_examples/examples/8.po";
    
    int size = 0;
    Node * rev_pTree = readTree(filename, &size); //reverse post order
    //printf("size : %d\n", size);


    int index = 0;
    Node * tempT = rev_pTree;
    Tree * bTree = buildTree(&tempT, size, &index);
    //printCordTree(bTree, 0);

    char filename1[] = "8.pre";
    writePreOrd(filename1, bTree);


    Node * bbList = tree2List(bTree);
    //print_List(bbList);
    bbList = reverseLL(bbList, size);
    //print_List(bbList);

    char filename2[] = "8.dim";
    writeDim(filename2, bbList);
    bTree -> cordx = bTree -> width;
    bTree -> cordy = bTree -> height;

    setCord(bTree, 0, 0);
    //printPreCord(bTree);

    char filename3[] = "8.pkg";
    writeCord(filename3, bTree);
    

    free_list(rev_pTree);
    destroyTree(bTree);
    free_list(bbList);
    return 0;
}

void printPreCord(Tree * root)
{
    if (root == NULL) 
        return; 
    
    if(root->chr=='N') 
        printf("%d(%d,%d)\n", root->val,root->cordx,root->cordy);
    //else
    //    printf("%c(%d,%d)\n", root->chr,root->cordx,root->cordy);
    printPreCord(root->left);
    printPreCord(root->right); 
}

void printTree(Tree *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
    
    space += 5;
    printTree(root->right, space);
    printf("\n"); 
    int i;
    for (i = 5; i < space; i++) 
        printf(" ");
    if(root->chr=='N') 
        printf("%d\n", root->val);
    else
        printf("%c\n", root->chr);
    printTree(root->left, space); 
} 

void printCordTree(Tree *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
    
    space += 5;
    printCordTree(root->right, space);
    printf("\n"); 
    int i;
    for (i = 5; i < space; i++) 
        printf(" ");
    if(root->chr=='N') 
        printf("%d,(%d,%d)\n", root->val, root->width, root->height);
    else
        printf("%c,(%d,%d)\n", root->chr, root->width, root->height);
    printCordTree(root->left, space); 
} 

void free_list(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void destroyTree(Tree* root)
{
    if(root != NULL)
    {
        destroyTree(root -> left);
        destroyTree(root -> right);
        free(root);
    }
    root = NULL;
}