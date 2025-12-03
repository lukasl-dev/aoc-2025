#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc <= 1) {
    printf("usage: %s file\n", argv[0]);
    return EXIT_FAILURE;
  }
  char *filename = argv[1];

  FILE *input_file = fopen(filename, "r");
  if (input_file == NULL) {
    printf("error: file '%s' not found\n", filename);
    return EXIT_FAILURE;
  }

  fclose(input_file);

  return EXIT_SUCCESS;
}
