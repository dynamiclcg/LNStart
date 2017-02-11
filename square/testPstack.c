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
  temp->x=2;
  temp->y=3;
  
  push(temp);
  
  temp->x=3;
  temp->y=4;
  push(temp);
  
  temp->x=4;
  temp->y=5;
  push(temp);
  
  out=pop();
  out=pop();
  
  clearStack();
  free(temp);
  free(out);
}
