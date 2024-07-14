#include "lexer.h"

bool is_valid_command(char c)
{
  return strchr("<>.,+-[]", c) != NULL;
}
