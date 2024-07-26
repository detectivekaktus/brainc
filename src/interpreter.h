#ifndef BRAINC_INTERPRETER
#define BRAINC_INTERPRETER

#include "brainc.h"
#include "lexer.h"


typedef struct {
  char *bytes;
  int pos;
} Bytes_Array;

Bytes_Array *init_bytes();
void destroy_bytes(Bytes_Array *bytesarr);
void destroy_interpreter_memory(Bytes_Array *bytesarr, Instructions *ins);
int interpret(Instructions *ins);

#endif
