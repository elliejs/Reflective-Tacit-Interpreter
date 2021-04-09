#include <stdio.h>
#include <stdlib.h>

#include "headers.h"
#include "instructions.h"

int FACTORIAL[] = { // 6,  // OUT
    5,              // LAMBDA
    1,              // X
    2,              // IF
                    // T:
    6,              //// VALUE
    4,              //// MULT
    6,              //// VALUE
    7,              //// RECUR
    3,              //// DEC
    6,              //// VALUE
                    // F:
    0};             //// ONE

int indx = 0;
void machine_cycle(machine_ptr m) {
  if (m->atom_busy == false) {
    if (*(m->thisI) == NULL) {
      printd("curr instruction is null, creating one to run...\n");
      *(m->thisI) = instrCopy(m->primitives[FACTORIAL[indx]]);
      indx++;
    }
    (*(m->thisI))->gen(m);
    m->atom_busy = true;
  }
  printd("machine energy: %ld\n", m->energy);
  printd("instr name:     %s\n", (*(m->thisI))->name);
  printd("atom name:      %s\n\targs: ", m->thisA->name);
  for (int i = 0; i < m->thisA->arity; i++) {
    printd("%d ", m->thisA->args[i]);
  }
  printd("\n");
  // d printInstrTree(m->rootI, (*(m->rootI))->marked);
  printd("\n");

  if (m->atom_busy == true) {
    m->atom_busy = false;
    m->thisA->act(m);
  }
}

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    printf("run with ./interp [x], where x is the number to perform x!\n");
    exit(EXIT_FAILURE);
  }

  // machine set up
  machine m = {.primitives = {one_instr(), x_instr(atoi(argv[1])), if_instr(),
                              dec_instr(), mult_instr(), lambda_instr()},
               .thisI = malloc(sizeof(instr_ptr_ptr)),
               .atom_busy = false,
               .energy = 100,
               .DeBruijnIndex = 0,
               .thisA = NULL,
               .out = {.valid = false}};
  machine_ptr pm = &m;
  *(pm->thisI) = out_instr();
  pm->rootI = pm->thisI;

  // meta-machine running is this little block
  while (--pm->energy > 0) {
    machine_cycle(pm);
    if (pm->thisA == NULL || pm->out.valid)
      break;

    advanceI(pm);
  }
  printd("\n\n");

  // cleanup
  machineFinalReport(pm);

  exit(EXIT_SUCCESS);
}
