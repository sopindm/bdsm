#pragma once
#include <stddef.h>

void* bdsm_alloc(size_t size);
void bdsm_free(void* data);
