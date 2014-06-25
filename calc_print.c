#include "calc_print.h"

#include <stdio.h>

static int maxargsExp(A_exp exp)
{
  if (exp == NULL)
    return 0;
  
  if (exp->kind == A_eseqExp)
    return maxargs(exp->u.eseq.stm) + maxargsExp(exp->u.eseq.exp);
  else if (exp->kind == A_opExp)
    return maxargsExp(exp->u.op.left) + maxargsExp(exp->u.op.right);
  else return 0;
}

static int maxargsExpList(A_expList expList)
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
  else {
    assert (stm->kind == A_printStm);
    return 1 + maxargsExpList(stm->u.print.exps);
  }
}

