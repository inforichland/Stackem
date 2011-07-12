#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "machine.h"

// machine code

#define incStack(sp) ((sp)--)
#define decStack(sp) ((sp)++)

inline int pop(Machine *m) {
  int x = m->memory[m->stackPointer];
  decStack(m->stackPointer);
  return x;
}

inline void push(Machine *m, int x) {
  incStack(m->stackPointer);
  m->memory[m->stackPointer] = x;
}

void op_add_func(Machine *m) {
  decStack(m->stackPointer);
  m->memory[m->stackPointer] += m->memory[m->stackPointer - 1];
}

void op_sub_func(Machine *m) {
  decStack(m->stackPointer);
  m->memory[m->stackPointer] -= m->memory[m->stackPointer - 1];
}

void op_mul_func(Machine *m) {
  decStack(m->stackPointer);
  m->memory[m->stackPointer] *= m->memory[m->stackPointer - 1];
}

void op_div_func(Machine *m) {
  decStack(m->stackPointer);
  m->memory[m->stackPointer] /= m->memory[m->stackPointer - 1];
}

void op_lit_func(Machine *m) {
  push(m, m->programCodes[++m->programCounter]);
}

void op_brn_func(Machine *m) {
  // have to decrement by 1 b/c the inner loop will increment the PC
  m->programCounter = m->programCodes[m->programCounter + 1] - 1;
  printf ("  Branching to: %d\n", m->programCounter + 1);
}

void op_bze_func(Machine *m) {
  if (m->memory[m->stackPointer] == 0) {
    m->programCounter = m->programCodes[m->programCounter + 1] - 1;
    printf ("  Branching to: %d\n", m->programCounter + 1);    
  }
  else
    m->programCounter++;
}

void op_neg_func(Machine *m) {
  m->memory[m->stackPointer] = -m->memory[m->stackPointer];
}

void op_hlt_func(Machine *m) {
  printf ("  Halting\n");
  m->halted = 1;
  m->result = pop(m);
}

opcode_func_ptr opcodeTable[] = {
  &op_add_func,
  &op_sub_func,
  &op_mul_func,
  &op_div_func,
  &op_lit_func,
  &op_brn_func,
  &op_bze_func,
  &op_neg_func,
  &op_hlt_func,
};

void runMachine(Machine *m) {
  opcode_func_ptr currentOpcode;
  m->stackPointer = m->memorySize - 1;
  
  while (!m->halted && (m->programCounter < m->programCodesCount)) {
    printf ("Executing opcode: %d\n", m->programCodes[m->programCounter]);

    if (m->programCodes[m->programCounter] >= 0 && 
	m->programCodes[m->programCounter] < op_max) {

      currentOpcode = m->opcode_funcs[m->programCodes[m->programCounter]];
      currentOpcode(m);
      m->programCounter++;
    } else {
      printf ("  Invalid opcode!\n");
      m->result = -1;
      return;
    }
  }
}

Machine *initMachine(int initialMemory, int *codes, int codeLength, int initPc) {
  Machine *m = (Machine*)malloc(sizeof(Machine));
  if (m != NULL) {
    m->stackPointer = 0;
    m->programCounter = initPc;
    m->halted = 0;
    m->memorySize = initialMemory;
    m->memory = (int*)malloc(initialMemory);
    if (m->memory == NULL) {
      free(m);
      return NULL;
    }
    m->opcode_funcs = &opcodeTable;
    m->programCodes = codes;
    m->programCodesCount = codeLength;
  }

  return m;
}

void destroyMachine(Machine *m) {
  free(m->memory);
  free(m);
}
