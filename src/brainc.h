#ifndef BRAINC_IMPLEMENTATION
#define BRAINC_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_BYTES           1024
#define MAX_OUTPUT_FILENAME 1024
#define DA_INIT_CAPACITY    64
#define SUCCESS             0
#define FAIL                1

typedef struct {
  int argc;
  char **argv;
  int index;
} Args;

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

#define da_heap_free(da)                                                            \
  do {                                                                              \
    free((da)->items);                                                              \
    free(da);                                                                       \
  } while (0)

int main(int argc, char **argv);
char *next_arg(Args *args);
char *read_entire_file(char *filename);
void usage(char *name);
void help(void);

#endif
