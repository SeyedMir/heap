#pragma once

#include <stdbool.h>
#include <stdint.h>

struct heap_elem {
    uint64_t key;
    uint64_t value;
};

struct heap {
    size_t n_elems;
    size_t cap;
    struct heap_elem *heap_arr;
};

bool heap_init(struct heap *h, size_t cap);
void heap_destroy(struct heap *h);
bool heap_is_empty(const struct heap *h);
bool heap_insert(struct heap *h, struct heap_elem e);
bool heap_get_min(struct heap *h, struct heap_elem *e);
