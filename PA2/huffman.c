#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "h_man.h"

Node* index_Node(Node* list, int index);
#define ASCIIMAX 256

Node *read_file(char *filename, long ** arr_info)
{
    FILE* fh;
    if(!(fh = fopen(filename, "rb")))
    {
        return NULL;
    }

    int size;
	fseek(fh, 0, SEEK_END);
	size = ftell(fh);
    fseek(fh, 0, SEEK_SET);
    if(size == 0)
    {
        fclose(fh);
        return NULL;
    }

    Node * huff_list = NULL;
    unsigned char val = 'a';
    long jjj;

    long * arrl = malloc(3 * sizeof(long));
    fread(&jjj,sizeof(long), 1, fh);
    arrl[0] = jjj;
    fread(&jjj,sizeof(long), 1, fh);
    arrl[1] = jjj;
    fread(&jjj,sizeof(long), 1, fh);
    arrl[2] = jjj;

    *arr_info = arrl;

    fseek(fh, 0, SEEK_SET);

    while(!feof(fh))
    {
        val = fgetc(fh);

        if(!feof(fh))
        {
            huff_list = add_Node(huff_list, val);
        }
    }
    fclose(fh);

    return huff_list;
}


Node * add_Node(Node * head, char chr) 
{
    Node * newNode = malloc(sizeof(*newNode));

    if (head == NULL) 
    {
        head = newNode;
        head -> next = NULL;
        head -> value = chr;
        head -> freq  = 1;

        return(head);
    }

    Node * temp = head;
    Node * temp2 = NULL;

    while(temp != NULL) 
    {
        if (temp -> next == NULL)
        {
            temp2 = temp; 
        }
        temp = temp -> next;
        
    } 
    temp2 -> next = newNode; 
    newNode -> next = NULL;
    newNode -> value = chr;
    newNode -> freq = 1;

    return(head);
}

