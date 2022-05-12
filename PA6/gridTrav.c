#include <stdio.h>
#include "gridTrav.h" 
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

short ** creatGrid(char * filename, int * r, int * c)
{
    FILE * fh = fopen(filename, "rb");

    if(fh == NULL)
    {
        fprintf(stderr, "INVALID FILE\n");
        return NULL;
    }

    fseek(fh, 0, SEEK_END);
    int size = ftell(fh);

    if(!(size))
    {
        fprintf(stderr, "EMPTY FILE\n");
        fclose(fh);
        return NULL;
    }

	fclose(fh);
	fh = fopen(filename, "rb");

    fread(r, sizeof(short), 1, fh);
    fread(c, sizeof(short), 1, fh);

    if(size != ((2+(*r)*(*c)) * sizeof(short)))
    {
        fprintf(stderr, "INVALID SIZE IN FILE\n");
        fclose(fh);
        return NULL;
    }

    short ** rGrid = malloc(*r * sizeof(short*));
    int i;
    for(i = 0; i < *r; i++)
    {
        rGrid[i] = malloc(*c * sizeof(short));
    }
    
    for(i = 0; i < *r; i++)
    {
        int j;
        for(j = 0; j < *c; j++)
        {
            fread(&(rGrid[i][j]), sizeof(short), 1, fh);
        }
    }
    fclose(fh);;
    return rGrid;
}

void txtConv(char * filename, short ** grid, int r, int c)
{
    FILE * fh = fopen(filename, "w");

    fprintf(fh, "%hd %hd\n", r, c);
    int i, j;
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            fprintf(fh,"%hd", grid[i][j]);
            if(j < c - 1)
                fprintf(fh, " ");
        }
        fprintf(fh, "\n");
    }
    fclose(fh);
}

Point *** listPoint(short** grid, int r, int c)
{
    Point *** pGrid = malloc(r * sizeof(Point**));
    int i;
    for(i = 0; i < r; i++)
    {
        pGrid[i] = malloc(c * sizeof(Point *));
    }

    for(i = 0; i < r; i++)
    {
        int j;
        for(j = 0; j < c; j++)
        {
            pGrid[i][j] = creatPoint((short)i, (short)j, grid[i][j], 32767, NULL);
        }
    }

    return pGrid;
}

Point * creatPoint(short r, short c, short val, int time, Point * pred)
{
    Point * temp = malloc(sizeof(Point));
    temp -> r = r;
    temp -> c = c;
    temp -> val = val;
    temp -> time = time;
    temp -> next = NULL;
    temp -> pred = pred;
    temp -> check = 0;
    return temp;
} 

int shortestPath(Point *** list, int r, int c, int rb, int cb, Point * prev, int g)
{
    //Down(r+1), Left(c-1), Right(c+1), Up(r-1)
    //goal = r -> rb
    if(r < 0 || c < 0 || r >= rb || c >= cb)
        return 0;

    if((prev == NULL) & (g == 1))
    {
        list[r][c] -> time = list[r][c] -> val;
        list[r][c] -> pred = NULL;
    }
    else if(list[r][c] -> pred == NULL)
        return 0;
    
    if(list[r][c] -> check ==  1)
        return 0; 

    if(r > 0)
    {
        if((list[r-1][c] -> time) > (list[r][c] -> time + list[r-1][c] -> val))
        {
            list[r-1][c] -> time = list[r][c] -> time + list[r-1][c] -> val;
            list[r-1][c] -> pred = list[r][c];
            list[r-1][c] -> check = 0;
        }
    }
    if(c < cb - 1)
    {
        if((list[r][c+1] -> time) > (list[r][c] -> time + list[r][c+1] -> val))
        {
            list[r][c+1] -> time = list[r][c] -> time + list[r][c+1] -> val;
            list[r][c+1] -> pred = list[r][c];
            list[r][c+1] -> check = 0;
        }
    }
    if(c > 0)
    {
        if((list[r][c-1] -> time) > (list[r][c] -> time + list[r][c-1] -> val))
        {
            list[r][c-1] -> time = list[r][c] -> time + list[r][c-1] -> val;
            list[r][c-1] -> pred = list[r][c];
            list[r][c-1] -> check = 0;
        }
    }
    if(r < rb - 1)
    {
        if((list[r+1][c] -> time) > (list[r][c] -> time + list[r+1][c] -> val))
        {
            list[r+1][c] -> time = list[r][c] -> time + list[r+1][c] -> val;
            list[r+1][c] -> pred = list[r][c];
            list[r+1][c] -> check = 0;
        }
    }
    list[r][c] -> check = 1;
    return 1;
}

void shortHelp(Point *** list, int rb, int cb)
{
    int k;
    for(k = 0; k < cb; k++)
    {
        shortestPath(list, rb-1, k, rb, cb, NULL, 1);
    }

    int i, j;
    k = 1;
    while(k > 0)
    {
        k = 0;
        for(i = 0; i < rb-1; i++)
        {
            for(j = 0; j < cb; j++)
            {
                k += shortestPath(list, i, j, rb, cb, NULL, 0);
            }
        }
    }

}

int * pathHelp(Point *** list, int r, int c, int * path)
{
    int * sPaths = malloc(c * sizeof(int));
    int i;
    *path = 0;
    shortHelp(list, r, c);
    for(i = 0; i < c; i++)
    {
        sPaths[i] = list[0][i] -> time;
        if((list[0][*path] -> time) > (list[0][i] -> time))
        {
            *path = i;
        } 
    }

    return sPaths;
}

void pathTrav(char * filename, Point *** list, int r, int c, int sCol)
{
    FILE * fh = fopen(filename, "wb");

    int totalTime = list[0][sCol]->time;
    int count = 1;
    Point * tmpTrav = list[0][sCol];
    while(tmpTrav -> pred != NULL)
    {
        count ++;
        tmpTrav = tmpTrav -> pred;
    }
    fwrite(&totalTime, sizeof(int), 1, fh);
    fwrite(&count, sizeof(int), 1, fh);

    tmpTrav = list[0][sCol];
    while(tmpTrav != NULL)
    {
        fwrite(&(tmpTrav->r), sizeof(short), 1, fh);
        fwrite(&(tmpTrav->c), sizeof(short), 1, fh);
        tmpTrav = tmpTrav -> pred;
    }
    fclose(fh);
}

void clearList(Point *** list, int r, int c)
{
    int i, j;
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            list[i][j] -> time = 32767;
            list[i][j] -> check = 0;
            list[i][j] -> pred = NULL;
        }
    }
}

void printMat(char * filename, int * list, int c)
{
    FILE * fh = fopen(filename, "wb");
    short col = (short)c;
    fwrite(&col, sizeof(short), 1, fh);

    fwrite(list, sizeof(int), c, fh);

    fclose(fh);
}

void testP(Point *** list, int r, int c)
{
    int i,j;
    fprintf(stdout,"Time\n");
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            fprintf(stdout, "%d ", list[i][j] -> time);
        }
        fprintf(stdout,"\n");
    } 
}

