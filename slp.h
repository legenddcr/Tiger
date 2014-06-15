#ifndef SLP_H
#define SLP_H
typedef struct A_stm_ *A_stm;
typedef struct A_exp_ *A_exp;
typedef struct A_expList_ *A_expList;

/* BinOp -> + | - | x | / */
typedef enum {A_plus,A_minus,A_times,A_div} A_binop;

/* Stm -> CompundStm | AssignStm | PrintStm */
struct A_stm_ {enum {A_compoundStm, A_assignStm, A_printStm} kind;
             union {struct {A_stm stm1, stm2;} compound;
                    struct {string id; A_exp exp;} assign;
                    struct {A_expList exps;} print;
                   } u;
            };

/* CompundStm -> Stm; Stm */
A_stm A_CompoundStm(A_stm stm1, A_stm stm2);
/* AssignStm -> id := Exp */
A_stm A_AssignStm(string id, A_exp exp);
/* PrintStm -> print(ExpList) */
A_stm A_PrintStm(A_expList exps);


/* Exp -> IdExp | NumExp | OpExp | EseqExp */
struct A_exp_ {enum {A_idExp, A_numExp, A_opExp, A_eseqExp} kind;
             union {string id;
                    int num;
                    struct {A_exp left; A_binop oper; A_exp right;} op;
                    struct {A_stm stm; A_exp exp;} eseq;
                   } u;
            };

/* id -> string */
/* IdExp -> id */
A_exp A_IdExp(string id);
/* NumExp -> num */
A_exp A_NumExp(int num);
/* OpExp -> Exp Binop Exp */
A_exp A_OpExp(A_exp left, A_binop oper, A_exp right);
/* EseqExp -> (Stm, Exp) */
A_exp A_EseqExp(A_stm stm, A_exp exp);

/* ExpList -> PairExpList | LastExpList */
struct A_expList_ {enum {A_pairExpList, A_lastExpList} kind;
                   union {struct {A_exp head; A_expList tail;} pair;
                          A_exp last;
                         } u;
                  };
/* PairExpList -> Exp, ExpList */
A_expList A_PairExpList(A_exp head, A_expList tail);
/* LastExpList -> Exp */
A_expList A_LastExpList(A_exp last);
#endif
