#include <stdlib.h>
#include "alloc.h"
#include "slist.h"

void bdsm_slist_init(bdsm_slist* list) {
    list->size = 0;
    list->root.next = NULL;
    list->end = NULL;
}

void bdsm_slist_free(bdsm_slist* list) {
    bdsm_slist_node* it = bdsm_slist_begin(list);
    while(it != NULL) {
        bdsm_slist_node* next = it->next;
        bdsm_free(it);
        it = next;
    }
}

bdsm_slist_node* bdsm_slist_begin(bdsm_slist* list) {
    return list->root.next;
}
bdsm_slist_node* bdsm_slist_end(bdsm_slist* list) {
    return list->end;
}

void* bdsm_slist_get(bdsm_slist_node* node) {
    return node + 1;
}
void* bdsm_slist_insert(bdsm_slist* list, bdsm_slist_node* after,
                        size_t size) {
    bdsm_slist_node* node =
        (bdsm_slist_node*)bdsm_alloc(sizeof(bdsm_slist_node) + size);
    node->next = NULL;

    list->size++;
    if(after->next == NULL)
        list->end = node;
    else
        node->next = after->next;

    after->next = node;

    return node + 1;
}

void bdsm_slist_erase(bdsm_slist* list, bdsm_slist_node* after) {
    list->size--;

    bdsm_slist_node* next = after->next;
    if(after == &list->root)
        list->end = NULL;
    else if(next == list->end)
        list->end = after;

    after->next = next->next;

    free(next);
}
