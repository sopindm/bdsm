#include <stdlib.h>
#include "list.h"

void bdsm_slist_new(bdsm_slist* list, size_t alignment) {
    list->alignment = alignment;
    list->size = 0;
    list->root.next = NULL;
    list->end = NULL;
}

static size_t _align(size_t what, size_t alignment) {
    return (what + alignment - 1) / alignment * alignment;
}

bdsm_slist_node* bdsm_slist_begin(bdsm_slist* list) {
    return list->root.next;
}
bdsm_slist_node* bdsm_slist_end(bdsm_slist* list) {
    return list->end;
}

void* bdsm_slist_get(bdsm_slist* list, bdsm_slist_node* node) {
    return (void*)_align((size_t)(&node->next + 1), list->alignment);
}
void* bdsm_slist_insert(bdsm_slist* list, bdsm_slist_node* after,
                        size_t size) {
    size_t allocationSize =
        _align(sizeof(bdsm_slist_node), list->alignment) + size;
    bdsm_slist_node* node = (bdsm_slist_node*)malloc(allocationSize);
    node->next = NULL;

    list->size++;
    if(after->next == NULL)
        list->end = node;
    else
        node->next = after->next;

    after->next = node;

    return (void*)_align((size_t)(node + 1), list->alignment);
}

void bdsm_slist_erase(bdsm_slist* list, bdsm_slist_node* after) {
    (void)list;

    bdsm_slist_node* next = after->next;
    after->next = next->next;

    free(next);
}
