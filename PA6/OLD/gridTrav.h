#ifndef __GRID_TRAV__
#define __GRID_TRAV__

typedef struct _Point {
   short r;
   short c;
   short val;
   int time;
   int check;
   struct _Point *next;
   struct _Point *pred;
} Point;

typedef struct _Stack {
   struct _Point * point;

   struct _Stack *next;
   struct _Stack *sub_tail;
} Stack;

int isEmpty(Stack * stack); //1 -> is empty
Stack * pop(Stack * stack);
Stack * push(Stack * stack, Point * val);
void printQ(Stack * stack);

short ** creatGrid(char * filename, int * r, int * c);
void txtConv(char * filename, short ** grid, int r, int c);
Point *** listPoint(short ** grid, int r, int c);
Point * creatPoint(short r, short c, short val, int time, Point * pred);
int shortestPath(Point *** list, int r, int c, int rb, int cb, Point * prev, int g, int * max, Stack ** que);
int * pathHelp(Point *** list, int r, int c, int * path);
void clearList(Point *** list, int r, int c);
void shortHelp(Point *** list, int r, int c, int rb, int cb, Point * prev, int * max);
void printMat(char * filename, int * list, int c);

void pathTrav(char * filename, Point *** list, int r, int c, int sCol);
void testP(Point *** list, int r, int c);

#endif