#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "seq.h"
#include "instructions.h"
#include "memory.h"

typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, MAP, UNMAP, OUT, IN, LOADP, LV
} Um_opcode;


void cmov(Memory_T memory, uint32_t *registers, uint32_t ra, 
            uint32_t rb, uint32_t rc)
{
    (void)memory;

    if (registers[rc] != 0) {
        registers[ra] = registers[rb];
    }
}

void sload(Memory_T memory, uint32_t *registers, uint32_t ra, 
            uint32_t rb, uint32_t rc)
{
    registers[ra] = Memory_get(memory, registers[rb], registers[rc]);
}

void sstore(Memory_T memory, uint32_t *registers, uint32_t ra, 
            uint32_t rb, uint32_t rc)
{
    (void)registers;

    Memory_put(memory, registers[ra], registers[rb], registers[rc]);
}

void add(Memory_T memory, uint32_t *registers, uint32_t ra, 
        uint32_t rb, uint32_t rc)
{
    (void)memory;

    registers[ra] = registers[rb] + registers[rc];
}

void mul(Memory_T memory, uint32_t *registers, uint32_t ra, 
        uint32_t rb, uint32_t rc)
{
    (void)memory;
    
    registers[ra] = registers[rb] * registers[rc];
}

void divide(Memory_T memory, uint32_t *registers, uint32_t ra, 
        uint32_t rb, uint32_t rc)
{
    (void)memory;

    /* allowed to fail if value in rc is 0 */
    registers[ra] = registers[rb] / registers[rc];
}

void nand(Memory_T memory, uint32_t *registers, uint32_t ra, 
        uint32_t rb, uint32_t rc)
{
    (void)memory;
    
    registers[ra] = ~(registers[rb] & registers[rc]);
}

void halt(Memory_T memory, uint32_t *registers, uint32_t ra, 
        uint32_t rb, uint32_t rc)
{
    (void)registers;
    (void)ra;
    (void)rb;
    (void)rc;

    Memory_free(memory);
    exit(0);
}

void map(Memory_T memory, uint32_t *registers, uint32_t ra, 
        uint32_t rb, uint32_t rc)
{
    (void)ra;

    uint32_t id = Memory_map(memory, registers[rc]);
    registers[rb] = id;
}

void unmap(Memory_T memory, uint32_t *registers, uint32_t ra, 
            uint32_t rb, uint32_t rc)
{
    (void)ra;
    (void)rb;

    Memory_unmap(memory, registers[rc]);
}

void out(Memory_T memory, uint32_t *registers, uint32_t ra, 
        uint32_t rb, uint32_t rc)
{
    (void)memory;
    (void)ra;
    (void)rb;

    assert(registers[rc] <= 255);
    
    fputc(registers[rc], stdout);
}

void in(Memory_T memory, uint32_t *registers, uint32_t ra, 
        uint32_t rb, uint32_t rc)
{
    (void)memory;
    (void)registers;
    (void)ra;
    (void)rb;

    uint32_t in = fgetc(stdin);

    if (feof(stdin)) {
        in = ~0;
    }

    registers[rc] = in;
}

void loadp(Memory_T memory, uint32_t *registers, uint32_t ra, 
                uint32_t rb, uint32_t rc)
{
    (void)ra;
    (void)rc;
    if (registers[rb] == 0) {
        return;
    }

    Memory_loadp(memory, registers[rb]);

}

void lv(Memory_T memory, uint32_t *registers, uint32_t ra, 
        uint32_t rb, uint32_t rc)
{
    
    (void)memory;
    (void)rc;

    /* rb holds 25 bit value to be loaded, done in um.c */
    registers[ra] = rb;   
}

void (*inst_pointer[14]) (Memory_T memory, uint32_t *registers, 
                          uint32_t ra, uint32_t rb, uint32_t rc) = {
                            cmov, sload, sstore, add, mul, divide, nand, halt, 
                            map, unmap, out, in, loadp, lv};

void instruction(Memory_T memory, uint32_t *registers,
                uint32_t opcode, uint32_t ra, uint32_t rb, uint32_t rc) 
{
    /* Ensure opcodes and registers are within correct range */
    assert(opcode < 14);
    assert(ra <= 7);
    if (opcode != 13) {
        assert(rb <= 7);
        assert(rc <= 7);
    } 
    
    inst_pointer[opcode](memory, registers, ra, rb, rc);
}