#include <stdio.h>
#include "2048.h"

int tilt_line_left(int length,int *line) {

  // make sure vector length is sensible
  if (length<1||length>255) return -1;

  // slide tiles to the left
  int k;
  for(k=2; k>0; k--) {
    int j;
    for(j=3; j>=1; j--) {
      if (line[j]!=0 && line[j-1]==0) {
        line[j-1]=line[j];
        line[j]=0;
      } 
    }
  }

  // combine tiles as required
  int i;
  for(i=0; i<=2; i++) {
    if (line[i]==line[i+1]) {
      line[i]=line[i]*2;
      line[i+1]=0;
    }
  }

  // slide again to ensure numbers are where they should be  
  int h;
  for(h=3; h>=1; h--) {
    if (line[h]!=0 && line[h-1]==0) {
      line[h-1]=line[h];
      line[h]=0;
     }
  }

  return 0;
}

int tilt_board_up(int size,int **board) {
  
  int i;
  for(i=0;i<size;i++) tilt_line_left(size,board[i]);
  return 0;
}

int tilt_board_right(int size,int **board) {

  board_rotate_270(size,board);
  tilt_board_up(size,board);
  board_rotate_90(size,board);
  return 0;
}

int tilt_board_down(int size,int **board) {

  board_rotate_180(size,board);
  tilt_board_up(size,board);
  board_rotate_180(size,board);
  return 0;
}

int tilt_board_left(int size,int **board) {

  board_rotate_90(size,board);
  tilt_board_up(size,board);
  board_rotate_270(size,board);
  return 0;
}
