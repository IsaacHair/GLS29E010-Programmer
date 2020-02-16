#include <stdlib.h>
#include <stdio.h>

void main(int argc, char* argv[]) {
  FILE *source = fopen(argv[1], "r");
  FILE *dump = fopen(argv[2], "w");
  char c;
  for (c = fgetc(source); 1; c = fgetc(source)) {
    if (c == '\n')
      fprintf(dump, "\n");
    else if (c == ' ')
      fprintf(dump, " ");
    else if (c == '0')
      if (((c = fgetc(source)) >= '0' && c <= '9') ||
	  (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
	fprintf(dump, "0%c", c);
      else
	fprintf(dump, "0%c", c);
    else if (c == 'a' || c == 'A') {
      if ((c = fgetc(source)) == 'd' || c == 'D')
	if ((c = fgetc(source)) == 'r' || c == 'R')
	  if ((c = fgetc(source)) == '+')
	    fprintf(dump, "adr%c", fgetc(source));
	  else
	    fprintf(dump, "adr%c", c);
    }
    else if (c == 'j' || c == 'J') { //needs to fix the caps for all including the actual operand
      if ((c = fgetc(source)) == 'm' || c == 'M')
	if ((c = fgetc(source)) == 'p' || c == 'P') {
	  if ((c = fgetc(source)) == '+')
	    c = fgetc(source);
	  if (c == 'r' || c == 'R')
	    fprintf(dump, "jmpr");
	  else if (c == 'i' || c == 'I')
	    fprintf(dump, "jmpi");
	}
    }
    else if (c == 'b' || c == 'B') {
      if ((c = fgetc(source)) == 'u' || c == 'U')
	if ((c = fgetc(source)) == 'f' || c == 'F')
	  if ((c = fgetc(source)) == '+')
	    fprintf(dump, "buf%c", fgetc(source));
	  else
	    fprintf(dump, "buf%c", c);
    }
    else if (c == 'o' || c == 'O') {
      if ((c = fgetc(source)) == 'u' || c == 'U')
	if ((c = fgetc(source)) == 't' || c == 'T')
	  if ((c = fgetc(source)) == '+')
	    fprintf(dump, "out%c", fgetc(source));
	  else
	    fprintf(dump, "out%c", c);
    }
    else if (c == '/') {
      while ((c = fgetc(source)) != '\n')
	1;
      fprintf(dump, "\n");
    }
    else if (c == EOF)
      break;
  }
  fclose(source);
  fclose(dump);
}
