
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
  pstack=NULL;

  //no need do other thing
  return 0;
}


int push(tway *newp)
{
  tway *pushed=(tway *)malloc(sizeof(tway));
  if(!pushed){
    printf("Failed to create a new node!\n");
    return 1;
  }
  //put the value into new file
  pushed->x=newp->x;
  pushed->y=newp->y;
  pushed->next=NULL;

  if(isEmpty()){
    pstack=pushed;
  }else{
    //find the point at the top of stack
    tway *pre=pstack;
    while(pre->next){
      pre=pre->next;
    }
    pre->next=pushed;
    //the size of pstack added
  }
  size++;
  return 0;
}


tway *pop(){
  if(isEmpty()){
    return NULL;
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
    free(pstack);
    }else {

    /* Find the last null value and remove one */
    while(cur->next){
      pre=cur;
      cur=cur->next;
    }
    result->x=cur->x;
    result->y=cur->y;
    free(cur);
    pre->next=NULL;
  }
  size--;
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

  if(!isEmpty()){
    tway *pre=pstack;
    tway *cur=pre->next;
    while(cur){
      free(pre);
      pre=cur;
      cur=pre->next;
    }
    free(pre);
  }
  size=0;
}
