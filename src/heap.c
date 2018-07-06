#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "heap.h"

/* This uses 1-indexed array for heap implementation.
 * Element at index 0 is just undefined/ignored
 */

#define LCHILD(x) (2 * x)
#define RCHILD(x) (2 * x + 1)
#define PARENT(x) (x / 2)

static bool heap_resize(struct heap *h, size_t new_cap)
{
    assert(h);
    assert(new_cap >= h->cap);

    struct heap_elem *heap_arr_new = realloc(h->heap_arr, new_cap * sizeof(h->heap_arr[0]));
    if(!heap_arr_new) return false;

    h->heap_arr = heap_arr_new;
    h->cap = new_cap;

    return true;
}

bool heap_init(struct heap *h, size_t cap)
{
    assert(h);

    cap++; /* 1-indexed array and cap could be 0 */
    h->n_elems = 0;
    h->heap_arr = calloc(cap, sizeof(h->heap_arr[0]));
    if(!h->heap_arr) return false;
    h->cap = cap;

    return true;
}

void heap_destroy(struct heap *h)
{
    assert(h);

    free(h->heap_arr);
    h->heap_arr = NULL;
    h->cap = 0;
    h->n_elems = 0;
}

bool heap_is_empty(const struct heap *h)
{
    assert(h);

    return h->n_elems == 0 ? true : false;
}

bool heap_insert(struct heap *h, struct heap_elem e)
{
    assert(h);

	if(h->n_elems + 1 == h->cap) {
        if(!heap_resize(h, h->cap * 2))
            return false;
	}

	h->n_elems++;
	h->heap_arr[h->n_elems] = e;

	/* Shifting up if necessary */
	size_t i = h->n_elems;
	while(PARENT(i) >= 1)
	{
		if(h->heap_arr[i].key >= h->heap_arr[PARENT(i)].key) {
			break;
        }
        else {
			/* Swap i with its parent */
			h->heap_arr[i] = h->heap_arr[PARENT(i)];
			h->heap_arr[PARENT(i)] = e; /* The ith element is e */
			i = PARENT(i);
		}
	}

	return true;
}

bool heap_get_min(struct heap *h, struct heap_elem *e)
{
    assert(h);
	if(heap_is_empty(h)) return false;

	*e = h->heap_arr[1];

    h->heap_arr[1] = h->heap_arr[h->n_elems];
	h->n_elems--;

    /* Shifting down if necessary */
	size_t i = 1;
	while(LCHILD(i) <= h->n_elems)
	{
		/* find the smaller child first */
		size_t smaller = LCHILD(i);
		if(RCHILD(i) <= h->n_elems) {
		    if(h->heap_arr[RCHILD(i)].key < h->heap_arr[smaller].key)
		        smaller = RCHILD(i);
        }

		if(h->heap_arr[i].key <= h->heap_arr[smaller].key) {
			break;
        }
		else {
			/* swap i with smaller */
			h->heap_arr[i] = h->heap_arr[smaller];
            /* n_elems + 1 is a copy of the ith element */
			h->heap_arr[smaller] = h->heap_arr[h->n_elems + 1];
			i = smaller;
		}
	}

	return true;
}
