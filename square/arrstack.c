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

void initialize()
{
  size = 0;
  astack = item[resize];
  
  if ( !astack ) {
    printf("Error : initialize stack fail\n");
    exit(1);
  }
}

void push(item i)
{
  if ( isOverflow() ) {
    
}
