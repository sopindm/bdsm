#pragma once
#include <stddef.h>

struct bdsm_vector;
typedef void (*bdsm_vector_mover)(struct bdsm_vector* vector,
                                  void* to, void* from);
typedef struct bdsm_vector {
    size_t element_size;
    size_t size;
    size_t allocated_size;
    void* data;
    bdsm_vector_mover mover;
} bdsm_vector;

void bdsm_vector_new(bdsm_vector* vector, size_t element_size,
                     size_t size, bdsm_vector_mover mover);
void bdsm_vector_free(bdsm_vector* vector);

void bdsm_vector_resize(bdsm_vector* vector, size_t new_size);

void* bdsm_vector_at(bdsm_vector* vector, size_t index);

void* bdsm_vector_push(bdsm_vector* vector);
void bdsm_vector_pop(bdsm_vector* vector);
