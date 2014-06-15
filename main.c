/* This file is intentionally empty.  You should fill it in with your
   solution to the programming exercise. */
#include "prog1.h"

int maxargs(A_stm stm)
{
  return 0;
}


void interp(A_stm stm)
{
   
}

int main(int argc, char *argv[])
{
  A_stm stm = prog();
  printf ("Max args is %d\n", maxargs(stm));
  interp(stm);  
  return 0;
}

