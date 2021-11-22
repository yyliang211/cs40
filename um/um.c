#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "memory.h"
#include "bitpack.h"
#include "um-dis.h"
#include "seq.h"
#include "instructions.h"
#include "assert.h"

FILE *openFile(const char *filename, const char *mode);
void print_registers(uint32_t *r);
uint32_t *load_segment_zero(FILE *fp, int *size);
uint32_t getNextWord(FILE *fp);
void execute_instruction(Memory_T memory, uint32_t *registers, 
                        uint32_t *prog_count, int *size, FILE *fp);

int main(int argc, char *argv[])
{
    //Reg_T registers = Reg_new();
    uint32_t registers[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    

    if(argc != 2) {
        fprintf(stderr, "Usage: ./um filename");
        exit(EXIT_FAILURE);
    }

    FILE *fp = openFile(argv[1], "r");
    int size = 0;

    Memory_T memory = Memory_new(load_segment_zero(fp, &size));

    uint32_t prog_count = 0;
    /* this loop should run until halt calls exit, or if program counter goes
     * over limit, which is an error and should cause um failure */
    while (true) {
        execute_instruction(memory, registers, &prog_count, &size, fp);
    }

    Memory_free(memory);
}

void execute_instruction(Memory_T memory, uint32_t *registers, 
                        uint32_t *prog_count, int *size, FILE *fp)
{
    uint32_t word = Memory_get(memory, 0, *prog_count);
        
    // const char *out = Um_disassemble(word);
    // printf("     0: [0x%08x] %s;\n", word, out);

        uint32_t opcode = Bitpack_getu(word, 4, 28);
        //printf("%d\n", opcode);
        assert(opcode < 14);

        /* Three register instructions */
        if (opcode == 7) {
            fclose(fp);
        }
        if (opcode < 12) {
            uint32_t ra = Bitpack_getu(word, 3, 6);
            uint32_t rb = Bitpack_getu(word, 3, 3);
            uint32_t rc = Bitpack_getu(word, 3, 0);
            
            instruction(memory, registers, opcode, ra, rb, rc);
        }
        /* Special instructions */
        else if (opcode == 12) {
            uint32_t rb = Bitpack_getu(word, 3, 3);
            uint32_t rc = Bitpack_getu(word, 3, 0);
            
            /* subtract onebecause it will increment at loop end */
            *prog_count = registers[rc] - 1; 
            instruction(memory, registers, opcode, 0, rb, rc);
            *size = 100;

        } else if (opcode == 13) {
            uint32_t ra = Bitpack_getu(word, 3, 25);
            assert(ra <= 7);

            uint32_t val = Bitpack_getu(word, 25, 0);
            instruction(memory, registers, opcode, ra, val, 0);
        }
        (*prog_count)++;
}

FILE *openFile(const char *filename, const char *mode)
{
    FILE *fp = fopen(filename, mode);
    if (fp == NULL) {
        fprintf(stderr, "Could not open file %s with mode %s\n", filename, mode);
        exit(EXIT_FAILURE);
    }
    return fp;
}

void print_registers(uint32_t *r)
{
    for (int i = 0; i < 8; i++) {
        printf("%u, ", *(r + i));
    }
    printf("\n");
}

uint32_t *load_segment_zero(FILE *fp, int *size)
{
    int cap = 1;
    uint32_t *seg_zero = malloc(cap * 4);
    *size = 0;
    while(!feof(fp)){
        uint32_t word = getNextWord(fp);
        if(feof(fp)) {
           return seg_zero;
        }
        *(seg_zero + *size) = word;
        (*size)++;
        if (*size == cap) {
           seg_zero = realloc(seg_zero, cap * 2 * 4);
           cap *= 2;
        }
    }
    seg_zero = realloc(seg_zero, *size);
    return seg_zero;
}

uint32_t getNextWord(FILE *fp)
{
    int bpb = 8; /* bits per byte */
    int num_bytes = 4;
    uint64_t out = 0;
    for (int i = 0; i < 4; i++) {

        unsigned char c = fgetc(fp);
        if (feof(fp)) {
            return 0;
        }
        out = Bitpack_newu(out, bpb, num_bytes*bpb-((i+1)*bpb), c);
    }
    return (uint32_t)out;
}


