#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "shell_array.h" 
#include "shell_list.h"
void free_list(Node *head);

int main(int argc, char * argv[]) {

	long n_comp = 0;

	char* input_file;
	char* ouput_file;
	input_file = malloc(strlen(argv[2]) + 1);		
	ouput_file = malloc(strlen(argv[3]) + 1); 
	strcpy(input_file, argv[2]);	
	strcpy(ouput_file, argv[3]);


	if(argc > 4) 
	{		
		fprintf(stderr,"Wrong input ARG");
		exit(EXIT_FAILURE);
	}

	//Array Test
	if(!strcmp(argv[1],"-a")) {

		int size = 0;
		long* out_array = Array_Load_From_File(input_file, &size);	
		if(out_array == NULL) {
			fprintf(stderr,"Failed to open file");
			exit(EXIT_FAILURE);
		}
		Array_Shellsort(out_array, size, &n_comp);	
		int size_num = Array_Save_To_File(ouput_file, out_array, size);
		fprintf(stdout,"%ld\n", n_comp);

		free(out_array);
	}


	// SHELL LIST Test
	if(!strcmp(argv[1],"-l")) 
	{
		n_comp = 0;
		Node* list_main = List_Load_From_File(input_file);

		if(list_main == NULL) {
			fprintf(stderr,"Failed to open file or allocate sufficient memory");
			int size_nums = List_Save_To_File(ouput_file, list_main);
			exit(EXIT_FAILURE);
		}
		//clock_t start = clock();

		list_main = List_Shellsort(list_main, &n_comp);

		//clock_t stop = clock();
		//double timing = ((double)(stop - start)) / CLOCKS_PER_SEC;
		//printf("\nTiming : %f sec\n\n", timing);
		
		int size_nums = List_Save_To_File(ouput_file, list_main);
		fprintf(stdout,"%ld\n", n_comp);
		
		free_list(list_main);
	}
	free(input_file);
	free(ouput_file);

	return EXIT_SUCCESS;
}
	
void free_list(Node *head) 
{
    while (head != NULL) 
	{
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}	
