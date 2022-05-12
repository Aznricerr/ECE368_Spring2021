#include "shell_array.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
//#include <limits.h>

long *Array_Load_From_File(char *filename, int *size)
{
    int i = 0;
    //No FILE
    FILE *fh;
    if (!(fh = fopen(filename, "rb")))
    {
        *size = 0;
        return NULL;
    }
    //FILE* fh = fopen(filename, "rb");
    fseek(fh, 0, SEEK_END);
    *size = ftell(fh);
    *size = (*size / sizeof(long));

    if (*size == 0)
    {
        return NULL;
    }
    long *arr = (long *)malloc(*size * sizeof(long));

    fclose(fh);
    fh = fopen(filename, "rb");

    long buffer;
    for (i = 0; i < *size; i++)
    {
        fread(&buffer, sizeof(long), 1, fh);
        arr[i] = buffer;
        //printf("%ld ", buffer);
    }
    fclose(fh);
    return arr;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
    FILE *fh = fopen(filename, "wb");
    if (array == NULL || size == 0)
    {
        char null_arr[0];
        fwrite(null_arr, 0, 0, fh);
        fclose(fh);
        return 0;
    }

    int size_temp = size;
    fwrite(array, sizeof(long), size, fh);

    fclose(fh);
    return size;
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
    int i = 0;
    int k = 0;
    int start_val = 1;
    do
    {
        start_val = (start_val * 3) + 1;
    } while (start_val < size);
    start_val = (start_val - 1) / 3;

    for (k = start_val; k > 0; k = (k - 1) / 3)
    {
        int j;
        for (j = k; j < size; j++)
        {
            long temp_r = array[j];
            i = j;
            while (i >= k && array[i - k] > temp_r)
            {
                array[i] = array[i - k];
                i -= k;
                *n_comp = *n_comp + 1;
            }
            *n_comp = *n_comp + 1;
            array[i] = temp_r;
        }
        //printf("\n%d\n", k);
    }
    for (int p = 0; p < size; p++)
    {
        printf(" %ld", array[p]);
    }
    return;
}
