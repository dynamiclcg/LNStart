/*
 * File : testArrstack.c Date : 2017-03-09
 * ========================================
 * Author : lcg
 * Target : 
 *   a simple test for the array list
 */


#include <stdio.h>
#include <stdlib.h>
#include "arrstack.h"

int main()
{
  initialize();
  
  item temp[12],out[12];
  int i;
  
  for( i = 0 ; i < 12 ; i++ ){
    temp[i].x=i;
    temp[i].y=100+i;
    push(temp[i]);
    printf("Stack [ push ] : x= %d , y= %d\n",temp[i].x,temp[i].y);
  }
      
      
  for( i = 11 ; i >= 0 ; i--){
    pop(&(out[i]));
    printf("Stack [ pop ] : x= %d , y= %d\n",out[i].x,out[i].y);
  }

  clearStack();

  return 0;
}
