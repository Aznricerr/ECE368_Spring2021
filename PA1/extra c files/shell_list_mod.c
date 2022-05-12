#include "shell_list.h"
#include "list_of_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
void print_List(Node*head);
Node* index_Node(Node* list, int index);
//void swap_Nodes(Node** list, int ind1, int ind2);
void swap_Nodes(Node** head, Node * n1, Node *p1, Node * n2, Node * p2);
Node * shell_insort(Node *head, int k, int size, long * n_comp);
void selectionSort(Node** head);

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
    ////FIX THIS
    FILE* fh = fopen(filename, "wb");
    Node * temp;
    temp = list;
    int size = 0;
    do
    {
        fwrite(&(list->value), sizeof(long), 1, fh);
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
    int start_val = 1;
    do
    {
        start_val = (start_val * 3) + 1;
    }while(start_val < size);
    start_val = (start_val - 1) / 3;
    int k, j, l;

    for(k = start_val; k > 0; k = (k-1) / 3)
    {
        do
        {
            j = 0;
            Node * p_tmp = list;
            Node * pp_tmp = NULL;
            Node * pc_tmp = index_Node(list, k-1);
            Node * c_tmp = pc_tmp -> next;
            for(l = k; l < size ; l++)
            {
                if(p_tmp -> value > c_tmp -> value)
                {
                    swap_Nodes(&list, p_tmp, pp_tmp, c_tmp, pc_tmp);
                    if(k == 1)
                    {
                        Node * hold1 = p_tmp;
                        p_tmp = c_tmp;
                        c_tmp = hold1;
                        pc_tmp = p_tmp;
                    }
                    else
                    {
                        Node * hold1 = p_tmp;
                        p_tmp = c_tmp;
                        c_tmp = hold1;                       
                    }
                    j = 1;
                }
                if(pp_tmp == NULL)
                {
                    pp_tmp = p_tmp;
                }
                else
                {
                    pp_tmp = pp_tmp -> next;
                }
                p_tmp = p_tmp -> next;
                pc_tmp = pc_tmp -> next;
                c_tmp = c_tmp -> next;
                *n_comp = *n_comp + 1;
            }


        }while(j == 1);
        
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



