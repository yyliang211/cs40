#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "memory.h"
#include "bitpack.h"
#include "seq.h"

void new_free_test();
void map_unmap_test();
void more_test();
void map10_test();
void load_test();

int main()
{
    printf("New and Free test: ");
    new_free_test();
    printf("Success!\n");
    
    printf("Map-Unmap test: ");
    map_unmap_test();
    printf("Success!\n");

    printf("Map-10 test: ");
    map10_test();
    printf("Success!\n");

    printf("Loadp test: ");
    load_test();
    printf("Success!\n");
    
}

void new_free_test()
{
    uint32_t *sz = malloc(4);
    Memory_T mem = Memory_new(sz);
    Memory_free(mem);
}

void map_unmap_test()
{
    uint32_t *sz = malloc(4);
    Memory_T mem = Memory_new(sz);
    uint32_t new_id = Memory_map(mem, 10);
    Memory_unmap(mem, new_id);
    Memory_free(mem);
}

void more_test()
{
    uint32_t *sz = malloc(4);
    Memory_T mem = Memory_new(sz);
    uint32_t seg_one = Memory_map(mem, 12);
    uint32_t seg_two = Memory_map(mem, 30);
    uint32_t seg_three = Memory_map(mem, 1);
    uint32_t seg_four = Memory_map(mem, 50);
    uint32_t seg_five = Memory_map(mem, 9);
    printf("seg one id: %d\n", seg_one);
    printf("seg two id: %d\n", seg_two);
    printf("seg three id: %d\n", seg_three);
    printf("seg four id: %d\n", seg_four);
    printf("seg five id: %d\n", seg_five);
    
    Memory_put(mem, new_id, 1, 3);
    Memory_unmap(mem, new_id);
    Memory_free(mem);
}

void map10_test()
{
    uint32_t *sz = malloc(4);
    Memory_T mem = Memory_new(sz);
    uint32_t new_id = Memory_map(mem, 10);
    for (uint32_t i = 0; i < 10; i++) {
        Memory_put(mem, new_id, i, i);
    }
    for (uint32_t i = 0; i < 10; i++) {
        uint32_t curr = Memory_get(mem, new_id, i);
        if(curr != i) {
            printf("Failure\n");
            exit(EXIT_FAILURE);
        }
    }
    Memory_unmap(mem, new_id);
    Memory_free(mem);
}

void load_test()
{
    uint32_t *sz = malloc(4);
    Memory_T mem = Memory_new(sz);
    uint32_t new_id = Memory_map(mem, 10);
    for (uint32_t i = 0; i < 10; i++) {
        Memory_put(mem, new_id, i, i);
    }
    Memory_loadp(mem, new_id);
    for (uint32_t i = 0; i < 10; i++) {
        uint32_t curr = Memory_get(mem, 0, i);
        if(curr != i) {
            printf("Failure\n");
            exit(EXIT_FAILURE);
        }
    }
    
    Memory_unmap(mem, new_id);
    Memory_free(mem);
}
