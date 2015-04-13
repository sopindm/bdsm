#pragma once
#include <stddef.h>

typedef struct bdsm_slist_node {
    struct bdsm_slist_node* next;
} bdsm_slist_node;

typedef struct bdsm_slist {
    size_t size;
    bdsm_slist_node root;
    bdsm_slist_node* end;
} bdsm_slist;

void bdsm_slist_init(bdsm_slist*);
void bdsm_slist_free(bdsm_slist*);

bdsm_slist_node* bdsm_slist_begin(bdsm_slist*);
bdsm_slist_node* bdsm_slist_end(bdsm_slist*);

void* bdsm_slist_get(bdsm_slist_node*);
void* bdsm_slist_insert(bdsm_slist*, bdsm_slist_node* after,
                        size_t size);
void bdsm_slist_erase(bdsm_slist*, bdsm_slist_node* after);
