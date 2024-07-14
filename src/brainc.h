#ifndef BRAINC_IMPLEMENTATION
#define BRAINC_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define DA_INIT_CAPACITY 64

#define da_heap_alloc(type) (type *)calloc(1, sizeof(type));

#define da_append(da, item)                                                         \
  do {                                                                              \
    if ((da)->size >= (da)->capacity) {                                             \
      (da)->capacity = (da)->capacity == 0 ? DA_INIT_CAPACITY : (da)->capacity * 2; \
      (da)->items = realloc((da)->items, (da)->capacity * sizeof(*(da)->items));    \
    }                                                                               \
    (da)->items[(da)->size++] = (item);                                             \
  } while (0)

#define da_free(da) free(da->items);

#endif
