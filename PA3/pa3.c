#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "packed.h"
void free_list(Node *head);
void destroyTree(Tree* root); 


int main(int argc, char * argv[]) {

    if(argc != 5) 
    {
        fprintf(stderr,"Inccorrect Number of Flags\n");
        return EXIT_FAILURE;
    }
    //INPUT DATA
    int size = 0;
    Node * rev_pTree = readTree(argv[1], &size); //reverse post order

    //CREATE TREE
    int index = 0;
    Node * tempT = rev_pTree;
    Tree * bTree = buildTree(&tempT, size, &index);

    //PRINT PRE ORDER
    writePreOrd(argv[2], bTree);
    
    //TREE TO LL
    Node * bbList = tree2List(bTree);
    bbList = reverseLL(bbList, size);

    //PRINT DIMENSIONS OF TREE
    writeDim(argv[3], bbList);

    //SET CORDINATEDS OF TREE
    bTree -> cordx = bTree -> width;
    bTree -> cordy = bTree -> height;
    setCord(bTree, 0, 0);

    //WRITE CORDINATES OF TREE
    writeCord(argv[4], bTree);
    

    free_list(rev_pTree);
    destroyTree(bTree);
    free_list(bbList);
    return 0;
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