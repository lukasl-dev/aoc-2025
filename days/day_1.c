#include "sys/types.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIAL_LENGTH 100
#define START_POS 50

typedef char rotation_t;
#define ROT_LEFT (rotation_t)'L'
#define ROT_RIGHT (rotation_t)'R'

typedef struct {
  rotation_t rot;
  int steps;
} instruction_t;

bool parse(char *raw, instruction_t *instr) {
  if (strlen(raw) < 2) {
    return false;
  }
  instr->rot = raw[0];
  instr->steps = atoi(raw + 1);
  return true;
}

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

  int pos = START_POS;
  int solution_1 = 0;
  int solution_2 = 0;

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, input_file)) != -1) {
    if (read > 0 && line[read - 1] == '\n') {
      line[read - 1] = '\0';
      read -= 1;
    }
    if (read == 0) {
      continue;
    }

    instruction_t instr = {0};
    if (!parse(line, &instr)) {
      printf("error: invalid instruction '%s'\n", line);
      free(line);
      fclose(input_file);
      return EXIT_FAILURE;
    }

    switch (instr.rot) {
    case ROT_LEFT:
      solution_2 +=
          ((DIAL_LENGTH - pos) % DIAL_LENGTH + instr.steps) / DIAL_LENGTH;
      pos = ((pos - instr.steps) % DIAL_LENGTH + DIAL_LENGTH) % DIAL_LENGTH;
      break;

    case ROT_RIGHT:
      solution_2 += (pos + instr.steps) / DIAL_LENGTH;
      pos = (pos + instr.steps) % DIAL_LENGTH;
      break;

    default:
      printf("error: invalid rotation '%c'\n", instr.rot);
      free(line);
      fclose(input_file);
      return EXIT_FAILURE;
    }

    if (pos == 0) {
      solution_1++;
    }
  }

  if (line) {
    free(line);
  }
  fclose(input_file);

  printf("1. Solution: %d\n", solution_1);
  printf("2. Solution: %d\n", solution_2);

  return EXIT_SUCCESS;
}
