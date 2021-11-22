#ifndef INSTRUCTIONS
#define INSTRUCTIONS

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "seq.h"
#include "memory.h"

extern void instruction(Memory_T memory, uint32_t *registers,
                        uint32_t opcode, uint32_t ra, uint32_t rb, uint32_t rc);

extern uint32_t *load_program(Memory_T memory, uint32_t rb, uint32_t rc, 
                              int *prog_count);

#endif