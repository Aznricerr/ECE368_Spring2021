#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "h_man.h"


void free_list(Node *head);
void destroyTree(Tree* root);

int main(int argc, char * argv[]) {
    
    if(argc != 7) 
    {
        fprintf(stderr,"Inccorrect Number of Flags\n");
        return EXIT_FAILURE;
    }

    /*Collect Data and Decode Topology*/
    Node * input_stream;
    Tree * input_tree;

    char *topology;
    long * header_info;
    input_stream = read_file(argv[1], &header_info);

    if(input_stream == NULL)
    {
        fprintf(stderr,"Invalid File\n");
        return EXIT_FAILURE;
    }

    long size;
    int top_index = 0;
    topology = find_topology(input_stream, &size, &top_index, header_info, argv[2]);

    /*Build Tree and Decode Message*/
    long index = 0;
    input_tree = help_bTree(argv[2]);

    char *decoded_stream;
    int size_ori = 0;
    long bit_input = 0;
    decoded_stream = decode_stream(input_tree, input_stream, top_index, &size_ori, header_info, &bit_input);

    write_top(argv[3], decoded_stream, size_ori);
    //Write Frequency
    write_freq(argv[4], argv[3]);

    //Build Huffman tree based off Decoded Message
    Node * main_top;
    main_top = top_data(argv[3], size_ori);
    Node * trav_top = main_top;

    Tree * huff_tree;
    long char_amt;
    huff_tree = build_huff(main_top, &char_amt);


    decode_writeTree(argv[5], huff_tree);


    //Write Huffman Topology
    long bits_hyff = 0; 
    find_bits(huff_tree, &bits_hyff, 0);

    char_amt = 8;
    write_vals(argv[6], bit_input, bits_hyff, char_amt);
    //printf("%ld, %ld, %ld\n", bit_input, bits_hyff, char_amt);

    free_list(input_stream);
    free_list(main_top);
    destroyTree(input_tree);
    destroyTree(huff_tree);
    free(decoded_stream);
    free(topology);
    free(header_info);
    
    return EXIT_SUCCESS;
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
