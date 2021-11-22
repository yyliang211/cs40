#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "memory.h"
#include "bitpack.h"
#include "seq.h"
#include "assert.h"

/* Incomplete struct for memory management*/
struct Memory_T {
    Seq_T map;
    Seq_T unmapped;
    Seq_T sizes;
};

/* Function Declarations */
uint32_t getNextWord(FILE *fp);
void load_segment_zero(Memory_T memory, FILE *fp, int *size);
uint32_t *Memory_segment(Memory_T memory, uint32_t segment);


Memory_T Memory_new(uint32_t *seg_zero)
{
    Memory_T new = malloc(sizeof(*new));
    Seq_T map = Seq_new(0);
    Seq_T unmapped = Seq_new(0);
    Seq_T sizes = Seq_new(0);
    new->map = map;
    new->unmapped = unmapped;
    new->sizes = sizes;
    
    uint32_t *prog_size = malloc(sizeof(*prog_size));
    *prog_size = 0;
    Seq_addhi(new->sizes, prog_size);
    Seq_addhi(new->map, seg_zero);

    return new;
}

void Memory_free(Memory_T memory)
{
    while (Seq_length(memory->map) > 0) {
        free(Seq_remlo(memory->map));
    }
    Seq_free(&(memory->map));

    while (Seq_length(memory->sizes) > 0) {
        free(Seq_remlo(memory->sizes));
    }
    Seq_free(&(memory->sizes));

    while (Seq_length(memory->unmapped) > 0) {
        free(Seq_remlo(memory->unmapped));
    }
    Seq_free(&(memory->unmapped));

    free(memory);
}

uint32_t Memory_map(Memory_T memory, uint32_t size)
{
    assert(memory);
    
    uint32_t *seg_ptr = NULL;
    uint32_t seg_id = 0;
    uint32_t *new_seg = malloc(size * sizeof(uint32_t));
    uint32_t *seg_size = malloc(sizeof(*seg_size));
    *seg_size = size;

    /* Initializes all words to 0 in new segment */
    for (uint32_t i = 0; i < size; i++) {
        new_seg[i] = 0;
    }
    
    /* If we can reuse 32-bit IDs */
    if (Seq_length(memory->unmapped) > 0) {
        seg_ptr = (uint32_t *)Seq_remlo(memory->unmapped);
        seg_id = *seg_ptr;
        Seq_put(memory->map, seg_id, new_seg);
        free(seg_ptr);
        
        Seq_put(memory->sizes, seg_id, seg_size);
    }
    else {
        seg_id = Seq_length(memory->map);
        Seq_addhi(memory->map, new_seg);
        Seq_addhi(memory->sizes, seg_size);
        
    }
    
    return seg_id;
}

void Memory_unmap(Memory_T memory, uint32_t segment)
{
    assert(memory);

    void *old_seg = Seq_put(memory->map, segment, NULL);
    free(old_seg);

    void *old_size = Seq_put(memory->sizes, segment, NULL);
    free(old_size);

    uint32_t *new_id = malloc(sizeof(*new_id));
    *new_id = segment;

    Seq_addhi(memory->unmapped, new_id);
}

void Memory_put(Memory_T memory, uint32_t segment, uint32_t offset, 
                uint32_t value)
{
    assert(memory);
    assert(segment < (uint32_t)Seq_length(memory->map));

    uint32_t *block = Seq_get(memory->map, segment);
    block[offset] = value;
}

uint32_t Memory_get(Memory_T memory, uint32_t segment, uint32_t offset)
{
    assert(memory);
    //printf("%u, %u\n", segment, (uint32_t)Seq_length(memory->map));
    assert(segment < (uint32_t)Seq_length(memory->map));

    uint32_t *block = Seq_get(memory->map, segment);
    return block[offset];
}

void Memory_loadp(Memory_T memory, uint32_t segment)
{
    //uint32_t *block = Seq_get(memory->map, segment);
    uint32_t length = *(uint32_t *)Seq_get(memory->sizes, segment);
    uint32_t *curr_seg = Seq_get(memory->map, segment);
    
    uint32_t *new_seg = malloc(length * sizeof(uint32_t));
    for (uint32_t i = 0; i < length; i++) {
        uint32_t curr = *(curr_seg + i);
        *(new_seg + i) = curr;
    }
    uint32_t *old_zero = Seq_get(memory->map, 0);
    free(old_zero);
    Seq_put(memory->map, 0, new_seg);
}