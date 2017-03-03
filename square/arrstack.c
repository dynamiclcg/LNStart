/*
 * File : arrstack.c Date : 2017-03-08
 * ========================================
 * Author : lcg
 * Target : 
 *   the code realize the array stack
 */

#include <stdio.h>
#include <stdlib.h>
#include "arrstack.h"

/* the real size to truncate */
int realSize;

/* the memory elements  */
int size;

/* the pointer of stack */
item *astack;

int initialize()
{
  realSize = 0;
  size = resize;
  astack = (item *) malloc(sizeof(item) * size);
  if ( !astack ) {
    printf("Error : initialize stack fail\n");
    exit(1);
  }
  return 0;
}

void push(item i)
{
  if ( !astack ) {
    printf("Error : stack error with push!\n");
    exit(1);
  } else if ( isOverflow() ) {
    reSize();
  }
  
  astack[realSize].x = i.x;
  astack[realSize].y = i.y;
  realSize++;
}

void reSize()
{
  int newsize = size + resize;
  if( size >= limitSize ){
    printf("Error : stack over flow !\n");
    clearStack();
    exit(1);
  }
  
  item *newastack = (item *)malloc(sizeof(item) * newsize);
  if ( !newastack ) {
    printf("Error : failed to resize stack!\n");
    clearStack();
    exit(1);
  }
  
  int i;
  for( i = 0 ; i < size ; i++ ){
    newastack[i].x = astack[i].x;
    newastack[i].y = astack[i].y;
  }
  
  size = newsize;
  free(astack);
  astack = newastack;
}

void pop(item *i)
{
  if ( !astack ) {
    printf("Error : initialize stack first!\n");
    exit(1);
  } else if ( isEmpty() ){
    printf("Warning : empty stack!\n");
    i = (item *)NULL;
    return ;
  }

  realSize--;			/* stack pop out */
  *i = astack[realSize];
}

void top(item *i)
{
  if ( !astack ) {
    printf("Error : initialize stack first!\n");
    exit(1);
  } else if ( isEmpty() ){
    printf("Warning : empty stack!\n");
    i = (item *)NULL;
    return;
  }

  *i = astack[realSize-1];
}

int isEmpty()
{
  if ( realSize == 0 ) return 1;
  return 0;
}

int isOverflow()
{
  if ( realSize == size ) return 1;
  return 0;
}

void clearStack()
{
  free(astack);
}
