#ifndef __HB_TREE__
#define __HB_TREE__
#include "hbt.h"
#include <stdio.h>

Tnode ** readEval(char * filename, int * size);
Tnode * buildTree(Tnode ** listTnode, int size, int * index);
int validBST(Tnode * root);
int fHeight(Tnode *head);
int validHB(Tnode *root);
Tnode * readHB(char * filename, int * size, int * output);
Tnode * createNode(int val);
Tnode * rotateCCR(Tnode * root);
Tnode * rotateCR(Tnode * root);
Tnode * insertNode(Tnode * tree, int findKey, int * match);
Tnode * deleteNode(Tnode * tree, int key);
Tnode * rotation(Tnode * tree);
void printTree(Tnode *root, int space);
void setBal(Tnode * root);
void writePreOrd(char * filename, Tnode * head);
void helpPreOrd(FILE * fh, Tnode * head);

void printPre(Tnode * root);
#endif