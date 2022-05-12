#ifndef __H_MAN_H__
#define __H_MAN_H__

typedef struct _Node {
   char value; //value from encoding list
   long freq;
   struct _Node *next;
} Node;

typedef struct _Tree{ 
    char chr; //char
    long freq; //freq/weight
    long depht;
    int creat_time;
    struct _Tree * left; 
    struct _Tree * right; 
} Tree;
//Huffman Tree Struct

typedef struct _Forest {
   Tree *root; 
   struct _Forest *next;
} Forest;

Node *read_file(char *filename, long **arr_info);
Node * add_Node(Node * head, char chr);

char *find_topology(Node *head, long * size, int * index, long * log_arr, char * filename);
void write_top(char * filename, char * string, int size);

//Tree *build_Tree(char * top, long size, long * index);
Tree *build_Tree(FILE * fh);
char *decode_stream(Tree * head, Node * start, int node_start, int *size, long * log_arr, long *bit_input);
Tree * Add_LeftNode(Tree * root, char chr);
Tree * Add_RightNode(Tree * root, char chr);

void printTree(Tree *root, int space);


//void write_freq(char * filename, char *decoded, int size);
void write_freq(char * filename, char * file_read);

Node *top_data(char * filename, int size);

Node *node_exist(Node *head, char val);

void sort(Node **h);

Tree *build_huff(Node * tp_data, long *char_amt);

Tree *add_TreeNode(char val, long freq);

Tree *merge_TreeNodes(Tree *ltree, Tree *rtree, int crt_time);

Tree **sortForest(Tree **forest, int size);

void decode_writeTree(char * filename, Tree * root);
void decode_htree(Tree *root, FILE * fh);
Tree * findsKey(Tree * root);
//void decode_htree(Tree *root, char *Tdec, long *ind); //preorder traversal

void find_bits(Tree *root, long *hbits, long dep);

void write_vals(char *filename, long in_val, long huff_val, long amt);


#endif