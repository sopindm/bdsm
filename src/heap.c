#include <string.h>
#include "heap.h"

static void _swap(bdsm_vector* vector, size_t i1, size_t i2) {
    char buffer[vector->element_size];

    if(vector->mover == NULL) {
        memcpy(buffer, bdsm_vector_at(vector, i1),
               vector->element_size);
        memcpy(bdsm_vector_at(vector, i1), bdsm_vector_at(vector, i2),
               vector->element_size);
        memcpy(bdsm_vector_at(vector, i2), buffer,
               vector->element_size);
    } else {
        vector->mover(vector, buffer, bdsm_vector_at(vector, i1));
        vector->mover(vector, bdsm_vector_at(vector, i1),
                      bdsm_vector_at(vector, i2));
        vector->mover(vector, bdsm_vector_at(vector, i2), buffer);
    }
}

static void _go_down(bdsm_heap* heap, size_t at) {
    while(at < heap->vector.size / 2) {
        int less_than_left =
            heap->less(heap, bdsm_vector_at(&heap->vector, at),
                       bdsm_vector_at(&heap->vector, at * 2 + 1));

        int less_than_right =
            heap->vector.size > (at * 2 + 2)
                ? heap->less(
                      heap, bdsm_vector_at(&heap->vector, at),
                      bdsm_vector_at(&heap->vector, at * 2 + 2))
                : 1;

        if(less_than_left && less_than_right) {
            return;
        }

        if(less_than_right) {
            _swap(&heap->vector, at, at * 2 + 1);
            at *= 2;
            at++;
        } else if(less_than_left) {
            _swap(&heap->vector, at, at * 2 + 2);
            at++;
            at *= 2;
        } else {
            int left_less = heap->less(
                heap, bdsm_vector_at(&heap->vector, at * 2 + 1),
                bdsm_vector_at(&heap->vector, at * 2 + 2));

            if(left_less) {
                _swap(&heap->vector, at, at * 2 + 1);
                at *= 2;
                at++;
            } else {
                _swap(&heap->vector, at, at * 2 + 2);
                at++;
                at *= 2;
            }
        }
    }
}

void bdsm_heap_init(bdsm_heap* heap, bdsm_heap_less less) {
    heap->less = less;

    if(heap->vector.size == 0)
        return;

    for(size_t i = (heap->vector.size - 2) / 2;; i--) {
        _go_down(heap, i);
        if(i == 0)
            break;
    }
}

size_t bdsm_heap_size(bdsm_heap* heap) { return heap->vector.size; }
