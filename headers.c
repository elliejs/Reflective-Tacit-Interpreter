#include "headers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void assert(bool x) {
  if (!x)
    exit(EXIT_FAILURE);
}

void applyArg(machine_ptr m) {
  atom_ptr down = m->thisA->down;
  down->args[down->counter] = m->thisA->args[m->thisA->counter];
}

void applyArgDirect(machine_ptr m, int i) {
  atom_ptr down = m->thisA->down;
  down->args[down->counter] = i;
}

void free_atom(atom_ptr a) {
  free(a->args);
  free(a);
}

void resolve(machine_ptr m) {
  atom_ptr down = m->thisA->down;
  free_atom(m->thisA);
  m->thisA = down;
  if (m->thisA != NULL) {
    m->atom_busy = true;
  } else {
    printd("atom stack is exhausted. Cleaning Up...\n");
  }
}

// where the magic happens
void advanceI(machine_ptr m) {
  if (m->atom_busy)
    return;
  m->thisI = (*(m->thisA->boundI))->nexts[++(m->thisA->counter)];
}

instr_ptr instrCopy(instr_ptr i) {
  instr_ptr o = malloc(sizeof(instr));
  o->name = malloc((strlen(i->name) + 1) * sizeof(char));
  strcpy(o->name, i->name);
  o->gen = i->gen;
  o->nexts = malloc(i->arity * sizeof(instr_ptr_ptr));
  memcpy(o->nexts, i->nexts, i->arity * sizeof(instr_ptr_ptr));
  for (int ii = 0; ii < i->arity; ii++) {
    // if (o->nexts[ii] == NULL)
    o->nexts[ii] = malloc(sizeof(instr_ptr));
    memcpy(o->nexts[ii], i->nexts[ii], sizeof(instr_ptr));
  }
  o->down_args = malloc(i->arity * sizeof(int));
  memcpy(o->down_args, i->down_args, i->arity * sizeof(int));
  o->arity = i->arity;
  o->marked = false;
  return o;
}

void free_instr(instr_ptr i) {
  for (int ii = 0; ii < i->arity; ii++) {
    // if (*(i->nexts[ii]) == NULL)
    free(i->nexts[ii]);
    i->nexts[ii] = NULL;
  }
  free(i->nexts);
  free(i->down_args);
  free(i->name);
  free(i);
  i = NULL;
}

void printInstrTree(instr_ptr_ptr i, bool marking_axis) {
  printf(" (");
  printf("%s", (*i)->name);
  (*i)->marked = !marking_axis;
  for (int ii = 0; ii < (*i)->arity; ii++) {
    instr_ptr_ptr i_next = (*i)->nexts[ii];
    if ((i_next != NULL) && (*i_next != NULL) &&
        ((*i_next)->marked == marking_axis)) {
      printInstrTree(i_next, marking_axis);
    }
  }
  printf(")");
}

void freeInstrTree(instr_ptr_ptr i, bool marking_axis) {
  (*i)->marked = !marking_axis;
  for (int ii = 0; ii < (*i)->arity; ii++) {
    instr_ptr_ptr i_next = (*i)->nexts[ii];
    if ((i_next != NULL) && (*i_next != NULL) &&
        ((*i_next)->marked == marking_axis)) {
      freeInstrTree(i_next, marking_axis);
    }
  }
  free_instr(*i);
}

void freeMachine(machine_ptr m) {
  freeInstrTree(m->rootI, (*(m->rootI))->marked);
  free(m->rootI);

  while (m->thisA != NULL) {
    atom_ptr down = m->thisA->down;
    free_atom(m->thisA);
    m->thisA = down;
  }

  for (int i = 0; i < NUM_PRIMITIVES; i++) {
    free_instr(m->primitives[i]);
  }
  for (int i = 0; i < m->DeBruijnIndex; i++) {
    instr_ptr value = m->primitives[NUM_PRIMITIVES + i];
    free_instr(value);

    instr_ptr recur = m->primitives[NUM_PRIMITIVES + i + 1];
    free(recur->nexts[0]);
    // can't free recur->nexts[1], as it is a circular dependency lower in the
    // program.
    free(recur->nexts);
    free(recur->down_args);
    free(recur->name);
    free(recur);
  }
}

void machineFinalReport(machine_ptr m) {
  if (m->out.valid) {
    printf("VALID OUTPUT\n");
    printf(" RESULT:  %d\n", m->out.value);
  } else {
    printf("STILL PROCESSING\n");
  }

  printf(" PROGRAM:");
  printInstrTree(m->rootI, (*(m->rootI))->marked);

  printf("\n");
  printf(" ENERGY:  %ld\n", m->energy);

  freeMachine(m);
}