char *find_topology(Node *head, long * size, int * index, long * log_arr, char * filename)
{
    Node * hold = NULL;
    int top_byte;
    FILE* fh = fopen(filename, "wb");
    

    int index_long = sizeof(long) * 1;

    hold = index_Node(head, index_long);
    top_byte = log_arr[1];

    index_long = sizeof(long) * 3; //begining of topology
    *index =24 + top_byte; 

    char * top = malloc(top_byte * 3 * sizeof(char));
    hold = index_Node(head, index_long);
    int find_top = 0; //boolean
    int top_int = 0;

    int asc_ind = 7;

    int j,i,k,v,p, dec;
    int *bit_arr = (int*) malloc(8 * sizeof(int));
    for(j = 0; j < top_byte; j++)
    {
        int *arr = (int*) malloc(8 * sizeof(int));
        unsigned char b = hold -> value;
        v = 0;
        for(i = 7; i >= 0; i--)
        {
            k = b >> i;
            if (k & 1)
                arr[v] = 1;
            else
                arr[v] = 0;
            v++;
       }
       int ind = 7;
       while(ind >= 0)
       {
            if ((j == (top_byte - 1)) && (find_top == 0))
            {
                ind = -1;
            }
            else if((j != (top_byte - 1)) && (find_top == 0))
            {
                if(arr[ind] == 0)
                {
                    char zero = 48;
                    fwrite(&zero, sizeof(char), 1, fh);
                    //top[top_int] = 48;
                    top_int ++;
                }
                else if(arr[ind] == 1)
                {
                    char one = 49;
                    fwrite(&one, sizeof(char), 1, fh);
                    //top[top_int] = 49;
                    top_int ++;
                    find_top = 1;
                }
                ind --;
            }
            else if(find_top == 1)
            {
                bit_arr[asc_ind] = arr[ind];
                asc_ind --;
                ind --;
                if(asc_ind == -1)
                {
                    find_top = 0;
                    asc_ind = 7;
                    dec = 0;
                    for(p = 7; p >= 0; p--)
                    {
                        if(bit_arr[p])
                        {
                            dec = dec + (1 << abs(p - 7));
                        }
                    }
                    fwrite(&dec, sizeof(char), 1, fh);
                    //top[top_int] = dec;
                    top_int ++;
                }
            }
       }
       
       hold = hold -> next;
       free(arr);
    }
    *size = top_int;

    free(bit_arr);
    fclose(fh);

    return top;
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

void write_top(char * filename, char * string, int size)
{
    FILE* fh = fopen(filename, "wb");

    //Insert NULL Case HERE<><>
    //
    //
    int i;
    for(i = 0; i < size; i++)
    {
        fputc(string[i], fh);
    }

    //fputs(string, fh);
    fclose(fh);
}

Tree * help_bTree(char * filename)
{
    FILE * fh = fopen(filename, "rb");

    Tree * root = build_Tree(fh);
    fclose(fh);

    return root;
}


Tree *build_Tree(FILE * fh)
{
    Tree * root = malloc(sizeof(Tree));

    if(!feof(fh))
    {
        unsigned char val = 'a'; 
        val = fgetc(fh);
        //fprintf(stdout, "val:%c\n", val);
        if(val == 48)
        {
            root -> chr = 0;
            root -> left = NULL;
            root -> right = NULL;
            //*index = *index + 1;
            root -> left = build_Tree(fh);
            root -> right = build_Tree(fh);
        }
        else if(val == 49)
        {
            val = fgetc(fh);
            //fprintf(stdout, "val:%c\n", val);
            root -> chr = val;
            root -> left = NULL;
            root -> right = NULL;
            //*index = *index + 2;
        }
    }
    

    return root;
}
/*
Tree *build_Tree(char * top, long size, long * index)
{
    Tree * root = malloc(sizeof(Tree));

    if(*index < size)
    {
        if(top[*index] == 48)
        {
            root -> chr = 0;
            root -> left = NULL;
            root -> right = NULL;
            *index = *index + 1;
            root -> left = build_Tree(top, size , index);
            root -> right = build_Tree(top, size, index);
        }
        else if(top[*index] == 49)
        {
            root -> chr = top[*index + 1];
            root -> left = NULL;
            root -> right = NULL;
            *index = *index + 2;
        }
    }
    

    return root;
}
*/
char *decode_stream(Tree * head, Node * start, int node_start, int * size, long * log_arr, long * bit_input)
{
    Node * hold = NULL;
    int total_bytes = log_arr[0];
    hold = index_Node(start, node_start);
    int find_ori = log_arr[2];
    long bits_decode = total_bytes - log_arr[1] - 24;
    *size = find_ori;
    char * decoded = malloc(find_ori * sizeof(char));

    int j,i,k,v;
    v = 0;
    int *arr = (int*) malloc(8 * bits_decode * sizeof(int));
    for(j = 0; j < bits_decode; j++)
    {
        v = ((j+1) * 8) - 1;
        unsigned char b = hold -> value;
        for(i = 7; i >= 0; i--)
        {
            k = b >> i;
            if (k & 1)
                arr[v] = 1;
            else
                arr[v] = 0;
            v--;
       }
       
                
       hold = hold -> next;     
    }
    int l;
    int dec = 0;
    Tree * temp = head;
    for(l = 0; l < (bits_decode * 8); l++)
    {
        if(((temp -> left) == NULL) && ((temp ->right) == NULL))
        {
            decoded[dec] = temp -> chr;
            //printf("dec: %c\n", decoded[dec]);
            dec ++;
            temp = head;
        }
        if(arr[l] == 0)
        {
            temp = temp -> left;
        }
        else if(arr[l] == 1)
        {
            temp = temp -> right;
        }
        if(dec == (find_ori))
        {
            *bit_input = l;
            l = (bits_decode * 8);
        }
    }


    free(arr);

    return decoded;
}


void printTree(Tree *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
    
    space += 5;
    printTree(root->left, space);
    printf("\n"); 
    int i;
    for (i = 5; i < space; i++) 
        printf(" "); 
    printf("%c\n", root->chr);
    printTree(root->right, space); 
} 

void write_freq(char * filename, char * file_read)
{
    FILE * fh = fopen(filename, "wb");
    FILE * fr = fopen(file_read, "rb");
    int write = 0;
    if (fh == NULL) 
    {
        fprintf(stderr, "fopen fail\n");
        return;
    }


    unsigned char val = 'a';
    val = fgetc(fr);

    int i = 0;
    long zero = 0;
    if (val == '\0')
    {
        while (i < ASCIIMAX)
        {
            fwrite(&zero, sizeof(long), 1, fh);
            i++;
        }
        fclose(fr);
        fclose(fh);
        return;
    }

    int j;
    long count;
    while(i < ASCIIMAX) 
    {
        fseek(fr, 0, SEEK_SET);
        count = 0;
        while(!feof(fr))
        {
            val = fgetc(fr);
            if(val == i)
            {
                if(!feof(fr))
                    count += 1;
            }
        }
        if (count > 0)
        {
            write = fwrite(&count, sizeof(long), 1, fh); 
            i++;
        }
        else
        {
            fwrite(&zero, sizeof(long), 1, fh);
            i++;
        }

    }
    fclose(fr);
    fclose(fh);

}



/*
void write_freq(char * filename, char *decoded, int size)
{
    FILE * fh = fopen(filename, "wb");
    int write = 0;
    if (fh == NULL) 
    {
        fprintf(stderr, "fopen fail\n");
        return;
    }

    int i = 0;
    long zero = 0;
    if (decoded[0] == '\0')
    {
        while (i < ASCIIMAX)
        {
            fwrite(&zero, sizeof(long), 1, fh);
            i++;
        }
        fclose(fh);
        return;
    }

    int j;
    long count;

    while(i < ASCIIMAX) 
    {
        count = 0;
        for(j = 0; j < size; j++)
        {
            if(decoded[j] == i)
            {
                count += 1;
            }
        }
        if (count > 0)
        {
            write = fwrite(&count, sizeof(long), 1, fh); 
            i++;
        }
        else
        {
            fwrite(&zero, sizeof(long), 1, fh);
            i++;
        }

    }

    fclose(fh);

} */

Node *top_data(char * filename, int size)
{
    FILE * fh = fopen(filename, "rb");
    Node * huff_list = NULL;
    Node * freq_ch = NULL;
    int i;
    unsigned char val = 'a';
    for(i = 0; i < size; i++)
    {
        val = fgetc(fh);
        if(!feof(fh))
        {
            freq_ch = node_exist(huff_list, val);
            if(freq_ch == NULL)
            {
                huff_list = add_Node(huff_list, val);
            }
            else
            {
                (freq_ch -> freq)++;
            }
        }
    }
    fclose(fh);

    sort(&huff_list);

    return huff_list;
}

Node *node_exist(Node *head, char val)
{
    Node * current = NULL;
    current = head;
    while (current != NULL) { 
        if (val == (current ->value)) 
            return (current); 
        current = current->next; 
    }
    return current;
}

void sort(Node **h)
{
    //JUST SWITCHED VALUES
    int  a;
    char k;

    Node *temp1 = NULL;
    Node *temp2 = NULL;

    for(temp1 = *h; temp1 != NULL; temp1 = temp1 -> next)
    {
        for(temp2 = temp1 -> next;temp2 != NULL;temp2 = temp2 -> next)
          { 
            if(temp2 -> freq < temp1 -> freq)
            {
                a = temp1 -> freq;
                k = temp1 -> value;
                temp1 -> freq = temp2 -> freq;
                temp1 -> value = temp2 -> value;
                temp2 -> freq = a;
                temp2 -> value = k;
            }
            else if(temp2 -> freq == temp1 -> freq)
            {
                if(temp2 -> value < temp1 -> value)
                {
                    a = temp1 -> freq;
                    k = temp1 -> value;
                    temp1 -> freq = temp2 -> freq;
                    temp1 -> value = temp2 -> value;
                    temp2 -> freq = a;
                    temp2 -> value = k;
                }
            }
        }
    }
}

Tree *build_huff(Node * tp_data, long *char_amt)
{
    Node * temp = NULL;
    temp = tp_data;

    int size = 0;
    while(temp != NULL)
    {
        size ++;
        temp = temp -> next;
    }
    *char_amt = size;

    Tree ** forest = malloc(size * sizeof(Tree));
    Tree * for_root = NULL;

    temp = tp_data;
    
    int i;
    for(i = 0; i < size; i++)
    {
        Tree *root = NULL;
        root = add_TreeNode(temp->value, temp ->freq);
        temp = temp ->next;

        forest[i] = root; 
    }
    int j = 0;
    Tree * zero_tree = malloc(sizeof(Tree));
    zero_tree -> left = NULL;
    zero_tree -> right = NULL;
    zero_tree ->freq = 0;
    zero_tree ->depht = 0;
    zero_tree ->chr =0;
    zero_tree ->creat_time = -1;
    forest = sortForest(forest, size);
    while(j + 1< size)
    {
        forest[j] = merge_TreeNodes(forest[j], forest[j+1], j);
        forest[j+1] = zero_tree;
        forest = sortForest(forest, size);
        j = j + 1;
    }

    for_root = forest[size-1];
    free(forest);
    free(zero_tree);
    return for_root;
}

Tree *add_TreeNode(char val, long freq)
{
    Tree * temp = malloc(sizeof(Tree));
    temp -> chr = val;
    temp -> freq = freq;
    temp -> depht = 1;
    temp -> left = NULL;
    temp -> right = NULL; 

    return temp;
}

Tree *merge_TreeNodes(Tree *ltree, Tree *rtree, int crt_time)
{
    Tree * temp = malloc(sizeof(Tree));
    temp -> chr = 0;
    temp -> freq = (ltree -> freq) + (rtree -> freq);
    temp -> left = ltree;
    temp -> right = rtree;
    temp -> creat_time = crt_time;
    if(ltree -> depht > rtree -> depht)
    {
        temp -> depht = (ltree -> depht) + 1;
        //temp -> right -> depht =  (ltree -> depht);
    }
    else
    {
        temp -> depht = (rtree -> depht) + 1;
        //temp -> left -> depht =  (rtree -> depht);
    } 

    return temp;
}

Tree **sortForest(Tree **forest, int size)
{
    Tree **new_forest = NULL;
    new_forest = forest;
    int i;
    for(i=0; i<size-1; i++)
	{
		int Imin = i;
        int j;
		for(j=i+1; j<size; j++)
		{
			if( (new_forest[j] -> freq) < (new_forest[Imin] -> freq))
			{
				Imin = j;
			}
            /*else if((new_forest[j] -> freq) == (new_forest[Imin] -> freq) && (new_forest[j] -> depht) < (new_forest[Imin] -> depht))
            {
                Imin = j;
            } */
            else if((new_forest[j] -> freq) == (new_forest[Imin] -> freq))
            {
                if((new_forest[j] -> chr != 0) && (new_forest[Imin] -> chr == 0))
                {
                    Imin = j;
                }
                else if((new_forest[j] -> chr != 0) && (new_forest[Imin] -> chr != 0))
                {
                    Tree *n1 = NULL;
                    Tree *n2 = NULL;
                    n1 = new_forest[j];
                    n2 = new_forest[Imin];
                    if(n1 -> chr < n2 -> chr)
                    {
                        Imin = j;
                        //printf("create time %d, key : %c \n", new_forest[j] -> creat_time, new_forest[j] ->chr );
                    }
                }
                else if((new_forest[j] -> chr == 0) && (new_forest[Imin] -> chr != 0))
                {
                    Imin = Imin;
                }
                else if((new_forest[j] -> creat_time) < (new_forest[Imin] -> creat_time))
                {
                    Imin = j;
                    //printf("create time %d, key : %c \n", new_forest[j] -> creat_time, new_forest[j] ->chr );
                }
            }
		}
		Tree *temp = new_forest[Imin];
		new_forest[Imin] = new_forest[i];
		new_forest[i] = temp;
	}
    return new_forest;
}

Tree * findsKey(Tree * root)
{
    Tree * trav = root;
    if((trav -> right == NULL) && (trav -> left == NULL))
    {
        return trav;        
    }
    else if((trav -> right == NULL) && (trav -> left != NULL))
    {
        return findsKey(trav -> left);
    }
    else if((trav -> right != NULL) && (trav -> left == NULL))
    {
        return findsKey(trav -> right);
    }
    else if(trav -> right -> depht > trav -> left -> depht)
    {
        return findsKey(trav -> right);
    }
    else if(trav -> right -> depht < trav -> left -> depht)
    {
        return findsKey(trav -> left);
    }
    else if(trav -> right -> depht == trav -> left -> depht)
    {
        return findsKey(trav -> left);
    }
    return trav;
}

void decode_writeTree(char * filename, Tree * root)
{
    FILE * fh = fopen(filename, "wb");
    decode_htree(root, fh);

    fclose(fh);
}

void decode_htree(Tree *root, FILE * fh)
{
    Tree * temp = NULL;
    temp = root;
    if((temp -> right != NULL) && (temp -> left != NULL) && (temp != NULL))
    {
        //Tdec[*index] = 48;
        //*index = *index + 1;
        char zero = 48;
        fwrite(&zero, sizeof(char), 1, fh);
        decode_htree(temp -> left, fh);
        decode_htree(temp -> right, fh);
    }
    else if((temp -> right == NULL) && (temp -> left == NULL) && (temp != NULL))
    {
        //Tdec[*index] = 49;
        //*index = *index + 1;
        char one = 49;
        fwrite(&one, sizeof(char), 1, fh);
        fwrite(&(temp->chr), sizeof(char), 1, fh);
        //Tdec[*index] = temp ->chr;
        //*index = *index + 1;
    }
    return;
}

void find_bits(Tree *root, long *hbits,long dep)
{
    Tree * temp = NULL;
    temp = root;
    if((temp -> right != NULL) && (temp -> left != NULL) && (temp != NULL))
    {
        find_bits(temp -> left, hbits, dep + 1);
        find_bits(temp -> right, hbits, dep + 1);
    }
    else if((temp -> right == NULL) && (temp -> left == NULL) && (temp != NULL))
    {
        *hbits = *hbits + (dep * temp->freq);
    }
    return;
}

void write_vals(char *filename, long in_val, long huff_val, long amt)
{
    FILE* fh = fopen(filename, "wb");

    //Insert NULL Case HERE<><>
    //
    //

    long val = 0;
    int val1 = 0;
    val = in_val / amt;
    val1 = (int)(in_val % amt);
    fwrite(&val, sizeof(long), 1, fh); 
    fwrite(&val1, sizeof(int), 1, fh); 

    val = huff_val / amt;
    val1 = (int)(huff_val % amt);
    fwrite(&val, sizeof(long), 1, fh); 
    fwrite(&val1, sizeof(int), 1, fh); 


    fclose(fh);
}



