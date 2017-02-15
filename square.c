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
void showPath(tway *path)
{
  struct tway *preway,*curway;
  
  preway=path;
  curway=preway->next;
  
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
 * Param : 
 *   int xp , int yp means the point of start position
 * return : 0 -> MOVEON 1 -> BACK
 * The function to move :
 *         up > right -> down -> left
 */
int moveNext(int xp,int yp)
{
  int check=0;
 
    /* UP value */
  if((xp-1>=0) && (mapSelf[xp-1][yp]==0)){
    return 1;
  }

  /* RIGHT value */
  if((yp+1<col) && (mapSelf[xp][yp+1]==0)){
    return 2;
  }

  /* DOWN value */
  if((xp+1<raw) && (mapSelf[xp+1][yp]==0)){
    return 3;
  }
  
  /* LEFT value */
  if((yp-1>=0) && (mapSelf[xp][yp-1]==0)){
    return 4;
  }
  
  /* GO BACK */
  return 0;
}


/*
 * Function : isFinished
 * return : 
 * 0 means failed, 1 means success
 */
int isFinished()
{
  int i,j;
  
  for(i=0;i<raw;i++){
    for(j=0;j<col;j++){
      if(mapSelf[i][j]==0)
	/* exists free space, continue */
	return 0;
    }
  }
  /* if no free space,just terminated */
  return 1;
}

/*
 * Function : startWork
 * Param : parameter
 * return : value
 */
void startWork(int x,int y)
{
  int retcode ;
  int i=0;
  
  tway *cur=(tway *)malloc(sizeof(tway));
  tway *temp=NULL;

  if(!cur){
    printf("Failed to malloc cur memory in startWork!\n");
    exit(1);
  }

  cur->x=x;
  cur->y=y;
  
  while(1){
    /* means this square has passed */
    mapSelf[cur->x][cur->y]=1;
    printf("The %d try\n",i);
    showInfo(mapSelf,raw,col);
    retcode = moveNext(cur->x,cur->y);


    /* According the return value to do next  */
    switch(retcode){
    case 0:
      temp=pop();
      cur->x=temp->x;
      cur->y=temp->y;
      free(temp);
      printf("Move Back\n");
      printf("The new value for cur is [%d,%d]\n",cur->x,cur->y);
      break;
    case 1:
      push(cur);
      cur->x=cur->x-1;
      printf("Move up\n");
      break;
    case 2:
      push(cur);
      cur->y=cur->y+1;
      printf("Move right\n");
      break;
    case 3:
      push(cur);
      cur->x=cur->x+1;
      printf("Move down\n");
      break;
    case 4:
      push(cur);
      cur->y=cur->y-1;
      printf("Move left\n");
      break;
    default:
      printf("UNKNOW ERROR!\n");
      exit(1);
    }
    /* if(retcode == 0){ */
    /*   /\* check if the stack is empth *\/ */
    /*   if(isEmpty()) */
    /* 	break; */
    /*   /\* there exists a stack of the path, when move to next , push it into stack*\/ */
    /*   /\* and when on other way to move , pop *\/ */
    /*   /\* if the stack is empty, means the stack run out, and then end the program *\/ */
    /*   back=pop(); */
    /* }else{ */
    /*   /\* means there exist space node to go  *\/ */
    /*   cur=cur->next; */
    /* } */
    /* record the path info */
    //(*path)->next=cur;
    i++;
    /* be caseful with if the map random with no way to list */
    if(isEmpty()||isFinished())  break;
  }
  free(cur);
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

  //randMap(raw,col);
  randStone(raw,col);
  showInfo(mapSelf,raw,col);
  

  tway *path=(tway *)malloc(sizeof(tway));
  if(!path){
    printf("Failed to malloc memory for path!\n");
    exit(1);
  }
  /* initialize the stack */
  initialize(); 

  startWork(rand()%raw,rand()%col);
  
  //showPath(path);
  //showInfo(mapSelf,raw,col);
  clearStack();

  //free the path 
  free(path);
  printf("raw info : %d , col info : %d\n",raw,col);
}
