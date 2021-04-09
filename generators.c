#include "generators.h"
#include "activators.h"
#include "headers.h"

gen_any(literal, 1); // should be 0, see if later framework will support
gen_any(if, 3);
gen_any(dec, 1);
gen_any(mult, 2);
gen_any(lambda, 2);
gen_any(value, 1);
gen_any(recur, 2);
gen_any(out, 1);
