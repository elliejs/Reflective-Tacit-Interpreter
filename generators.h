#ifndef GENERATORS_H
#define GENERATORS_H

#include "headers.h"
#include <stdlib.h>
#include <string.h>

#define gen_any(NAME, ARITY)                                                   \
  void gen_##NAME(machine_ptr m) {                                             \
    atom_ptr pa = malloc(sizeof(atom));                                        \
    pa->name = #NAME;                                                          \
    pa->act = act_##NAME;                                                      \
    pa->args = malloc(ARITY * sizeof(int));                                    \
    memcpy(pa->args, (*(m->thisI))->down_args, ARITY * sizeof(int));           \
    pa->arity = ARITY;                                                         \
    pa->counter = -1;                                                          \
    pa->down = m->thisA;                                                       \
    pa->boundI = m->thisI;                                                     \
    m->thisA = pa;                                                             \
  }

void gen_literal(machine_ptr);
void gen_if(machine_ptr);
void gen_dec(machine_ptr);
void gen_mult(machine_ptr);
void gen_lambda(machine_ptr);
void gen_value(machine_ptr);
void gen_recur(machine_ptr);
void gen_out(machine_ptr);

#endif
