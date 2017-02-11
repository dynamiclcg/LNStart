
/*
 * File : square.c  Date:2017-02-13
 * ==================================================
 * Author : lcg
 * Target : 
 *     do the move game for the little square to move from
 * one corner to another another
 */
#include <stdio.h>
#include <stdlib.h>
#include "pstack.h"

/* ***** Global variable ***** */
int raw,col;//raw and col value for the map
int mapSelf[10][10]={{0},{0}};//the pointer point to map

// defined in the pstack.h
/* typedef struct tway{ */
/*   int x; */
/*   int y; */
/*   struct tway *next; */
/* }tway; */

/*
 * Function : showLine
 * Param : int *line, int col
 * return : void
 */
void showLine(int *line, int col)
{
  int j=0;    
  printf("| ");
  while(j<col){
    switch(line[j]){
    case 0:
      printf(". ");
      break;;
    case 1:
      printf("\e[32m* \e[0m");
      break;
    case -1:
      printf("\e[31m# \e[0m");
      break;
    }
    j++;
  }	
  printf("|\n");
}

/*
 * Function : showInfo
 * Param : int **map -> the map info
 *     int raw : the raw for the map
 *     int col : the col for the map
 * return : value
 */
void showInfo(int (*map)[10], int raw, int col)
{
  int i;
  
  printf("========== Show Map info ==========\n");
  for(i=0; i<raw; i++){
    showLine(map[i],col);
  }
}


/*
 * Function : randStone
 * Param : int raw -> the raw value for map
 *         int col -> the col value for map
 * return : void
 */
void randStone(int raw, int col)
{
  int i=0;
  while(i<raw){
    mapSelf[rand()%raw][rand()%col]=-1;
    i++;
  }
}

/*
 * Function : randMap
 * Param : int raw -> the raw value for map
 *         int col -> the col value for map
 * return : void
 */
void randMap(int raw,int col)
{

  int i,j;

  /* mapSelf=(int **)malloc(sizeof(int *) * raw); */
  /* if(mapSelf==NULL){ */
  /*   printf("Failed to malloc memory !\n"); */
  /*   exit(1); */
  /* } */

  printf("***** RANDOM CREATE *****\n");
  for(i=0; i<raw; i++){
    /* mapSelf[i]=(int *)malloc(sizeof(int) * col); */
    /* if(mapSelf[i]==NULL){ */
    /*   printf("Faild to malloc memory for mapSelf\n"); */
    /*   exit(1); */
    /* } */
    printf("|  ");
    for(j=0; j<col; j++){
      /* map[i][j]=rand()%3; */
      mapSelf[i][j]=rand()%3-1;
      printf("%2d  ",mapSelf[i][j]);
    }
    printf("|\n");
  }
}

/*
 * Function : getNumber
 * Param : char *prompt , int *num
 * return : void
 *  use the addr for the input work with the prompt
 */
void getNumber(char *prompt , int *num)
{
  do{
    printf("%s\n",prompt);
    scanf("%d", num);
    if( *num == 0 )
      printf("[Error] wrong value!\n");
    else
      break;
  }while(1);
}


/*
 * Function : showPath
 * Param : struct tway *path
 * return : null
 */
void showPath(struct tway *path)
{
  struct tway *preway,*curway;
  
  preway=path;
  curway=preway->next;
  if(preway){
    printf("The path is null!\n");
    exit(0);
  }
  
  printf("[Start : (%2d , %2d)\n",preway->x, preway->y);
  while(curway){
    printf("[move] (%2d ,%2d) -> (%2d , %2d)\n",preway->x,preway->y,curway->x,curway->y);
    preway=curway;
    curway=preway->next;
  }
  printf("[End : end of path\n");
}


/*
 * Function : moveNext
 * Param : tway **cur
 * return : 0 -> MOVEON 1 -> BACK
 * The function to move :
 *         up > right -> down -> left
 */
int moveNext(tway **cur)
{
  int x=(*cur)->x;
  int y=(*cur)->y;
  int check=0;
 
  mapSelf[x][y]=1;//means this place passed
  showInfo(mapSelf,raw,col);
  tway *newp=(tway *)malloc(sizeof(tway));
  
  /* UP value */
  if((x-1>=0) && (mapSelf[x-1][y]==0)){
    newp->x=x-1;
    newp->y=y;
    check++;
  }else

  /* RIGHT value */
  if((y+1<col) && (mapSelf[x][y+1]==0)){
    newp->x=x;
    newp->y=y+1;
    check++;
  }else

  /* DOWN value */
  if((x+1<raw) && (mapSelf[x+1][y]==0)){
    newp->x=x+1;
    newp->y=y;
    check++;
  }else
  
  /* LEFT value */
  if((y-1>=0) && (mapSelf[x][y-1]==0)){
    newp->x=x;
    newp->y=y-1;
    check++;
  }
  
  if(check==0){
    return 0;
  }

  (*cur)->next=newp;
  push(newp);
  return 1;
}


/*
 * Function : startWork
 * Param : parameter
 * return : value
 */
void startWork(tway **path)
{
  int retcode ;
  tway *cur=(tway *)malloc(sizeof(tway));
  if(!cur){
    printf("Failed to malloc memery for startWork:cur\n");
    exit(1);
  }
   
  cur->x=(*path)->x;
  cur->y=(*path)->y;

  int i=0;
  while(i<10){
    retcode = moveNext(&cur);
    if(retcode != 0){
      /* check if the stack is empth */
      if(isEmpty())
	//means all the node passed
	break;
      /* there exists a stack of the path, when move to next , push it into stack*/
      /* and when on other way to move , pop */
      /* if the stack is empty, means the stack run out, and then end the program */
      cur=pop();
    }
    i++;
  }
}

/*
 * Function : main
 * Param : null
 * return : int
 */
int main()
{
  getNumber("Enter raw number : ", &raw);
  getNumber("Enter col number : ", &col);

  printf("raw info : %d , col info : %d\n",raw,col);
  //randMap(raw,col);
  randStone(raw,col);
  showInfo(mapSelf,raw,col);
  //initialize the stack for the program
  initialize();

  tway *path=(tway *)malloc(sizeof(tway));
  if(!path){
    printf("Failed to malloc memory for path!\n");
    exit(1);
  }
  
  path->x=0;
  path->y=0;
  path->next=NULL;

  startWork(&path);
  
  showPath(path);
  showInfo(mapSelf,raw,col);
  
  //free the stack data
  clearStack();
  free(path);


}
