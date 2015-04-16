#include <stdlib.h>
#include "alloc.h"
#include "vector.h"

void bdsm_vector_new(bdsm_vector* vector, size_t element_size,
                     size_t size, bdsm_vector_mover mover) {
    vector->element_size = element_size;
    vector->size = size;
    vector->allocated_size = size;
    vector->mover = mover;

    vector->data = bdsm_alloc(element_size * size);
}

void bdsm_vector_free(bdsm_vector* vector) {
    bdsm_free(vector->data);
}

void* bdsm_vector_at(bdsm_vector* vector, size_t index) {
    return vector->data + vector->element_size * index;
}

void bdsm_vector_resize(bdsm_vector* vector, size_t size) {
    if(vector->allocated_size >= size) {
        vector->size = size;
        return;
    }

    size_t new_size = vector->allocated_size;
    while(new_size < size)
        new_size *= 2;

    if(vector->mover == NULL)
        vector->data = bdsm_realloc(vector->data,
                                    new_size * vector->element_size);
    else {
        void* new_data = bdsm_alloc(new_size * vector->element_size);

        for(size_t i = 0; i < vector->size; i++)
            vector->mover(vector, new_data + i * vector->element_size,
                          vector->data + i * vector->element_size);

        bdsm_free(vector->data);
        vector->data = new_data;
    }

    vector->size = size;
    vector->allocated_size = new_size;
}

void* bdsm_vector_push(bdsm_vector* vector) {
    bdsm_vector_resize(vector, vector->size + 1);
    return bdsm_vector_at(vector, vector->size - 1);
}

void bdsm_vector_pop(bdsm_vector* vector) {
    bdsm_vector_resize(vector, vector->size - 1);
}
