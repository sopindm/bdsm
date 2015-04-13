#include "alloc.h"
#include "dlist.h"

void bdsm_dlist_init(bdsm_dlist* list) {
    list->size = 0;

    list->root.next = &list->root;
    list->root.prev = NULL;
}

void bdsm_dlist_free(bdsm_dlist* list) { (void)list; }

bdsm_dlist_node* bdsm_dlist_begin(bdsm_dlist* list) {
    return list->root.next;
}
bdsm_dlist_node* bdsm_dlist_end(bdsm_dlist* list) {
    return &list->root;
}

void* bdsm_dlist_insert(bdsm_dlist* list, bdsm_dlist_node* before,
                        size_t size) {
    list->size++;
    bdsm_dlist_node* node =
        (bdsm_dlist_node*)bdsm_alloc(sizeof(bdsm_dlist_node) + size);

    node->next = before;
    node->prev = before->prev;
    before->prev = node;

    if(node->prev == NULL)
        list->root.next = node;
    else
        node->prev->next = node;

    return node + 1;
}

void* bdsm_dlist_get(bdsm_dlist_node* node) { return node + 1; }
