#include "generators.h"
#include "headers.h"
#include <stdio.h>
#include <string.h>

void act_literal(machine_ptr m) {
  assert(m->thisA->counter <= -1);
  m->thisA->counter++;
  applyArg(m);
  resolve(m);
  return;
}

void act_if(machine_ptr m) {
  assert(m->thisA->counter <= 2);
  if (m->thisA->counter == 0)
    m->thisA->counter = m->thisA->args[0] > 0;
  else if (m->thisA->counter > 0) {
    applyArg(m);
    resolve(m);
  }
}

void act_dec(machine_ptr m) {
  assert(m->thisA->counter <= 0);
  if (m->thisA->counter == 0) {
    applyArgDirect(m, m->thisA->args[0] - 1);
    resolve(m);
  }
}

void act_mult(machine_ptr m) {
  assert(m->thisA->counter <= 1);
  if (m->thisA->counter == 1) {
    applyArgDirect(m, m->thisA->args[0] * m->thisA->args[1]);
    resolve(m);
  }
}

void act_lambda(machine_ptr m) {
  assert(m->thisA->counter <= 1);
  if (m->thisA->counter == 0) {
    m->lambda_values[m->DeBruijnIndex] = m->thisA->args[0];
    // char ascii_DeBruijnIndex = (char)(m->DeBruijnIndex + 48);
    instr_ptr value = malloc(sizeof(instr));
    value->name = malloc(7 * sizeof(char));
    snprintf(value->name, 7 * sizeof(char), "VALUE%d", m->DeBruijnIndex);
    value->gen = gen_value;
    value->nexts = malloc(1 * sizeof(instr_ptr_ptr));
    for (int ii = 0; ii < 1; ii++) {
      value->nexts[ii] = malloc(sizeof(instr_ptr));
      *(value->nexts[ii]) = NULL;
    }
    value->down_args = malloc(sizeof(int));
    value->down_args[0] = m->DeBruijnIndex;
    value->arity = 1;
    m->primitives[NUM_PRIMITIVES + m->DeBruijnIndex] = value;

    instr_ptr recur = malloc(sizeof(instr));
    recur->name = malloc(7 * sizeof(char));
    snprintf(recur->name, 7 * sizeof(char), "RECUR%d", m->DeBruijnIndex);
    recur->gen = gen_recur;
    recur->nexts = malloc(2 * sizeof(instr_ptr_ptr));
    for (int ii = 0; ii < 1; ii++) {
      recur->nexts[ii] = malloc(sizeof(instr_ptr));
      *(recur->nexts[ii]) = NULL;
    }
    memcpy(&(recur->nexts[1]), &((*(m->thisA->boundI))->nexts[1]),
           sizeof(instr_ptr_ptr));
    recur->down_args = malloc(2 * sizeof(int));
    recur->down_args[1] = m->DeBruijnIndex;
    recur->arity = 2;
    m->primitives[NUM_PRIMITIVES + m->DeBruijnIndex + 1] = recur;

    m->DeBruijnIndex++;
  } else if (m->thisA->counter == 1) {
    m->DeBruijnIndex--;

    instr_ptr value = m->primitives[NUM_PRIMITIVES + m->DeBruijnIndex];
    free_instr(value);

    instr_ptr recur = m->primitives[NUM_PRIMITIVES + m->DeBruijnIndex + 1];
    free(recur->nexts[0]);
    // can't free recur->nexts[1], as it is a circular dependency lower in the
    // program.
    free(recur->nexts);
    free(recur->down_args);
    free(recur->name);
    free(recur);

    applyArg(m);
    resolve(m);
  }
}

void act_value(machine_ptr m) {
  assert(m->thisA->counter <= -1);
  applyArgDirect(m, m->lambda_values[m->thisA->args[0]]);
  resolve(m);
}

void act_recur(machine_ptr m) {
  assert(m->thisA->counter <= 1);
  if (m->thisA->counter == 0) {
    m->lambda_values[m->thisA->args[1]] = m->thisA->args[0];
  } else if (m->thisA->counter == 1) {
    applyArg(m);
    resolve(m);
  }
}

void act_out(machine_ptr m) {
  assert(m->thisA->counter <= 0);
  if (m->thisA->counter == 0) {
    m->out.value = m->thisA->args[m->thisA->counter];
    m->out.valid = true;
    resolve(m);
  }
}
