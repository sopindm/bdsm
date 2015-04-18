#pragma once
#include <vector.h>

struct bdsm_heap;
typedef int (*bdsm_heap_less)(struct bdsm_heap* heap,
                              const void* value1, const void* value2);

typedef struct bdsm_heap {
    bdsm_vector vector;
    bdsm_heap_less less;
} bdsm_heap;

void bdsm_heap_init(bdsm_heap* heap,      // makes heap using
                    bdsm_heap_less less); // underlying vector

size_t bdsm_heap_size(bdsm_heap* heap);

void* bdsm_heap_top(bdsm_heap* heap);
void bdsm_heap_pop(bdsm_heap* heap);

void* bdsm_heap_allocate(bdsm_heap* heap); // allocates memory for one
                                           // more element
void bdsm_heap_commit(bdsm_heap* heap); // moves last element to right
                                        // place in heap
