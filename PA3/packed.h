#ifndef __PACKED_H__
#define __PACKED_H__

typedef struct _Tree{ 
    char chr; //type
    int width; //width
    int height; //length
    int val; //val of tree node
    int cordx; //x cordinates
    int cordy; //y cordinates
    struct _Tree * left; 
    struct _Tree * right; 
} Tree;

typedef struct _Node {
    char chr; //type
    int width; //width
    int height; //length
    int val; //val of tree node
    struct _Node *next;
} Node;
void print_List(Node*head);
Node * readTree(char * filename, int * size);
Node * add_Node(Node * list, char chr, int val, int width, int height);
Tree * buildTree(Node ** head, int size, int * index);

void writePreOrd(char * filename, Tree * head);
void helpPreOrd(FILE * fh, Tree * head);

Node * tree2List(Tree * tTree);
void writeDim(char * filename, Node * list);
Node * reverseLL(Node * list, int size);

void setCord(Tree * list, int floor, int leftbound);
void writeCord(char * filename, Tree * head);
void helpwriteCord(FILE * fh, Tree * head);

#endif