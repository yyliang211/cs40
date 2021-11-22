#ifndef REGISTERS
#define REGISTERS

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Regs_T *Regs_T;

Regs_T Reg_new(uint32_t num_reg);
Regs_T Reg_free(uint32_t num_reg);


#endif