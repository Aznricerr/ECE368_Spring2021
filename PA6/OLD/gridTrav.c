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
    fclose(fh);
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

int shortestPath(Point *** list, int r, int c, int rb, int cb, Point * prev, int g, int * max, Stack ** que)
{
    //Down(r+1), Left(c-1), Right(c+1), Up(r-1)
    //goal = r -> rb
    if(r == rb - 1)
    {
        *que = pop(*que);
        return 0;        
    }
    if(r < 0 || c < 0 || r >= rb || c >= cb)
    {
        *que = pop(*que);
        return 0;        
    }

    if((prev == NULL) & (g == 1))
    {
        list[r][c] -> time = list[r][c] -> val;
    }
    else if(list[r][c] -> pred == NULL)
    {
        *que = pop(*que);
        return 0;        
    }

    
    
    if((*max < (list[r][c] -> time)) & (*max != 0))
    {
        *que = pop(*que);
        list[r][c] -> check = 1;
        return 0;
    }
    
    if(list[r][c] -> check ==  1)
    {
        *que = pop(*que);
        return 0;
    }

    if(r < rb - 1)
    {
        if(((list[r+1][c] -> time) > (list[r][c] -> time + list[r+1][c] -> val)))
        {
            list[r+1][c] -> time = list[r][c] -> time + list[r+1][c] -> val;
            if(((list[r+1][c] -> time) < *max) & ((rb - 2) == r))
            {
                *max = (list[r+1][c] -> time);
            }
            else if(((rb - 2) == r) & (*max == 0))
            {
                *max = (list[r+1][c] -> time);
            }
            list[r+1][c] -> pred = list[r][c];
            //printf("ERR : %d\n", ((*que)-> point)->r);
            *que = push(*que, list[r+1][c]);
            //printf("do I make it here #0\n");
            list[r+1][c] -> check = 0;
        }
    }
    if(c < cb - 1)
    {
        if((list[r][c+1] -> time) > (list[r][c] -> time + list[r][c+1] -> val))
        {
            list[r][c+1] -> time = list[r][c] -> time + list[r][c+1] -> val;
            list[r][c+1] -> pred = list[r][c];
            *que = push(*que, list[r][c+1]);
            //printf("making it here?\n");
            list[r][c+1] -> check = 0;
        }
    }
    if(c > 0)
    {
        if((list[r][c-1] -> time) > (list[r][c] -> time + list[r][c-1] -> val))
        {
            list[r][c-1] -> time = list[r][c] -> time + list[r][c-1] -> val;
            list[r][c-1] -> pred = list[r][c];
            *que = push(*que, list[r][c-1]);
            list[r][c-1] -> check = 0;
        }
    }
    if(r > 0)
    {
        if((list[r-1][c] -> time) > (list[r][c] -> time + list[r-1][c] -> val))
        {
            list[r-1][c] -> time = list[r][c] -> time + list[r-1][c] -> val;
            list[r-1][c] -> pred = list[r][c];
            *que = push(*que, list[r-1][c]);
            list[r-1][c] -> check = 0;
        }
    }
    list[r][c] -> check = 1;
    //printQ(*que);
    //printf("do I make it here #1\n");
    *que = pop(*que);
    //printf("do I make it here #2\n");

    return 1;
}

void shortHelp(Point *** list, int r, int c, int rb, int cb, Point * prev, int * max)
{
    int l;
    *max = 0;
    /*for(l = 0; l < rb; l++)
    {
        *max += (short)(list[l][c] -> val);
    } */
    //printf("%d\n", max);
    Stack * que = NULL;
    que = push(que, list[r][c]);
    if(prev == NULL)
        shortestPath(list, r, c, rb, cb, NULL, 1, max, &que);

    if(r < 0 || c < 0 || r >= rb || c >= cb)
        return;
    //printQ(que);

  //  int i, j;
  //  int k = 1;
/*
    int lb = 0;
    int rrb = cb - 1;
    int lw = 1;
    if(c > 0)
        lb = c - 1;
    if(c < cb - 1)
        rrb = c + 1;
*/
    /*
    while(k > 0)
    {
        k = 0;
        for(i = 0; i < lw; i++)
        {
           for(j = lb; j < rb; j++)
            {
                k += shortestPath(list, i, j, rb, cb, NULL, 0, max, que);
            }
        }
        if(lw < rb - 1)
            lw++;
        if(lb > 0)
            lb--;
        if(rrb < cb)
            rrb++;
    }  */
    //printf("%d\n", isEmpty(que));
    while(!isEmpty(que))
    {
        //printQ(que);
        short temp_r = (que->point)->r;
        short temp_c = (que->point)->c;
        shortestPath(list, temp_r, temp_c, rb, cb, NULL, 0, max, &que);
        testP(list, rb, cb);
    }
}

