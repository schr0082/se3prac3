#include <stdio.h>
#include <stdlib.h>
#include "2048.h"

int **board_create(int size)
{
  int i;
  // make sure size of board is sensible
  if (size<1||size>255) return NULL;

  int **board=calloc(size,sizeof(int *));
  if (!board) return NULL;
  for(i=0;i<size;i++) {
    board[i]=calloc(size,sizeof(int));
    if (!board[i]) return NULL;
  }
  return board;
}

int board_display(int size,int **board)
{
  // make sure size of board is sensible
  if (size<1||size>255) return -1;
  
  int x,y;
  
  for(y=0;y<size;y++) {    
    for(x=0;x<size;x++) {
      if (board[x][y]) printf("[% 5d]",board[x][y]);
      else printf("[     ]");
    }
    printf("\n");
  }
  return 0;
}

int board_spawn_tile(int size,int **board) {

  // Find how many empty squares there are
  int n=0;
  int x,y;
  for(x=0;x<size;x++) 
    for(y=0;y<size;y++)
      if (!board[x][y]) n++;

  // no empty squares
  if (n<1) return -1;
  
  // pick square to fill
  n=random()%n;

  // pick value to insert, either 2 or 4
  int value;
  if (random()&1) value=2; else value=4;

  // Insert value into board
  for(x=0;x<size;x++) 
    for(y=0;y<size;y++)
      if (!board[x][y]) {
	if (n) n--; else {
	  board[x][y]=value;
	  return 0;
	}
      }
  
  // Something went wrong
  return -1;
}

int board_rotate_90(int size, int **board) {

  //check to see if the board is an appropriate size

  if (size < 1 || size > 255) return -1;
  
  int temp_board[size][size];
  int x,y;


  // rotate into temp_board

  for(x = 0; x < size; x++)
    for(y = 0; y < size; y++)
      temp_board[(size-1)-y][x]=board[x][y];


  // copy temp board back into original board

  for(x = 0; x < size; x++) 
    for(y = 0; y < size; y++)
      board[x][y]=temp_board[x][y];
 
 return 0;
}

int board_rotate_180(int size, int **board) {

  //call rotate 90 twice

  board_rotate_90(size, board);
  return board_rotate_90(size, board);
}

int board_rotate_270(int size, int **board) {

  //call rotate 180, then rotate 90 for a total of 270

  board_rotate_180(size, board);
  return board_rotate_90(size, board);
}
