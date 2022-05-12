#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hbt.h"
#include "hbTree.h"
//void printTree(Tnode *root, int space);
void destroyTree(Tnode* root); 


int main(int argc, char * argv[]) {
    //char filename[] = "./pa4_examples/examples/tree0.b";
    char filename[] = "tree.b";
    int size = 0;
    Tnode ** listTnodes = readEval(filename, &size);
    int valid = 1;
    if(listTnodes == NULL)
    {
        valid = -1;
        printf("\n\n");
        fprintf(stdout,"%d,0,0\n", valid);
        return EXIT_FAILURE;
    }
    int i;
    for(i = 0; i < size; i++)
    {
        fprintf(stdout,"%d %d\n", listTnodes[i]->key, listTnodes[i]->balance);
    }
    printf("\n\n");
    int index = 0;
    Tnode * preEvalTree = buildTree(listTnodes, size, &index);
    printTree(preEvalTree, 0);
    printf("\n\n");

    fprintf(stdout,"%d,%d,%d\n", valid, !validBST(preEvalTree), !validHB(preEvalTree));

    char filename2[] = "./pa4_examples/examples/ops3.b";
    int tmpSize = 0;
    Tnode * balanceTree = readHB(filename2, &tmpSize); 
    printf("\n\nfinal tree\n");
    printTree(balanceTree, 0);
    printf("\n");
    printPre(balanceTree);

    //char filename3[] = "tree.b";
    //writePreOrd(filename3, balanceTree);

    destroyTree(balanceTree);
    destroyTree(preEvalTree);
    free(listTnodes);
    return 0;
}


/*
void printTree(Tnode *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return;
    
    space += 5; 
    printTree(root->right, space);
    int i;
    for (i = 5; i < space; i++) 
        printf(" ");
    fprintf(stdout, "%d\n", root -> key);
    printTree(root->left, space); 
} 
*/

void destroyTree(Tnode* root)
{
    if(root != NULL)
    {
        destroyTree(root -> left);
        destroyTree(root -> right);
        free(root);
    }
    root = NULL;
}