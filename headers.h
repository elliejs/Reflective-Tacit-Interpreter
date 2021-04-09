#ifndef HEADERS_H
#define HEADERS_H

#include <stdbool.h>
#include <stdlib.h>

#define NUM_PRIMITIVES 6
#define MAX_LAMBDA_DEPTH 20
#define MAX_TIME 1000

// #define DEBUG

#ifdef DEBUG
#define printd printf
#define d ;
#else
#define printd //
#define d      //
#endif

typedef struct machine machine;
typedef struct machine *machine_ptr;
typedef struct instr instr;
typedef struct instr *instr_ptr;
typedef struct instr **instr_ptr_ptr;
typedef struct atom atom;
typedef struct atom *atom_ptr;
typedef void (*trigger)(machine_ptr);
typedef struct output output;

struct output {
  int value;
  bool valid;
};

struct machine {
  instr_ptr_ptr thisI;
  instr_ptr_ptr rootI;
  atom_ptr thisA;
  int lambda_values[MAX_LAMBDA_DEPTH];
  int DeBruijnIndex;
  instr_ptr primitives[NUM_PRIMITIVES + (MAX_LAMBDA_DEPTH * 2)];
  size_t energy;
  bool atom_busy;
  output out;
};

struct instr {
  char *name;
  trigger gen;
  instr_ptr_ptr *nexts;
  int *down_args;
  int arity;
  bool marked;
};

struct atom {
  const char *name;
  trigger act;
  int counter;
  int *args;
  int arity;
  atom_ptr down;
  instr_ptr_ptr boundI;
};

void assert(bool);
void applyArg(machine_ptr);
void applyArgDirect(machine_ptr, int);
void resolve(machine_ptr);
void advanceI(machine_ptr);
void free_instr(instr_ptr);
instr_ptr instrCopy(instr_ptr);
void printInstrTree(instr_ptr_ptr, bool);
void freeInstrTree(instr_ptr_ptr, bool);
void freeMachine(machine_ptr);
void machineFinalReport(machine_ptr);
#endif
