#pragma once
#include <stddef.h>

void* bdsm_alloc(size_t size);
void bdsm_free(void* data);
void* bdsm_realloc(void* what, size_t size);
