#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shell_array.h"
#include "shell_list.h"
#include "list_of_list.h"
#include <time.h>

void free_list(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(int argc, char * argv[]) {
	//char filename[] = "./examples/niceone.b";
    char filename[] = "./examples/15.b";
    
    //char filename[] = "./examples/temptemp.b";
    Node * main_temp;
    Node * values;
    main_temp = List_Load_From_File(filename);
    long val = 0;

    clock_t start = clock();

    values = List_Shellsort(main_temp, &val);

    clock_t stop = clock();
	double timing = ((double)(stop - start)) / CLOCKS_PER_SEC;
	printf("\nTiming : %f sec\n\n", timing);

    char temptemp[] = "./examples/temptemp.b";
    int size = List_Save_To_File(temptemp, values);

    printf("\n%ld\n", val);

    free_list(values);

    /*
    int size;
    long* out_array = Array_Load_From_File(filename, &size);
    
    printf("\n\n");
    
    
    long n_comp = 0;

    Array_Shellsort(out_array, size , &n_comp);


    for(int i = 0; i < size; i++)
    {
        printf(" %ld ", out_array[i]);
    }

    printf("\n%ld \n", n_comp); 

    char niceone[] = "./examples/niceone.b";
    int size1;
    size1 = Array_Save_To_File(niceone, out_array, size);

    free(out_array);
    */
    

    return 0;

}

 

