#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "headers.h"

instr_ptr one_instr(void);
instr_ptr x_instr(int);
instr_ptr if_instr(void);
instr_ptr dec_instr(void);
instr_ptr mult_instr(void);
instr_ptr lambda_instr(void);
instr_ptr out_instr(void);

#endif
