#pragma once
#include <stddef.h>

typedef struct bdsm_array {
    size_t element_size;
    size_t size;
    void* data;
} bdsm_array;

void bdsm_array_new(bdsm_array* array, size_t element_size,
                    size_t size);
void bdsm_array_free(bdsm_array* array);

void* bdsm_array_at(bdsm_array* array, size_t index);
