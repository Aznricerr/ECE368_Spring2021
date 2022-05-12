#ifndef __TESTING_H__
#define __TESTING_H__

typedef struct _Stack {
   int weight;
   struct _Stack *next;
   struct _Stack *tail;
} Stack;

int isEmpty(Stack * stack); //1 -> is empty
Stack * pop(Stack * stack);
Stack * push(Stack * stack, int val);

#endif