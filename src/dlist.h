#pragma once
#include <stddef.h>

typedef struct bdsm_dlist_node {
    struct bdsm_dlist_node* prev;
    struct bdsm_dlist_node* next;
} bdsm_dlist_node;

typedef struct bdsm_dlist {
    size_t size;
    bdsm_dlist_node root;
} bdsm_dlist;

void bdsm_dlist_init(bdsm_dlist*);
void bdsm_dlist_free(bdsm_dlist*);

bdsm_dlist_node* bdsm_dlist_begin(bdsm_dlist*);
bdsm_dlist_node* bdsm_dlist_end(bdsm_dlist*);

void* bdsm_dlist_get(bdsm_dlist_node*);

void* bdsm_dlist_insert(bdsm_dlist*, bdsm_dlist_node* before,
                        size_t size);
void bdsm_dlist_erase(bdsm_dlist*, bdsm_dlist_node* before);

void* bdsm_dlist_insert_after(bdsm_dlist*, bdsm_dlist_node*,
                              size_t size);
void bdsm_dlist_erase_after(bdsm_dlist*, bdsm_dlist_node*);
