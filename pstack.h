
/*
 * File : stack.c  Date:2017-02-13
 * ==================================================
 * Author : lcg
 * Target : 
 *     in order to realize some specific stack type
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct tway{
  int x;
  int y;
  struct tway *next;
}tway;

int size;
struct tway *pstack;


/*
 * Function : initialize
 * Param : NULL
 * return : 
 *  0 means success , 1 means failed
 */
int initialize();


/*
 * Function : push
 * Param : 
 * tway *newp
 * return : 
 * 0 success , 1 failed
 */
int push(tway *newp);


/*
 * Function : pop
 * return : 
 * tway * , pop out the value of top
 */
tway * pop();


/*
 * Function : top
 * return : 
 * return the top value without pop out
 */
tway * top();


/*
 * Function : isEmpth
 * return : 
 * 1 : means empty, and 0 means no empty
 */
int isEmpty();


/*
 * Function : clearStack
 * return : void
 */
void clearStack();
