#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "heap.h"

bool test_one()
{
    struct heap h;
    if(!heap_init(&h, 1)) return false;

    struct heap_elem e = {1, 2};
    struct heap_elem e_min = {0};

    if(!heap_insert(&h, e)) return false;
    if(!heap_get_min(&h, &e_min)) return false;
    if(memcmp(&e, &e_min, sizeof(e))) return false;

    heap_destroy(&h);

    return true;
}

bool test_multi()
{
    struct heap h;
    if(!heap_init(&h, 1)) return false;

    struct heap_elem e_min = {0};

    if(!heap_insert(&h, (struct heap_elem){2, 0})) return false;
    if(!heap_insert(&h, (struct heap_elem){1, 0})) return false;
    if(!heap_insert(&h, (struct heap_elem){3, 0})) return false;
    if(!heap_get_min(&h, &e_min) || e_min.key != 1) return false;
    if(!heap_get_min(&h, &e_min) || e_min.key != 2) return false;
    if(!heap_get_min(&h, &e_min) || e_min.key != 3) return false;

    heap_destroy(&h);

    return true;
}

int main(int argc, char **argv)
{
    bool ret = true;

    ret = ret && test_one();
    printf("test_one.....%s\n", ret ? "PASS" : "FAIL");
    ret = ret && test_multi();
    printf("test_multi.....%s\n", ret ? "PASS" : "FAIL");

    return ret ? 0 : 1;
}
