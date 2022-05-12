#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hbt.h"
#include "hbTree.h"
void destroyTree(Tnode* root); 


int main(int argc, char * argv[]) {

    //valid args
    if(!strcmp(argv[1], "-e"))
    {
        if(argc != 3) 
        {
            fprintf(stderr,"Inccorrect Number of Flags\n");
            return EXIT_FAILURE;
        }
        int size = 0;
        Tnode ** listTnodes = readEval(argv[2], &size);
        int valid = 1;
        if(listTnodes == NULL)
        {
            valid = -1;
            fprintf(stdout,"%d,0,0\n", valid);
            return EXIT_FAILURE;
        }
        //int i;
        //for(i = 0; i < size; i++)
        //{
        //    fprintf(stdout,"%d %d\n", listTnodes[i]->key, listTnodes[i]->balance);
        //}
        int index = 0;
        Tnode * preEvalTree = buildTree(listTnodes, size, &index);
        //printTree(preEvalTree, 0);
        fprintf(stdout,"%d,%d,%d\n", valid, !validBST(preEvalTree), !validHB(preEvalTree));   
        //destroyTree(preEvalTree);
        int j;
        for(j = 0; j < size; j++)
        {
            free(listTnodes[j]);
            listTnodes[j] = NULL;
        }
        free(listTnodes);
        //destroyTree(preEvalTree);
        return EXIT_SUCCESS;    
    }
    else if(!strcmp(argv[1], "-b"))
    {
        if(argc != 4) 
        {
            fprintf(stderr,"Inccorrect Number of Flags\n");
            return EXIT_FAILURE;
        }
        int tmpSize = 0;
        int output = 0;

        Tnode * balanceTree = readHB(argv[2], &tmpSize, &output);

        if(balanceTree == NULL)
        {
            fprintf(stdout, "%d\n", output);
            return EXIT_FAILURE; 
        }
        //printf("\n\nfinal tree\n");
        //printTree(balanceTree, 0);
        //printPre(balanceTree);
        writePreOrd(argv[3], balanceTree);
        fprintf(stdout, "%d\n", output); 
        destroyTree(balanceTree);
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "INVALID FLAG\n");
        return EXIT_FAILURE;       
    }
}


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