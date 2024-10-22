#include "compiler.h"

void free_compiler_memory(Instructions *ins)
{
  da_heap_free(ins);
  ins = NULL;
}

bool generate_assembly(Instructions *ins, const char *filename)
{
  FILE *f = fopen(filename, "w");
  if (f == NULL) {
    fprintf(stderr, "COMPILATION ERROR: couldn't generate assembly with %s filename.\n", filename);
    return false;
  }
  fprintf(f, "section .data\n");
  fprintf(f, "  bytesarr times %d db 0\n", MAX_BYTES);
  fprintf(f, "  pos dd 0\n");

  fprintf(f, "section .text\n");
  fprintf(f, "  global _start\n");

  fprintf(f, "_start:\n");
  int ip = 0;
  bool res = false;
  Instruction in = ins->items[ip];
  while (in.kind != END_OF_FILE) {
    switch (in.kind) {
      case INCREMENT: {
        fprintf(f, "  mov ebx, dword [pos]\n");
        fprintf(f, "  add byte [bytesarr + ebx], %d\n", in.value);
        in = ins->items[++ip];
      } break;

      case DECREMENT: {
        fprintf(f, "  mov ebx, dword [pos]\n");
        fprintf(f, "  sub byte [bytesarr + ebx], %d\n", in.value);
        in = ins->items[++ip];
      } break;

      case INPUT: {
        fprintf(f, "  mov ebx, dword [pos]\n");
        for (int i = 0; i < in.value; i++) {
          fprintf(f, "  mov rax, 0\n");
          fprintf(f, "  mov rdi, 0\n");
          fprintf(f, "  lea rsi, [bytesarr + ebx]\n");
          fprintf(f, "  mov rdx, 1\n");
          fprintf(f, "  syscall\n");
        }
        in = ins->items[++ip];
      } break;

      case OUTPUT: {
        fprintf(f, "  mov ebx, dword [pos]\n");
        for (int i = 0; i < in.value; i++) {
          fprintf(f, "  mov rax, 1\n");
          fprintf(f, "  mov rdi, 1\n");
          fprintf(f, "  lea rsi, [bytesarr + ebx]\n");
          fprintf(f, "  mov rdx, 1\n");
          fprintf(f, "  syscall\n");
        }
        in = ins->items[++ip];
      } break;

      case SHIFT_RIGHT: {
        fprintf(f, "  mov ebx, dword [pos]\n");
        fprintf(f, "  add ebx, %d\n", in.value);
        fprintf(f, "  mov [pos], ebx\n");
        in = ins->items[++ip];
      } break;

      case SHIFT_LEFT: {
        fprintf(f, "  mov ebx, dword [pos]\n");
        fprintf(f, "  sub ebx, %d\n", in.value);
        fprintf(f, "  mov [pos], ebx\n");
        in = ins->items[++ip];
      } break;

      case IF_ZERO: {
        fprintf(f, "  mov ebx, dword [pos]\n");
        fprintf(f, "  mov al, byte [bytesarr + ebx]\n");
        fprintf(f, "  test al, al\n");
        fprintf(f, "  jz addr_%d\n", in.value);
        fprintf(f, "addr_%d:\n", ip + 1);
        in = ins->items[++ip];
      } break;

     case IF_NZERO: {
        fprintf(f, "  mov ebx, dword [pos]\n");
        fprintf(f, "  mov al, byte [bytesarr + ebx]\n");
        fprintf(f, "  test al, al\n");
        fprintf(f, "  jnz addr_%d\n", in.value);
        fprintf(f, "addr_%d:\n", ip + 1);
        in = ins->items[++ip];
      } break;

      default: {
        fprintf(stderr, "Reached the unreachable end of compilation.\n");
        res = false;
      } break;
    }
  }
  fprintf(f, "  mov rax, 60\n");
  fprintf(f, "  mov rdi, 0\n");
  fprintf(f, "  syscall\n");
  res = true;
  fclose(f);
  free_compiler_memory(ins);
  return res;
}

bool compile_assembly(const char *output_name)
{
  if (system("nasm -f ELF64 -g source.asm -o source.o") != 0) {
    fprintf(stderr, "COMPILATION ERROR: couldn't produce the object file.\n");
    return false;
  }
  if (strlen(output_name) > 1000) {
    fprintf(stderr, "COMPILATION ERROR: output filename length cannot be bigger than 1000.\n");
    return false;
  }
  char ld[MAX_OUTPUT_FILENAME];
  sprintf(ld, "ld source.o -O3 -o %s", output_name);
  if (system(ld) != 0) {
    fprintf(stderr, "COMPILATION ERROR: couldn't link the object file.\n");
    return false;
  }
  return true;
}

int compile(Instructions *ins, const char *output_name)
{
  if (!generate_assembly(ins, "source.asm")) return FAIL;
  if (!compile_assembly(output_name)) return FAIL;
  return SUCCESS;
}
