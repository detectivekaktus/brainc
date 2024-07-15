#include "interpreter.h"
#include "lexer.h"

Bytes_Array *init_bytes() {
  Bytes_Array *bytesarr = malloc(sizeof(Bytes_Array));
  bytesarr->bytes = calloc(MAX_BYTES, sizeof(char));
  bytesarr->pos = 0;
  return bytesarr;
}

void destroy_bytes(Bytes_Array *bytesarr) {
  free(bytesarr->bytes);
  free(bytesarr);
  bytesarr = NULL;
}

void destroy_interpreter_memory(Bytes_Array *bytesarr, Instructions *ins) {
  destroy_bytes(bytesarr);
  da_free(ins);
  ins = NULL;
}

int interpret(Instructions *ins)
{
  Bytes_Array *bytesarr = init_bytes();
  int ip = 0;
  Instruction in = ins->items[ip];
  while (in.kind != END_OF_FILE) {
    switch (in.kind) {
      case INCREMENT: {
        bytesarr->bytes[bytesarr->pos] += in.value;
        in = ins->items[++ip];
      } break;

      case DECREMENT: {
        bytesarr->bytes[bytesarr->pos] -= in.value;
        in = ins->items[++ip];
      } break;

      case INPUT: {
        for (int i = 0; i < in.value; i++) {
          bytesarr->bytes[bytesarr->pos] = fgetc(stdin);
        }
        in = ins->items[++ip];
      } break;

      case OUTPUT: {
        for (int i = 0; i < in.value; i++) {
          fprintf(stdout, "%c", bytesarr->bytes[bytesarr->pos]);
        }
        in = ins->items[++ip];
      } break;

      case SHIFT_RIGHT: {
        bytesarr->pos += in.value;
        if (bytesarr->pos >= MAX_BYTES) {
          fprintf(stderr, "RUNTIME ERROR: Bytes overflow. Reached the right bytes limit %d.\n", MAX_BYTES);
          return INTERPRETATION_FAIL;
        }
        in = ins->items[++ip];
      } break;

      case SHIFT_LEFT: {
        bytesarr->pos -= in.value;
        if (bytesarr->pos < 0) {
          fprintf(stderr, "RUNTIME ERROR: Bytes underflow. Can't shift left from position 0.\n");
          return INTERPRETATION_FAIL;
        }
        in = ins->items[++ip];
      } break;

      case IF_ZERO: {
        if (bytesarr->bytes[bytesarr->pos] == 0) {
          ip = in.value;
          in = ins->items[ip];
        }
        else {
          in = ins->items[++ip];
        }
      } break;

      case IF_NZERO: {
        if (bytesarr->bytes[bytesarr->pos] != 0) {
          ip = in.value;
          in = ins->items[ip];
        }
        else {
          in = ins->items[++ip];
        }
      } break;

      default: {
        fprintf(stderr, "Reached the unrechable end of interpretation.\n");
        return INTERPRETATION_FAIL;
      } break;
    }
  }
  destroy_interpreter_memory(bytesarr, ins);
  return INTERPRETATION_SUCCESS;
}
