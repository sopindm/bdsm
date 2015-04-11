#include <stdlib.h>
#include "alloc.h"

void* bdsm_alloc(size_t size) { return malloc(size); }
void bdsm_free(void* memory) { return free(memory); }
