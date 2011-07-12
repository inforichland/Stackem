#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "machine.h"

// test opcodes
int testCodes[] = { op_brn, 15, // hardcoded "address" of op_hlt
		    op_lit, 2, op_lit, 3, op_mul, op_lit, 10, op_add, 
		    op_lit, 16, op_sub, op_bze, 0, op_hlt };

int main(int argc, char **argv) {
  Machine *machine = 
    initMachine(512, testCodes, sizeof(testCodes) / sizeof(int), 2);
  if (machine != NULL) {
    runMachine(machine);
    printf("\nResult: %d\n", machine->result);
    destroyMachine(machine);
    return 0;
  } else {
    return 1;
  }
}
