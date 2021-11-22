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
};

/* Function Declarations */
uint32_t getNextWord(FILE *fp);
void init_segment(UArray_T segment);

Memory_T Memory_new(UArray_T seg_zero)
{
    Memory_T new = malloc(sizeof(*new));
    Seq_T map = Seq_new(0);
    Seq_T unmapped = Seq_new(0);
    
    new->map = map;
    new->unmapped = unmapped;
    
    Seq_addhi(new->map, seg_zero);

    return new;
}

void Memory_free(Memory_T memory)
{
    while (Seq_length(memory->map) > 0) {
        UArray_T arr = Seq_remlo(memory->map);
        if (arr != NULL) {
            UArray_free(&arr);
        }
    }
    Seq_free(&(memory->map));

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

    UArray_T new_seg = UArray_new(size, sizeof(uint32_t));
    
    /* Initializes all words to 0 in new segment */
    init_segment(new_seg);
    
    /* If we can reuse 32-bit IDs */
    if (Seq_length(memory->unmapped) > 0) {
        seg_ptr = (uint32_t *)Seq_remlo(memory->unmapped);
        seg_id = *seg_ptr;
        Seq_put(memory->map, seg_id, new_seg);
        free(seg_ptr);
    }
    else {
        seg_id = Seq_length(memory->map);
        Seq_addhi(memory->map, new_seg);
    }
    
    return seg_id;
}

void init_segment(UArray_T segment)
{
    uint32_t len = UArray_length(segment);
    for (uint32_t i = 0; i < len; i++) {
        uint32_t *elem = UArray_at(segment, i);
        *elem = 0;
    }
}

void Memory_unmap(Memory_T memory, uint32_t segment)
{
    assert(memory);

    UArray_T old_seg = Seq_put(memory->map, segment, NULL);
    UArray_free(&old_seg);

    uint32_t *new_id = malloc(sizeof(*new_id));
    *new_id = segment;

    Seq_addhi(memory->unmapped, new_id);
}

void Memory_put(Memory_T memory, uint32_t segment, uint32_t offset, 
                uint32_t value)
{
    assert(memory);
    assert(segment < (uint32_t)Seq_length(memory->map));

    UArray_T block = Seq_get(memory->map, segment);
    uint32_t *word = (uint32_t *)UArray_at(block, offset);
    *word = value;
}

uint32_t Memory_get(Memory_T memory, uint32_t segment, uint32_t offset)
{
    assert(memory);
    //printf("%u, %u\n", segment, (uint32_t)Seq_length(memory->map));
    assert(segment < (uint32_t)Seq_length(memory->map));

    UArray_T block = Seq_get(memory->map, segment);
    return *((uint32_t *)UArray_at(block, offset));
}

void Memory_loadp(Memory_T memory, uint32_t segment)
{
    UArray_T curr_seg = Seq_get(memory->map, segment);
    UArray_T new_seg = UArray_copy(curr_seg, UArray_length(curr_seg));
    
    UArray_T old_zero = Seq_get(memory->map, 0);
    UArray_free(&old_zero);
    Seq_put(memory->map, 0, new_seg);
}