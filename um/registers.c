#include "registers.h"

struct Regs_T {
    uint32_t *registers;
};

Regs_T Reg_new(uint32_t num_reg){
    Regs_T new = malloc(sizeof(*new));
    new->registers = malloc(num_reg * sizeof(uint32_t))
    printf("register size: %d\n", num_reg*4);
    for (int i = 0; i < num_reg; i++) {
        (new->reg)+ = 0;
    }
    return new;
}

Regs_T 