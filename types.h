#ifndef TYPES_H
#define TYPES_H

#include "machine.h"

enum {
  op_add = 0,  // addition
  op_sub,      // subtraction
  op_mul,      // multiplication
  op_div,      // division
  op_lit,      // push a literal on the stack
  op_brn,      // unconditional branch
  op_bze,      // branch if TOS equal to 0
  op_neg,      // negate TOS,
  op_hlt,      // halt machine
  op_max       // max # of opcodes
};

#endif // TYPES_H
