#include "alloc.h"
#include "array.h"

void bdsm_array_new(bdsm_array* array, size_t element_size,
                    size_t size) {
    array->element_size = element_size;
    array->size = size;
    array->data = bdsm_alloc(element_size * size);
}

void bdsm_array_free(bdsm_array* array) { bdsm_free(array->data); }

void* bdsm_array_at(bdsm_array* array, size_t at) {
    return array->data + array->element_size * at;
}
