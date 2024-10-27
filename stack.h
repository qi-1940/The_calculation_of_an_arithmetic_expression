#ifndef STACK_H
#define STACK_H

#include "stdbool.h"

#define CHAR_KIND 0
#define DOUBLE_KIND 1

typedef struct{
    int kind;
    union{
    char c;
    double d;}u;
}element;

typedef struct {
    element * array;
    int top;
    int stacksize;
}SqStack;

typedef SqStack * Stack;



Stack creat_stack();

void push(Stack S,element input);

element pop(Stack S);

_Bool isEmpty(Stack S);

_Bool isFull(Stack S);

#endif