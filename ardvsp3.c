#include <stdlib.h>
#include <stdio.h>

void main(int argc, char* argv[]) {
  FILE *source = fopen(argv[1], "r");
  FILE *dump = fopen(argv[2], "w");
  char c;
  int num;
  for (num = 0, c = fgetc(source); c != EOF; c = fgetc(source))
    if (c >= '0' && c <= '9')
      if (num == 0)
	num = 1;
      else
	fprintf(dump, "%c", c);
    else if (((c >= 'a' && c <= 'z')
	      || (c == '\n') || (c == ' ')) && c != 'x') {
      fprintf(dump, "%c", c);
      num = 0;
    }
    else if (c >= 'A' && c <= 'Z') {
      fprintf(dump, "%c", c+'a'-'A');
      num = 0;
    }
    else if (c == '/') {
      num = 0;
      while ((c = fgetc(source)) != '\n')
	1;
      fprintf(dump, "\n");
    }
  fclose(source);
  fclose(dump);
}
