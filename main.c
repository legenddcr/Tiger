/* This file is intentionally empty.  You should fill it in with your
   solution to the programming exercise. */
#include <stdio.h>

#include "util.h"
#include "slp.h"
#include "prog1.h"

int maxargsExp(A_exp exp)
{
  if (exp == NULL)
    return 0;
  
  if (exp->kind == A_eseqExp)
    return maxargs(exp->u.eseq.stm) + maxargsExp(exp->u.eseq.exp);
  else if (exp->kind == A_opExp)
    return maxargsExp(exp->u.op.left) + maxargsExp(exp->u.op.right);
  else return 0;
}

int maxargsExpList(A_expList expList)
{
  if (expList == NULL)
    return 0;

  if (expList->kind == A_pairExpList)
    return maxargsExp(expList->u.pair.head) + maxargsExpList(expList->u.pair.tail);
  else
    return maxargsExp(expList->u.last);
}

/* Calculate print num */
int maxargs(A_stm stm)
{
  if (stm == NULL)
    return 0;

  if (stm->kind == A_compoundStm)
    return maxargs(stm->u.compound.stm1) + maxargs(stm->u.compound.stm2);
  else if (stm->kind == A_assignStm)
    return maxargsExp(stm->u.assign.exp);
  else
    return 1 + maxargsExpList(stm->u.print.exps);
}

int main(int argc, char *argv[])
{
  A_stm stm = prog();
  printf ("Max args is %d\n", maxargs(stm));
  interp(stm);  
  return 0;
}

