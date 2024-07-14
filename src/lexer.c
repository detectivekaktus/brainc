#include "lexer.h"

bool is_valid_command(char c)
{
  return strchr("<>.,+-[]", c) != NULL;
}

char lexer_next(Lexer *lexer)
{
  while (!is_valid_command((lexer->content[lexer->index++]))) {}
  return lexer->content[lexer->index++];
}
