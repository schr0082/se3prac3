#include <stdio.h>
#include "2048.h"
#include <alloca.h>

int line_vector_test(int i1,int i2,int i3,int i4,char *msg,
                int o1,int o2,int o3,int o4, int (*func)(int,int *))
{
  int list[4]={i1,i2,i3,i4};
  if (msg) printf("%s - ",msg); 
  else {
    printf("Tilting {%d,%d,%d,%d} left yields {%d,%d,%d,%d} - ",
             i1,i2,i3,i4,o1,o2,o3,o4);
  }
  fflush(stdout);
  func(4,list);
  if ((list[0]!=o1)||(list[1]!=o2)||(list[2]!=o3)||(list[3]!=o4))
    {
      printf("FAILED: {%d,%d,%d,%d} became {%d,%d,%d,%d} instead of"
             " {%d,%d,%d,%d}\n",
             i1,i2,i3,i4,list[0],list[1],list[2],list[3],
             o1,o2,o3,o4);
      return -1;
    } 
  printf("PASSED.\n");
  return 0;
  
}

int ttl_vector(int i1,int i2,int i3,int i4,char *msg,
               int o1,int o2,int o3,int o4)
{
  return line_vector_test(i1,i2,i3,i4,msg,o1,o2,o3,o4,tilt_line_left);
}

int test_tilt_left()
{
  int e=0;
  e|=ttl_vector(0,0,0,0,"Empty list is empty after shift",0,0,0,0);
  e|=ttl_vector(1,0,0,0,"Value on left stays on left after shift",1,0,0,0);
  e|=ttl_vector(0,0,0,1,"Value on right shifts to left edge after shift",1,0,0,0);
  e|=ttl_vector(0,0,1,0,"Value in middle shifts to left edge after shift",1,0,0,0);
  e|=ttl_vector(1,2,4,8,"Distinct values don't combine",1,2,4,8);
  e|=ttl_vector(1,1,1,1,"Combinations don't cascade",2,2,0,0);
  e|=ttl_vector(0,0,1,1,NULL,2,0,0,0);
  e|=ttl_vector(4,0,1,1,NULL,4,2,0,0);
  e|=ttl_vector(2,0,1,1,NULL,2,2,0,0);
  e|=ttl_vector(0,2,0,2,NULL,4,0,0,0);
  return e;
}

int board_vector_test(int i1,int i2,int i3,int i4,char *msg,
                      int o1,int o2,int o3,int o4, int (*func)(int,int **))
{
  int **board=alloca(2*sizeof(int*));
  board[0]=alloca(sizeof(int)*2);
  board[1]=alloca(sizeof(int)*2);
  board[0][0]=i1; board[1][0]=i2; board[0][1]=i3; board[1][1]=i4;

  if (msg) printf("%s - ",msg); 
  else {
    printf("Board operation on {{%d,%d},{%d,%d}} yields {{%d,%d},{%d,%d}} - ",
             i1,i2,i3,i4,o1,o2,o3,o4);
  }
  fflush(stdout);
  func(2,board);
  if ((board[0][0]!=o1)||(board[1][0]!=o2)
      ||(board[0][1]!=o3)||(board[1][1]!=o4))
    {
      printf("FAILED: {{%d,%d},{%d,%d}} became {{%d,%d},{%d,%d}} instead of"
             " {{%d,%d},{%d,%d}}\n",
             i1,i2,i3,i4,
             board[0][0],board[1][0],board[0][1],board[1][1],
             o1,o2,o3,o4);
      return -1;
    } 
  printf("PASSED.\n");
  return 0;
}

int main(int argc,char **argv)
{
  int e=0;
  e|=test_tilt_left();

  board_vector_test(1,2,4,8,"Rotate 2x2 board right (+90)",4,1,8,2,board_rotate_90);
  board_vector_test(0,1,2,4,"Rotate 2x2 board right (+90)",2,0,4,1,board_rotate_90);
  board_vector_test(0,0,0,1,"Rotate 2x2 board right (+90)",0,0,1,0,board_rotate_90);
  board_vector_test(1,0,0,1,"Rotate 2x2 board right (+90)",0,1,1,0,board_rotate_90);
 
  board_vector_test(1,2,4,8,"Rotate 2x2 board right (+180)",8,4,2,1,board_rotate_180);
  board_vector_test(0,1,2,4,"Rotate 2x2 board right (+180)",4,2,1,0,board_rotate_180);
  board_vector_test(0,0,0,1,"Rotate 2x2 board right (+180)",1,0,0,0,board_rotate_180);
  board_vector_test(1,0,0,1,"Rotate 2x2 board right (+180)",1,0,0,1,board_rotate_180);

  board_vector_test(1,2,4,8,"Rotate 2x2 board right (+270)",4,1,8,2,board_rotate_270);
  board_vector_test(0,1,2,4,"Rotate 2x2 board right (+270)",2,0,4,1,board_rotate_270);
  board_vector_test(0,0,0,1,"Rotate 2x2 board right (+270)",0,0,1,0,board_rotate_270);
  board_vector_test(1,0,0,1,"Rotate 2x2 board right (+270)",0,1,1,0,board_rotate_270);

  return e;
}
