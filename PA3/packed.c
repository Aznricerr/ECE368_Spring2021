#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include "packed.h"


//READ IN DATA

Node * readTree(char * filename, int * size)
{
    FILE* fh;
    if(!(fh = fopen(filename, "r")))
    {
        return NULL;
    }

    Node * postTree = NULL;
    int val = 0;

    while(!feof(fh))
    {
        val = fgetc(fh);
        if(val == 'V' || val == 'H')
        {
            if(!feof(fh))
            {
                postTree = add_Node(postTree, val, 0, 0, 0);
                *size = *size + 1;
                val = fgetc(fh);
            }          
        }
        else
        {
            if(!feof(fh))
            {
                long pos = ftell(fh);
                int width, height, value;
                fseek(fh, pos-1, SEEK_SET); 
                fscanf(fh, "%d(%d,%d)\n", &value, &width, &height); 
                postTree = add_Node(postTree, 'N', value, width, height);
                *size = *size + 1;
            }           
        }

    }
    fclose(fh);
    //print_List(postTree);

    return postTree;
}

Node * add_Node(Node * list, char chr, int val, int width, int height)
{
    Node * new_head = malloc(sizeof(*new_head));
    if(list == NULL)
    {
        new_head -> next = NULL;
        new_head -> chr = chr; 
        new_head -> width = width; 
        new_head -> height = height;
        new_head -> val = val;
    }
    else
    {
        new_head -> next = list;
        new_head -> chr = chr; 
        new_head -> width = width; 
        new_head -> height = height;
        new_head -> val = val;
    }
    return new_head;
}


void print_List(Node*head)
{
    Node* temp = NULL;
    temp = head;
    printf("\n");
    while(temp!=NULL)
    {
      if(temp -> chr == 'N')
      {
          printf("%d,(%d,%d)\n", temp->val, temp->width, temp->height);
      }
      else
      {
          printf("%c,(%d,%d)\n",temp->chr, temp->width, temp->height);
      }
      temp = temp->next;
    }
    printf("\n");
} 

//END OF READING DATA

//BUILDING TREE

Tree * buildTree(Node** head, int size, int * index)
{
    Tree * root = NULL;

    if(*index < size)
    {
        root = malloc(sizeof(Tree));
        if((*head)->chr == 'H' || (*head)->chr == 'V')
        {
            root -> chr = 0;
            root -> left = NULL;
            root -> right = NULL;
            root -> chr = (*head)->chr;
            root -> width = (*head)->width;
            root -> height = (*head)->height;
            root -> val = (*head)->val;
            *index = *index + 1;
            *head = (*head) -> next;
            root -> right = buildTree(head, size, index);
            *head = (*head) -> next;
            root -> left = buildTree(head, size, index);
            if(root->chr == 'H')
            {
                root -> height = (root->left->height) + (root->right->height);
                if((root->left->width) > (root->right->width))
                {
                    root -> width = (root->left->width);
                }
                else
                {
                    root -> width = (root->right->width);
                }
            }
            else if(root->chr == 'V')
            {
                root -> width = (root->left->width) + (root->right->width);
                if((root->left->height) > (root->right->height))
                {
                    root -> height = (root->left->height);
                }
                else
                {
                    root -> height = (root->right->height);
                }               
            }
        }
        else
        {
            root -> left = NULL;
            root -> right = NULL;
            root -> chr = (*head)->chr;
            root -> width = (*head)->width;
            root -> height = (*head)->height;
            root -> val = (*head)->val;
        }
    }
    

    return root; 
} 

void writePreOrd(char * filename, Tree * head)
{
    if(head == NULL)
        return;
    FILE * fh = fopen(filename, "w");
    helpPreOrd(fh, head);

    fclose(fh);
}

void helpPreOrd(FILE * fh, Tree * head)
{
    if(head == NULL)
        return;

    if(head->chr == 'N')
    {
        fprintf(fh, "%d(%d,%d)\n", head->val, head->width, head->height);
    }
    else
    {
        fprintf(fh, "%c\n", head->chr);
    }
    helpPreOrd(fh, head->left);
    helpPreOrd(fh, head->right);
}


//FINISH BUILDING TREE AND FPRINTING TO FILE

//TRANSFER TO LINKED LIST AND SORT

Node * tree2List(Tree * tTree)
{

    Node * head = NULL;   
    if(tTree != NULL)
    {
        head = malloc(sizeof(*head));
        head -> val = tTree -> val;
        head -> chr = tTree -> chr;
        head -> height = tTree -> height;
        head -> width = tTree -> width;
        head -> next = tree2List(tTree -> right);
        Node * temp = head;
        while (temp -> next != NULL)
        {
            temp = temp -> next;
        }
        temp -> next = tree2List(tTree -> left);
    }

    return head;
}

//REVERSE

Node * reverseLL(Node * list, int size)
{
    int i;
    Node * prev = list;
    Node * curr = list -> next;
    Node * nextt = curr;
    prev -> next = NULL;
    for(i=1; i<size; i++)
    {
        nextt = nextt -> next;
        curr -> next = prev;
        prev = curr;
        curr = nextt;
    }
    list = prev;
    return list;
}



void writeDim(char * filename, Node * list)
{
    if(list == NULL)
        return;
    FILE * fh = fopen(filename, "w");

    Node * temp = list;
    while(temp!=NULL)
    {
      if(temp -> chr == 'N')
      {
          fprintf(fh,"%d(%d,%d)\n", temp->val, temp->width, temp->height);
      }
      else
      {
          fprintf(fh,"%c(%d,%d)\n",temp->chr, temp->width, temp->height);
      }
      temp = temp->next;
    }

    fclose(fh);
} 



//EXPORTED POST ORDER LL W/ DIM TO FILE

//TREE PRE ORDER & SET CORDINATES

void setCord(Tree * list, int floor, int leftbound)
{
    if(list -> chr == 'V' || list -> chr == 'H')
    {
        if(list -> chr == 'V')
        {
            (list->left->cordx) = leftbound;
            (list->right->cordx) = leftbound + (list->left->width);

            (list->right->cordy) = floor;
            (list->left->cordy) = floor;

            setCord(list->left, floor, leftbound);
            setCord(list->right, floor, (list->right->cordx));
        }
        else if(list -> chr == 'H')
        {
            (list->left->cordy) = floor + (list->right->height);
            (list->right->cordy) = floor;

            (list->right->cordx) = leftbound;
            (list->left->cordx) = leftbound;

            setCord(list->left, (list->left->cordy), leftbound);
            setCord(list->right, floor, leftbound);
        }
    }

}

void writeCord(char * filename, Tree * head)
{
    if(head == NULL)
        return;
    FILE * fh = fopen(filename, "w");
    helpwriteCord(fh, head);

    fclose(fh);
}

void helpwriteCord(FILE * fh, Tree * head)
{
    if(head == NULL)
        return;

    if(head->chr == 'N')
    {
        fprintf(fh, "%d((%d,%d)(%d,%d))\n", head->val, head->width, head->height,head->cordx,head->cordy);
    }

    helpwriteCord(fh, head->left);
    helpwriteCord(fh, head->right);
}