int * pathHelp(Point *** list, int r, int c, int * path)
{
    int * sPaths = malloc(c * sizeof(int));
    int i;
    *path = 0;
    for(i = 0; i < c; i++)
    {
        int max = 0;
        shortHelp(list, 0, i, r, c, NULL, &max);
        //int j = 0;
        sPaths[i] = max;
        //sPaths[i] = (int)(list[r-1][j]->time);
        /*for(j = 0; j < c; j ++)
        {
            if(list[r-1][j]->time < sPaths[i])
                sPaths[i] = (int)list[r-1][j]->time; 
        } */
        if(sPaths[*path] > sPaths[i])
        {
            *path = i;
        }
        clearList(list, r, c);
    }
    return sPaths;
}

void pathTrav(char * filename, Point *** list, int r, int c, int sCol)
{
    FILE * fh = fopen(filename, "wb");

    int max = 0;
    shortHelp(list, 0, sCol, r, c, NULL, &max);
    int j;
    int timInd = 0;

    for(j = 0; j < c; j ++)
    {
        if((list[r-1][j]->time) < (list[r-1][timInd]->time))
            timInd = j; 
    }

    int totalTime = list[r-1][timInd]->time;
    int count = 1;
    Point * tmpTrav = list[r-1][timInd];
    while(tmpTrav -> pred != NULL)
    {
        count ++;
        Point * nxtTrav = tmpTrav -> pred;
        nxtTrav -> next = tmpTrav;
        tmpTrav = tmpTrav -> pred;
    }
    fwrite(&totalTime, sizeof(int), 1, fh);
    fwrite(&count, sizeof(int), 1, fh);
    //fprintf(stdout, "%d, %d\n", totalTime, count);
    while(tmpTrav != NULL)
    {
        //fprintf(stdout, "%d %d\n", tmpTrav->r, tmpTrav->c);
        fwrite(&(tmpTrav->r), sizeof(short), 1, fh);
        fwrite(&(tmpTrav->c), sizeof(short), 1, fh);
        tmpTrav = tmpTrav -> next;
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

Stack * push(Stack * stack, Point * val)
{
    Stack * new_head = malloc(sizeof(Stack));
    new_head -> point = val;
    new_head -> sub_tail = NULL;
    if(stack == NULL)
    {
        new_head -> next = NULL;
        new_head -> sub_tail = new_head;
        return new_head;
    }
    else
    {
        Stack * insrt = stack -> sub_tail;
        insrt -> next = new_head;
        stack -> sub_tail = new_head;
        new_head -> next = NULL; 
    }
    return stack;
   //return new_head;
}
/*
Stack * pop(Stack * stack)
{
    if(stack == NULL)
    {
        fprintf(stderr, "stack is empty");
        return NULL;
    }

    Stack * new_head = stack -> next;
    if((stack -> next) != NULL)
    {
        new_head -> sub_tail = stack -> sub_tail;
    }
    free(stack);
    return new_head;
}

int isEmpty(Stack * stack)
{
    if(stack == NULL)
        return 1;
    else 
        return 0;
}

void printQ(Stack * stack)
{
    Stack * tmp = stack;
    while(tmp != NULL)
    {
        fprintf(stdout, "print %d\n", (tmp->point)->val);
        tmp = tmp ->next;
    }
    fprintf(stdout, "\n");
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
} */
