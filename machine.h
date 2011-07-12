#ifndef MACHINE_H
#define MACHINE_H

// Types

struct Machine;
typedef void(*opcode_func_ptr)(struct Machine*);

typedef struct Machine {
  // memory-related
  int memorySize;
  int *memory;
  int stackPointer;

  // function
  opcode_func_ptr *opcode_funcs;

  // running
  int programCounter;
  int halted;
  int *programCodes;
  int programCodesCount;
  int result;
} Machine;

// Functions
Machine *initMachine(int initialMemory, int *codes, int codeLength, int initPc);
void destroyMachine(Machine*);
void runMachine(Machine*);

#endif // MACHINE_H
