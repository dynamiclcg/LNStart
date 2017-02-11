
/*
 * File : stack.c  Date:2017-02-13
 * ==================================================
 * Author : lcg
 * Target : 
 *     in order to realize some specific stack type
 */

#include <stdio.h>
#include <stdlib.h>
#include "pstack.h"

int initialize()
{
  //the size of pstack is 0
  size=0;
  pstack=(tway *)malloc(sizeof(tway));
  if(!pstack){
    printf("Failed to initialize of malloc for stack\n");
    exit(1);
  }
  //no need do other thing
  return 0;
}


int push(tway *newp)
{
  if(isEmpty()){
    pstack->x=newp->x;
    pstack->y=newp->y;
    pstack->next=NULL;
  }else{
    tway *pushed=(tway *)malloc(sizeof(tway));
    if(!pushed){
      printf("Failed to create a new node!\n");
      exit(0);
    }

    //put the value into new file
    pushed->x=newp->x;
    pushed->y=newp->y;
    pushed->next=NULL;
 
    //find the point at the top of stack
    tway *pre=pstack;
    tway *next=pstack->next;
    while(next){
      pre=next;
      next=pre->next;
    }
    pre->next=pushed;
    //the size of pstack added
  }
  size++;
  return 0;
}


tway *pop(){
  if(isEmpty()){
    return;
  }
  tway *pre=pstack;
  tway *cur=pstack->next;
  tway *result=(tway *)malloc(sizeof(tway));
  if(!result){
    printf("Failed to malloc the return value!\n");
    exit(1);
  }

  /* only on element in the stack */
  if(cur==NULL){
    result->x=pstack->x;
    result->y=pstack->y;
    size--;
    return result;
  }

  /* Find the last null value and remove one */
  while(cur->next){
    pre=cur;
    cur=cur->next;
  }
  result->x=cur->x;
  result->y=cur->y;
  free(cur);
  pre->next=NULL;
  size--;
  
   /* printf("pre x pointer: %l , pre y pointer: %l\n",&(pre->x),&(pre->y)); */
  return result;
}


tway * top()
{
  if(isEmpty())
    return NULL;
  if(!pstack->next)
      return pstack;

  tway *pre=pstack;
  tway *cur=pstack->next;
  while(cur){
    pre=cur;
    cur=cur->next;
  }
  return pre;
}


int isEmpty()
{
  if(size==0)
    return 1;
  return 0;
}

void clearStack()
{
  if(isEmpty){
    return;
  }

  tway *cur,*pre=pstack;
  while(pre){
    cur=pre;
    pre=pre->next;
    free(cur);
  }
}
