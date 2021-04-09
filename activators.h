#ifndef ACTIVATORS_H
#define ACTIVATORS_H

#include "headers.h"

void act_literal(machine_ptr m);
void act_if(machine_ptr m);
void act_dec(machine_ptr m);
void act_mult(machine_ptr m);
void act_lambda(machine_ptr m);
void act_value(machine_ptr m);
void act_recur(machine_ptr m);
void act_out(machine_ptr m);

#endif
