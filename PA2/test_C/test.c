#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "h_man.h"

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

void print_List(Node*head)
{
    Node* temp = NULL;
    temp = head;
    int i, k;
    printf("\n\n\n");
    while(temp!=NULL)
    {
      unsigned char b = temp -> value;
      printf(" %d ", b);
      for(i = 7; i >= 0; i--)
      {
        k = b >> i;
        if (k & 1)
            printf("1"); 
        else
            printf("0");
      }
      temp=temp->next;
    }
    printf("\n\n\n");
}

void print_Top(Node*head)
{
    Node* temp = NULL;
    temp = head;
    int i, k;
    printf("\n\n\n");
    while(temp!=NULL)
    {
      unsigned char b = temp -> value;
      printf("Character: %c ", b);
      long freqq = temp -> freq;
      printf("Freq : %ld ", freqq);
      temp=temp->next;
    }
    printf("\n\n\n");
}

int main(int argc, char * argv[]) {
    char filename[] = "./pa2_examples/encoded/gophers_huff.hbt";
    char filename1[] = "gophers.tree";
    
    Node * main_temp;
    Tree * main_tree;
    //Node * values;
    char *topology;
    long * arr_inf;
    main_temp = read_file(filename, &arr_inf);

    long size;
    int ind_com = 0;
    topology = find_topology(main_temp, &size, &ind_com, arr_inf);

    write_top(filename1, topology);

    long index = 0;
    main_tree = build_Tree(topology, size, &index);

    char *decoded_stream;
    int size_ori = 0;
    long bit_input = 0;
    decoded_stream = decode_stream(main_tree, main_temp, ind_com, &size_ori, arr_inf, &bit_input);

    char filename2[] = "gophers.ori";
    write_top(filename2, decoded_stream);

    char filename3[] = "gophers.count";
    write_freq(filename3, decoded_stream, size_ori);

    Node * main_top;
    main_top = top_data(decoded_stream, size_ori);

    Tree * huff_tree;
    long char_amt;
    huff_tree = build_huff(main_top, &char_amt);

    char *dtree = malloc(arr_inf[1] * 3 * sizeof(char));
    long countr = 0;
    decode_htree(huff_tree, dtree, &countr);

    char filename4[] = "gophers.htree";
    write_top(filename4, dtree);

    long bits_hyff = 0;
    find_bits(huff_tree, &bits_hyff, 0);

    char filename5[] = "gophers.eval";
    write_vals(filename5, bit_input, bits_hyff, char_amt);


    free_list(main_temp);
    free_list(main_top);
    destroyTree(main_tree);
    destroyTree(huff_tree);
    free(decoded_stream);
    free(topology);
    free(arr_inf);
    free(dtree);
    
    return 0;

}