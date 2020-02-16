#include <stdlib.h>
#include <stdio.h>

void main(int argc, char* argv[]) {
  FILE *source = fopen(argv[1], "r");
  FILE *dump = fopen(argv[2], "w");
  char c;
  for (c = fgetc(source); c != EOF; c = fgetc(source))
    if (((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
	 (c >= 'A' && c <= 'Z') || (c == '\n')) && c != 'x')
      fprintf(dump, "%c", c);
    else if (c == '/') {
      while ((c = fgetc(source)) != '\n')
	1;
      fprintf(dump, "\n");
    }
  fclose(source);
  fclose(dump);
}
