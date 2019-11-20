#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

void die(char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  if (errno != 0) {
    perror("errno");
  }
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");

  va_end(args);
  
  exit(1);
}

int main(int argc, char** argv) {
  // Check cmd line args
  if (argc != 2) {
    die("usage: assembler <assembly-file>");
  }

  struct stat src_stat;
  if (stat(argv[1], &src_stat) != 0) {
    die("failed to find assembly-file: %s", argv[1]);
  }

  // Read bin file
  FILE *srcf = fopen(argv[1], "r");
  if (srcf == NULL) {
    die("failed to open assembly file: %s", argv[1]);
  }

  // Read lines
  char *line = NULL;
  size_t line_len = 0;
  ssize_t line_status;

  while ((line_status = getline(&line, &line_len, srcf)) != -1) {
    printf("line: %s\n", line);
    // Ignore empty lines
    if (line_len == 0) {
	 continue;
    }

    // Remove whitespace from beginning of lines
    size_t num_spaces = 0;
    while(num_spaces < line_len && isspace(line[0])) {
	 line = &line[1];
	 num_spaces++;
    }

    // Get tokens
    char *label = NULL;
    char *mnemonic = NULL;
    // TODO: Store operands, remove trailing commas and other

    char *tok_line = line;
    char *tok = strtok(tok_line, " ");
    while (tok != NULL) {
	 // If label
	 if (label == NULL && num_spaces == 0) {
	   label = tok;
	 } else if (mnemonic == NULL) { // No label
	   mnemonic = tok;
	 }

	 // Keep reading tokens
	 tok = strtok(NULL, " ");
    }

    if (label != NULL) {
	 printf("label: %s\n", label);
    } else {
	 printf("label: NULL\n");
    }

    printf("mnemonic: %s\n", mnemonic);
  }

  fclose(srcf);
}
