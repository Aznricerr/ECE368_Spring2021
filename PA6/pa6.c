#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gridTrav.h"

void freeMatrix(short ** grid, int r);
void freeLLMat(Point *** grid, int r, int c);

int main(int argc, char * argv[]) {
    if(argc != 5) 
    {
        fprintf(stderr,"Inccorrect Number of Flags\n");
        return EXIT_FAILURE;
    }

    int r = 0;
    int c = 0;
    short ** grid = creatGrid(argv[1], &r, &c);
    if(grid == NULL)
        return EXIT_FAILURE;

    
    //Add cases for exit failure

    txtConv(argv[2], grid, r, c);

    Point *** gridList = listPoint(grid, r, c);
    int path = 0;
    int * output2 = pathHelp(gridList, r, c, &path);
    

    printMat(argv[3], output2, c);
    pathTrav(argv[4], gridList, r, c, path);

    freeLLMat(gridList, r, c);
    freeMatrix(grid, r);
    free(output2);
    
    return EXIT_SUCCESS;
}

void freeMatrix(short ** grid, int r)
{
    int i;
    for(i = 0; i < r; i++)
    {
        free(grid[i]);
    }
    free(grid);
}

void freeLLMat(Point *** grid, int r, int c)
{
    int i, j;
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            free(grid[i][j]);
        }
        free(grid[i]);    
    }    
    free(grid);
}




