#include "hbt.h"
#include "hbTree.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


Tnode ** readEval(char * filename, int * size)
{
    FILE * fh = fopen(filename, "rb");

    if(fh == NULL)
    {
        fprintf(stderr, "INVALID FILE\n");
        return NULL;
    }

    fseek(fh, 0, SEEK_END);
    *size = ftell(fh);

    if(!(*size))
    {
        fprintf(stderr, "EMPTY FILE\n");
        fclose(fh);
        return NULL;
    }

	fclose(fh);
	fh = fopen(filename, "rb");

    *size = *size / (sizeof(int) + sizeof(char));
    Tnode ** listTnodes = malloc((*size) * sizeof(Tnode));
    int i;
    for(i = 0; i < *size; i++)
    {
        Tnode * treeNode = malloc(sizeof(Tnode));

        int val, kids;
        val = 0;
        kids = 0;
        fread(&val, sizeof(int), 1, fh);
        fread(&kids, sizeof(char), 1, fh);
        //Add condition for if kids is < 0 || > 4
        if(kids < 0 || kids > 3)
        {
            fprintf(stderr, "INVALID FORMAT\n");
            return NULL;
        }
        treeNode -> key = val;
        treeNode -> balance = kids;
        treeNode -> right = NULL;
        treeNode -> left = NULL;
        listTnodes[i] = treeNode;
    }
    fclose(fh);
    return listTnodes;
}

Tnode * buildTree(Tnode ** listTnode, int size, int * index)
{
    if(*index < size)
    {
        int tmpInd = *index;
        if(listTnode[*index] -> balance == 3)
        {
            *index = *index + 1;
            listTnode[tmpInd] -> left = buildTree(listTnode, size, index);
            *index = *index + 1;
            listTnode[tmpInd] -> right = buildTree(listTnode, size, index);
            return listTnode[tmpInd];
        }
        else if(listTnode[*index] -> balance == 2)
        {
            *index = *index + 1;
            listTnode[tmpInd] -> left = buildTree(listTnode, size, index); 
            return listTnode[tmpInd];           
        }
        else if(listTnode[*index] -> balance == 1)
        {
            *index = *index + 1;
            listTnode[tmpInd] -> right = buildTree(listTnode, size, index);
            return listTnode[tmpInd];
        }
        else
        {
            return listTnode[tmpInd];
        }
    }
    return NULL;
}

int validBST(Tnode * root)
{
    if(root == NULL)
        return 0;
    
    if(root -> balance == 3)
    {
        if((root -> left -> key) > (root -> key))
        {
            return 1;
        }
        else if((root -> right -> key) < (root -> key))
        {
            return 1;
        }
        return (validBST(root->left) || validBST(root->right));
    }
    else if(root -> balance == 2)
    {
        if((root -> left -> key) > (root -> key))
        {
            return 1;
        }
        return (validBST(root->left));
    }
    else if(root -> balance == 1)
    {
        if((root -> right -> key) < (root -> key))
        {
            return 1;
        }
        return (validBST(root->right));
    }
    return 0;
}

int fHeight(Tnode *root)
{
    if(root == NULL)
        return 0;

    int maxLeft = fHeight(root->left); 
    int maxRight = fHeight(root->right);
    if(maxLeft > maxRight)
        return(maxLeft + 1);
    else
        return(maxRight + 1);

    return 0;
}

int validHB(Tnode *root)
{
    if(root == NULL)
        return 0;

    int left = 0;
    int right = 0;
    if(root -> left != NULL)
        left = fHeight(root->left);
    if(root -> right != NULL);
        right = fHeight(root->right);
     
    int diff = left - right;
    if((diff > 1) || (diff < -1))
        return 1;

    return validHB(root -> left) || validHB(root -> right);
}

//BUILDING HB BST


Tnode * readHB(char * filename, int * size, int * output)
{
    FILE * fh = fopen(filename, "rb");

    if(fh == NULL)
    {
        fprintf(stderr, "INVALID FILE\n");
        *output = -1;
        return NULL;
    }

    fseek(fh, 0, SEEK_END);
    *size = ftell(fh);

    if(!(*size))
    {
        fprintf(stderr, "EMPTY FILE\n");
        *output = -1;
        fclose(fh);
        return NULL;
    }

	fclose(fh);
	fh = fopen(filename, "rb");

    Tnode * treeNode = NULL;

    *size = *size / (sizeof(int) + sizeof(char));
    int i;
    for(i = 0; i < *size; i++)
    {
        int val;
        char instr;
        fread(&val, sizeof(int), 1, fh);
        fread(&instr, sizeof(char), 1, fh);
        //printf("%d,%c\n",val, instr);

        if(instr == 'i')
        {
            int match = 0;
            treeNode = insertNode(treeNode, val, &match);
        }
        else if(instr == 'd')
        {
             treeNode = deleteNode(treeNode, val);  
        }
        else
        {
            *output = 0;
            fprintf(stderr, "INVALID FORMAT\n");
            fclose(fh);
            return NULL;
        }
    }
    *output = 1;
    fclose(fh);

    return treeNode;
}

