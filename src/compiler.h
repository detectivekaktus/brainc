#ifndef BRAINC_COMPILER
#define BRAINC_COMPILER

#include "brainc.h"
#include "lexer.h"

bool generate_assembly(Instructions *ins, const char *filename);
bool compile_assembly(const char *output_name);
int compile(Instructions *ins, const char *output_name);

#endif
