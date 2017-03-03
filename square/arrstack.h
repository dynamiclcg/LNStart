/*
 * File : arrstack.h Date : 2017-03-08
 * ========================================
 * Author : lcg
 * Target :
 *    this file do the another realization of
 * stack, different with linked list
 */


/* ==============================
 * Usage of the arrstack:
 *    1. initialize this stack, initialize variable
 *    2. push : normal pop operation, exit if pop 
 *              without initialize operation
 *    3. pop : pop out the top item
 * ==============================
 */
#ifndef ARRSTACK_H
#define ARRSTACK_H

/*
 * Define the type of item in the stack
 */
typedef struct item{
int x;
int y;
}item;

/* the constant size to realloc */
#define resize 10

/* the MAXIMIZE size of stack */
#define limitSize 1000

/* the size of stack */
/* the stack for array stack */

/* the initial operation for stack */
int initialize();

/* the push operation in stack */
void push(item i);

/* the pop operation for stack */
void pop(item *i);

/* the top element for stack */
void top(item *i);
/* check if stack full */
int isOverflow();

/* check if stack is empty */
int isEmpty();

/* resize if the stack overflow */
void reSize();

/* clear stack function */
void clearStack();
#endif
