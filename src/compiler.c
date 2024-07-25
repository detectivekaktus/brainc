#include "compiler.h"

void generate_assembly(FILE *f, Instructions *ins)
{
  fprintf(f, "section .data\n");
  fprintf(f, "  runterr db \"RUNTIME ERROR.\",10\n");
  
  fprintf(f, "section .text\n");
  fprintf(f, "  extern calloc\n");
  fprintf(f, "  global _start\n");

  fprintf(f, "_start:\n");
}

int compile(Instructions *ins, const char *output_name)
{
  FILE *f = fopen("genasm.asm", "w");
  if (f == NULL) {
    fprintf(stderr, "COMPILATION ERROR: couldn't compile the program to the assembly representation.\n");
    return FAIL;
  }
  generate_assembly(f, ins);
  fclose(f);
  return SUCCESS;
}
