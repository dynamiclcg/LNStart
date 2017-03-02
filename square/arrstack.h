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
const resize 10;

/* the MAXIMIZE size of stack */
const MAXIMIZE 1000;

/* the size of stack */
int size;

/* the stack for array stack */
item *astack;

/* the initial operation for stack */
int initialize();

/* the push operation in stack */
void push(item i);

/* the pop operation for stack */
item pop();

/* check if stack full */
int isOverflow();

/* check if stack is empty */
int isEmpty();

/* resize if the stack overflow */
void resize();

#endif