Tnode * createNode(int val)
{
    Tnode * treeNode = malloc(sizeof(Tnode));
    treeNode -> key = val;
    treeNode -> left = NULL;
    treeNode -> right = NULL;
    treeNode -> balance = 0;


    return treeNode;
}


void setBal(Tnode * root)
{
    if(root == NULL)
        return;
    int diff;
    int maxLeft = fHeight(root->left); 
    int maxRight = fHeight(root->right);
    diff = maxLeft - maxRight;
    root -> balance = diff;
}

Tnode * insertNode(Tnode * tree, int findKey, int * match)
{
    if(tree == NULL)
        return createNode(findKey); 

    if(findKey <= tree->key)
        tree -> left = insertNode(tree->left, findKey, match);
    else 
        tree -> right = insertNode(tree->right, findKey, match);

    Tnode * temp = rotation(tree);

    return temp;
}

Tnode * rotation(Tnode * tree)
{
    Tnode * temp = tree;
    setBal(tree);
	if((tree->balance < -1) && (tree->right != NULL))
	{
        if (tree -> right -> balance > 0)
            tree -> right = rotateCR(tree -> right);
        temp = rotateCCR(tree);
	}
    else if((tree -> balance > 1) && (tree -> left != NULL))
	{
        if (tree -> left -> balance < 0)
            tree -> left = rotateCCR(tree -> left);
        temp = rotateCR(tree);
	}
	return temp;
}

Tnode * rotateCCR(Tnode * root)
{
    Tnode * new_root = root -> right;
    root -> right = new_root -> left;
    new_root -> left = root;
    setBal(root);
    setBal(new_root);
    
    return new_root;
}

Tnode * rotateCR(Tnode * root)
{
    Tnode * new_root = root -> left;
    root -> left = new_root -> right;
    new_root -> right = root;
    setBal(root);
    setBal(new_root);

    return new_root;
}

Tnode * deleteNode(Tnode * tree, int key)
{
    if(tree == NULL)
        return NULL;
    else if(key < tree -> key)
        tree -> left = deleteNode(tree -> left, key);
    else if(key > tree -> key)
        tree -> right = deleteNode(tree -> right, key);
    else
    {
        if(!((tree -> left != NULL) && (tree -> right != NULL)))
        {
            Tnode * new_head = NULL;
            if((tree -> left == NULL) && (tree -> right == NULL))           
                free(tree);
            else if(tree -> right == NULL)
            {
                new_head = tree -> left;
                free(tree);
            }
            else if(tree -> left == NULL)
            {
                new_head = tree -> right;
                free(tree);
            }
            return new_head;
        }
        else if((tree -> left != NULL) && (tree -> right != NULL))
        {
            Tnode* trav = tree -> left;
            
            while(trav -> right != NULL)
            {
                trav = trav -> right;
            }
            trav->right=NULL;
            
            int hold = trav -> key;
            trav -> key = tree -> key;
            tree -> key = hold;
            
            tree -> left = deleteNode(tree -> left, key);
        }
    }

    setBal(tree);
    setBal(tree->left);
    setBal(tree->right);
    if(tree->left != NULL)
    {
        if ((tree->balance) > 1 && (tree->left->balance) >= 0)
            return rotateCR(tree);
        if ((tree->balance) > 1 && (tree->left->balance) < 0)
        {
            tree->left = rotateCCR(tree->left);
            return rotateCR(tree);
        }
    }
    if(tree->right != NULL)
    {
        if ((tree->balance) < -1 && (tree->right->balance) <= 0)
            return rotateCCR(tree);
        if ((tree->balance) < -1 && (tree->right->balance) > 0)
        {
            tree->right = rotateCR(tree->right);
            return rotateCCR(tree);
        }
    } 

    return tree;
}

void writePreOrd(char * filename, Tnode * head)
{
    if(head == NULL)
        return;
    FILE * fh = fopen(filename, "wb");
    helpPreOrd(fh, head);

    fclose(fh);
}

void helpPreOrd(FILE * fh, Tnode * head)
{
    if(head == NULL)
        return;
    int key = head->key;
    char kids;
    if((head -> left != NULL) && (head -> right != NULL))
    {
        fwrite(&key, sizeof(int), 1, fh);
        kids = 3;
        fwrite(&kids, sizeof(char), 1, fh);
    }
    else if(head -> left != NULL)
    {
        fwrite(&key, sizeof(int), 1, fh);
        kids = 2;
        fwrite(&kids, sizeof(char), 1, fh);
    }
    else if(head -> right != NULL)
    {
        fwrite(&key, sizeof(int), 1, fh);
        kids = 1;
        fwrite(&kids, sizeof(char), 1, fh);
    }
    else
    {
        fwrite(&key, sizeof(int), 1, fh);
        kids = 0;
        fwrite(&kids, sizeof(char), 1, fh);
    }
    helpPreOrd(fh, head->left);
    helpPreOrd(fh, head->right);
}

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

void printPre(Tnode * root)
{
     if (root == NULL)
          return;
 
     printf("%d\n ", root->key); 
 
     printPre(root->left); 
     printPre(root->right);
}