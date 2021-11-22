#ifndef MEMORY
#define MEMORY

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "uarray.h"

typedef struct Memory_T *Memory_T;


extern Memory_T Memory_new(UArray_T seg_zero);
extern void Memory_free(Memory_T memory);

extern uint32_t Memory_map(Memory_T memory, uint32_t size);
extern void Memory_unmap(Memory_T memory, uint32_t id);

extern void Memory_put(Memory_T memory, uint32_t segment, uint32_t offset, 
                                                          uint32_t value);
extern uint32_t Memory_get(Memory_T memory, uint32_t segment, uint32_t offset);

extern void Memory_loadp(Memory_T memory, uint32_t segment);

#endif