/* This file is intentionally empty.  You should fill it in with your
   solution to the programming exercise. */
#include <stdio.h>

#include "calc_print.h"
#include "interp.h"
#include "prog1.h"

int main(int argc, char *argv[])
{
  A_stm stm = prog();
  printf ("Max args is %d\n", maxargs(stm));
  interp(stm);  
  return 0;
}

