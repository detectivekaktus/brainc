#include "brainc.h"
#include "lexer.h"

typedef struct {
  int argc;
  char **argv;
  int index;
} Args;

char *next_arg(Args *args)
{
  return args->argv[++args->index];
}

char *read_entire_file(char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) return NULL;
  fseek(file, 0, SEEK_END);
  int len = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *str = malloc(sizeof(char) * (len + 1));
  char c;
  int i = 0;
  while ((c = fgetc(file)) != EOF) {
    str[i++] = c;
  }
  str[i] = '\0';
  fclose(file);
  return str;
}

void usage(char *name)
{
  printf("usage: %s <filename.bf> | -i <filename.bf>\n", name);
  printf("  -i | --interpret: use interpretation only mode to execute the program.\n");
}

int main(int argc, char **argv)
{
  Args args = {
    .argc=argc,
    .argv=argv,
    .index=0
  };

  if (args.argc < 2) {
    fprintf(stderr, "ERROR: no command or file specified.\n");
    usage(args.argv[args.index]);
    return 1;
  }

  char *arg = next_arg(&args);
  if (strcmp(arg, "-i") == 0 || strcmp(arg, "--interpret") == 0) {
    arg = next_arg(&args);
    char *source = read_entire_file(arg);
    if (source == NULL) {
      fprintf(stderr, "INTERNAL ERROR: Couldn't read the file %s.\n", arg);
      return 1;
    }
    Instructions *ins = translate_program(source);
  }
  else {
    fprintf(stderr, "ERROR: unknown command %s.\n", arg);
    usage(args.argv[0]);
    return 1;
  }

  return 0;
}
