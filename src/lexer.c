#include "lexer.h"
#include "brainc.h"

bool is_valid_command(char c)
{
  return strchr("<>.,+-[]", c) != NULL;
}

char lexer_next(Lexer *lexer)
{
  while (!is_valid_command((lexer->content[lexer->index])))
    lexer->index++;
  return lexer->content[lexer->index++];
}

void destroy_lexer_memory(char *source, Addresses *addrs)
{
  free(source);
  da_free(addrs);
}

Instructions *translate_program(char *source)
{
  Lexer lexer = {
    .content=source,
    .index=0
  };
  Instructions *ins = da_heap_alloc(Instructions);
  Addresses addrs = {0};

  char c = lexer_next(&lexer);
  while (c != '\0') {
    switch (c) {
      case '+':
      case '-':
      case '<':
      case '>':
      case '.':
      case ',': {
        int value = 1;
        char n = lexer_next(&lexer);
        while (c == n) {
          n = lexer_next(&lexer);
          value++;
        }
        Instruction in = {
          .kind=c,
          .value=value
        };
        da_append(ins, in);
        c = n;
      } break;

      case '[': {
        Instruction in = {
          .kind=c,
          .value=0
        };
        da_append(&addrs, ins->size + 1);
        da_append(ins, in);
        c = lexer_next(&lexer);
      } break;

      case ']': {
        if (addrs.size == 0) {
          fprintf(stderr, "SYNTAX ERROR: ] doesn't have a closing pair.\n");
          exit(1);
        }
        size_t address = addrs.items[addrs.size - 1];
        Instruction in = {
          .kind=c,
          .value=address
        };
        ins->items[address - 1].value = ins->size + 1;
        addrs.size--;
        da_append(ins, in);
        c = lexer_next(&lexer);
      } break;

      default: {
        fprintf(stderr, "INTERNAL ERROR: Met unexpected token %c during the intermediate representation convertion.\n", c);
        exit(1);
      } break;
    }
  }
  Instruction eofin = {
    .kind = END_OF_FILE,
    .value = 0
  };
  da_append(ins, eofin);
  destroy_lexer_memory(source, &addrs);
  return ins;
}
