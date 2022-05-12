#include "shell_list.h"
#include "list_of_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
void print_List(Node*head);
Node* index_Node(Node* list, int index);
//void swap_Nodes(Node** list, int ind1, int ind2);
void swap_Nodes(Node** head, Node * n1, Node *p1, Node * n2, Node * p2);

Node *List_Load_From_File(char *filename)
{
    FILE* fh;
    if(!(fh = fopen(filename, "rb")))
    {
        return NULL;
    }
    int size;
    int i;
    //FILE* fh = fopen(filename, "rb");
	fseek(fh, 0, SEEK_END);
	size = ftell(fh);
	size = (size / sizeof(long));
    
    if(size == 0)
    {
        return NULL; 
    }
    
	fclose(fh);
	fh = fopen(filename, "rb");

	long buffer;
    Node * head;
    Node * temp = malloc(sizeof(Node));
    fread(&buffer, sizeof(long), 1,fh);
    temp->value = buffer;
    temp->next = NULL;
    head = temp;
	for(i = 1; i < size; i++)
	{
		fread(&buffer, sizeof(long), 1,fh);
        Node* temp2 = malloc(sizeof(Node));
        temp -> next = temp2;
        temp2 -> value = buffer;
        temp2 -> next = NULL;
    	temp = temp2;
  	} 
    temp = head;
    //print_List(temp);

	fclose(fh);
   
    return head;
}

int List_Save_To_File(char *filename, Node *list)
{
    FILE* fh = fopen(filename, "wb");
    Node * temp;
    temp = list;
    int size = 0;
    do
    {
        fwrite(&list->value, sizeof(long), 1, fh);
        list = list -> next;
        size ++;
    } while(list != NULL); 
    fclose(fh);
    
    return size;
}

Node *List_Shellsort(Node* list, long *n_comp)
{
    Node* temp = NULL; //to get size
    Node* head = NULL; //holds head of linked list
    Node* temp_r = NULL;
    Node* temp_ik = NULL;

    Node* temp_p1 = NULL;
    Node* temp_n1 = NULL;
    Node* temp_p2 = NULL;
    Node* temp_n2 = NULL;
    
    Node* temp_list = NULL;

    int i;
    int size = 0;
    temp = list;
    do
    {
        temp = temp -> next;
        size ++;
    } while(temp != NULL); 

    int halfway = size / 2;
    printf("Halfway : %ld", halfway);
    
    int start_val = (size - 1) / 3;
    int k, c;
    

    for(k = (start_val * 3) + 1; k > 0; k = (k-1) / 3)
    {
        int j, mInd;
        for(j = 0; j < size-k; j++)
        {
            i = j + k;
            temp_n1 = index_Node(list,j);
            while(i < size)
            {
                temp_n2 = index_Node(list, i);
                if(temp_n1 -> value < temp_n2 -> value)
                {
                    mInd = i;
                }
                i += k;
            }
            temp_n2 = index_Node(list, i);
            swap_Nodes(&list, )
            *n_comp = *n_comp + 1;        
        }
    } 
    //print_List(list);
    return list;
}

Node* index_Node(Node* head, int index)
{
    Node* current = NULL;
    current = head; 
  
    int count = 0; 
    while (current != NULL) { 
        if (count == index) 
            return (current); 
        count++; 
        current = current->next; 
    }
    return current; 
    
}

void swap_Nodes(Node** head, Node * n1, Node *p1, Node * n2, Node * p2)
{
    Node * temp = NULL;

    if (p1 != NULL)
    {
        p1 -> next = n2;
    }
    else
    {
        *head = n2;
    }

    p2 -> next = n1;
    temp = n2 -> next;
    n2 -> next = n1 -> next;
    n1 -> next = temp;
} 


void print_List(Node*head)
{
    Node* temp = NULL;
    temp = head;
    //print
    printf("\n\n\n");
    while(temp!=NULL)
    {
      printf(" %ld ",temp->value);
      temp=temp->next;
    }
    printf("\n\n\n");
}



