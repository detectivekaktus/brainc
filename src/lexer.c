#include "lexer.h"
#include <stdio.h>

bool is_valid_command(char c)
{
  return strchr("<>.,+-[]", c) != NULL;
}

char lexer_next(Lexer *lexer)
{
  while (!is_valid_command((lexer->content[lexer->index++]))) {}
  return lexer->content[--lexer->index];
}

Instructions *translate_program(char *source)
{
  Lexer lexer = {
    .content=source,
    .index=0
  };
  Instructions *ins = da_heap_alloc(Instructions);

  int c;
  while ((c = lexer_next(&lexer)) != '\0') {
    switch (c) {
      case '+':
      case '-':
      case '<':
      case '>':
      case '.':
      case ',': {
        lexer.index++;
      } break;

      case '[': {
        lexer.index++;
      } break;

      case ']': {
        assert(0 && "] is not implemented\n");
        lexer.index++;
      } break;

      default: {
        fprintf(stderr, "INTERNAL ERROR: Met an unexpected token %c during the intermediate representation convertion.\n", c);
        exit(1);
      } break;
    }
  }
  free(source);
  return ins;
}
