#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

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
    die("usage: emulator <bin-file>");
  }

  struct stat src_stat;
  if (stat(argv[1], &src_stat) != 0) {
    die("failed to find bin-file: %s", argv[1]);
  }

  // Read bin file
  FILE *srcf = fopen(argv[1], "rb");

  

  fclose(srcf);
}
