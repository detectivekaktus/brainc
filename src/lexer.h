#ifndef BRAINC_LEXER
#define BRAINC_LEXER

#include "brainc.h"

typedef enum {
  INCREMENT   = '+',
  DECREMENT   = '-',
  OUTPUT      = '.',
  INPUT       = ',',
  SHIFT_RIGHT = '>',
  SHIFT_LEFT  = '<',
  IF_ZERO     = '[',
  IF_NZERO    = ']',
  END_OF_FILE
} Instruction_Kind;

typedef struct {
  Instruction_Kind kind;
  int value;
} Instruction;

typedef struct {
  Instruction *items;
  size_t size;
  size_t capacity;
} Instructions;

typedef struct {
  size_t *items;
  size_t size;
  size_t capacity;
} Addresses;

typedef struct {
  char *content;
  size_t index;
} Lexer;

bool is_valid_command(char c);
char lexer_next(Lexer *lexer);
void destroy_lexer_memory(char *source, Addresses *addrs);
Instructions *translate_program(char *source);

#endif
