#include "instructions.h"
#include "generators.h"
#include "headers.h"

instr_ptr one_instr(void) {
  instr_ptr i = malloc(sizeof(instr));
  i->name = malloc(4 * sizeof(char));
  strcpy(i->name, "ONE");
  i->gen = gen_literal;
  i->nexts = malloc(1 * sizeof(instr_ptr_ptr));
  for (int ii = 0; ii < 1; ii++) {
    i->nexts[ii] = malloc(sizeof(instr_ptr));
    *(i->nexts[ii]) = NULL;
  }
  i->arity = 1;
  i->down_args = calloc(1, sizeof(int));
  i->down_args[0] = 1;
  i->marked = false;
  return i;
}
instr_ptr x_instr(int x) {
  instr_ptr i = malloc(sizeof(instr));
  i->name = malloc(2 * sizeof(char));
  strcpy(i->name, "X");
  i->gen = gen_literal;
  i->nexts = malloc(1 * sizeof(instr_ptr_ptr));
  for (int ii = 0; ii < 1; ii++) {
    i->nexts[ii] = malloc(sizeof(instr_ptr));
    *(i->nexts[ii]) = NULL;
  }
  i->down_args = calloc(1, sizeof(int));
  i->arity = 1;
  i->down_args[0] = x;
  i->marked = false;
  return i;
}
instr_ptr if_instr(void) {
  instr_ptr i = malloc(sizeof(instr));
  i->name = malloc(3 * sizeof(char));
  strcpy(i->name, "IF");
  i->gen = gen_if;
  i->nexts = malloc(3 * sizeof(instr_ptr_ptr));
  for (int ii = 0; ii < 3; ii++) {
    i->nexts[ii] = malloc(sizeof(instr_ptr));
    *(i->nexts[ii]) = NULL;
  }
  i->down_args = calloc(3, sizeof(int));
  i->arity = 3;
  i->marked = false;
  return i;
}
instr_ptr dec_instr(void) {
  instr_ptr i = malloc(sizeof(instr));
  i->name = malloc(4 * sizeof(char));
  strcpy(i->name, "DEC");
  i->gen = gen_dec;
  i->nexts = malloc(1 * sizeof(instr_ptr_ptr));
  for (int ii = 0; ii < 1; ii++) {
    i->nexts[ii] = malloc(sizeof(instr_ptr));
    *(i->nexts[ii]) = NULL;
  }
  i->down_args = calloc(1, sizeof(int));
  i->arity = 1;
  i->marked = false;
  return i;
}
instr_ptr mult_instr(void) {
  instr_ptr i = malloc(sizeof(instr));
  i->name = malloc(5 * sizeof(char));
  strcpy(i->name, "MULT");
  i->gen = gen_mult;
  i->nexts = malloc(2 * sizeof(instr_ptr_ptr));
  for (int ii = 0; ii < 2; ii++) {
    i->nexts[ii] = malloc(sizeof(instr_ptr));
    *(i->nexts[ii]) = NULL;
  }
  i->down_args = calloc(2, sizeof(int));
  i->arity = 2;
  i->marked = false;
  return i;
}
instr_ptr lambda_instr(void) {
  instr_ptr i = malloc(sizeof(instr));
  i->name = malloc(7 * sizeof(char));
  strcpy(i->name, "LAMBDA");
  i->gen = gen_lambda;
  i->nexts = malloc(3 * sizeof(instr_ptr_ptr));
  for (int ii = 0; ii < 3; ii++) {
    i->nexts[ii] = malloc(sizeof(instr_ptr));
    *(i->nexts[ii]) = NULL;
  }
  i->down_args = calloc(3, sizeof(int));
  i->arity = 3;
  i->marked = false;
  return i;
}
instr_ptr out_instr(void) {
  instr_ptr i = malloc(sizeof(instr));
  i->name = malloc(4 * sizeof(char));
  strcpy(i->name, "OUT");
  i->gen = gen_out;
  i->nexts = malloc(1 * sizeof(instr_ptr_ptr));
  for (int ii = 0; ii < 1; ii++) {
    i->nexts[ii] = malloc(sizeof(instr_ptr));
    *(i->nexts[ii]) = NULL;
  }
  i->down_args = calloc(1, sizeof(int));
  i->arity = 1;
  i->marked = false;
  return i;
}

//             0    1  2   3    4     5
// ALL*    = @[ONE, X, IF, DEC, MULT, LAMBDA]
