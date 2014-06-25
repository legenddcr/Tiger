#include "interp.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct table *Table_;
struct table {string id; int value; Table_ tail;};
Table_ Table(string id, int value, struct table *tail)
{
  Table_ t = (Table_) malloc(sizeof(*t));
  t->id = id;
  t->value = value;
  t->tail = tail;
}

struct IntAndTable {int i; Table_ t;};


static int lookup(Table_ t, string key);
static Table_ update(Table_ t, string key, int value);
static Table_ interpStm(A_stm stm, Table_ t);
static int binop(int left, int right, A_binop op);
static struct IntAndTable interpExp(A_exp exp, Table_ t);
static struct IntAndTable interpExpList(A_expList expList, Table_ t);

static int lookup(Table_ t, string key)
{
  while (t != NULL) {
    if (0 == strcmp(t->id, key))
      return t->value;
    t = t->tail;
  }

  return 0;
}

static Table_ update(Table_ t, string key, int value)
{
  return Table(key, value, t);
}

static Table_ interpStm(A_stm stm, Table_ t)
{
  if (stm == NULL)
    return NULL;

  if (stm->kind == A_compoundStm)
    return interpStm(stm->u.compound.stm2, interpStm(stm->u.compound.stm1, t));
  else if (stm->kind == A_assignStm)
    return update(t, stm->u.assign.id, interpExp(stm->u.assign.exp, t).i);
  else {
    struct IntAndTable iat = interpExpList(stm->u.print.exps, t);
    printf("%d", iat.i);
    return iat.t;
  }
}

static int binop(int left, int right, A_binop op)
{
  if (op == A_plus) return left + right;
  else if (op == A_minus) return left - right;
  else if (op == A_times) return left * right;
  else {
    assert(op == A_div);
    return left / right;
  }
}

static struct IntAndTable interpExp(A_exp exp, Table_ t)
{
  assert (exp != NULL);

  if (exp->kind == A_idExp)
    return IntAndTable(lookup(t, exp->u.id), t);
  else if (exp->kind == A_numExp)
    return IntAndTable(exp->u.num, t);
  else if (exp->kind == A_opExp) {
    struct IntAndTable left_iat = interpExp(exp->u.op.left, t);
    struct IntAndTable right_iat = interpExp(exp->u.op.right, left_iat.t);
    return IntAndTable(binop(left_iat.i, right_iat.i, exp->u.op.oper), right_iat.t);
  }
  else {
    assert (exp->kind == A_eseqExp);
    t = interpStm(exp->u.eseq.stm, t);
    return interpExp(exp->u.eseq.exp, t);
  }
}

static struct IntAndTable interpExpList(A_expList expList, Table_ t)
{
  assert (expList != NULL);
  
  if (expList->kind == A_pairExpList)
    return interpExpList(expList->pair.tail, interpExp(expList->pair.head, t).t);
  else
    return interpExp(expList->last);
}

void interp(A_stm stm)
{
  interpStm(stm, NULL);
}
