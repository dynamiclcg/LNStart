#include <stdio.h>
#include <stdlib.h>
#include "pstack.h"

int main()
{
  initialize();
  
  tway *temp=(tway *)malloc(sizeof(tway));
  tway *out=NULL;

  temp->x=1;
  temp->y=2;
  
  push(temp);
  
  out=pop();
  printf("out : x=%d y=%d\n",out->x,out->y);
  free(out);
  
  temp->x=2;
  temp->y=3;
  push(temp);

  out=pop();
  printf("out : x=%d y=%d\n",out->x,out->y);
  free(out);

  temp->x=3;
  temp->y=4;
  push(temp);

  temp->x=4;
  temp->y=5;
  push(temp);
  
  out=pop();
  printf("out : x=%d y=%d\n",out->x,out->y);
  free(out);
  out=pop();
  printf("out : x=%d y=%d\n",out->x,out->y);
  free(out);
  /* out=pop(); */
  /* printf("out : x=%d y=%d\n",out->x,out->y); */
  /* free(out); */
  
  /* out=pop(); */
  /* if(out==NULL) */
  /*   printf("NULL for the stack \n"); */

  /* temp->x=1; */
  /* temp->y=2; */
  
  /* push(temp); */
  
  /* out=pop(); */
  /* printf("out : x=%d y=%d\n",out->x,out->y); */
  /* free(out); */
  
  clearStack();
  free(temp);
}
