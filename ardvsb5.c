#include <stdlib.h>
#include <stdio.h>

//takes arduino vsb list assembly
//converts it to normal vsb assembly
//first file is source, second file is the destination
//simply removes the brackets, commas, etc
//changes comments to one slash but still retains their content
//retains blank lines

void main(int argc, char* argv[]) {
  FILE *source = fopen(argv[1], "r");
  FILE *dump = fopen(argv[2], "w");
  char c;
  int num;
  while ((c = fgetc(source)) != '0')
    1;
  for (num = 0; c != EOF; c = fgetc(source))
    if (c >= '0' && c <= '9')
      if (num == 0)
	num = 1;
      else
	fprintf(dump, "%c", c);
    else if ((c >= 'a' && c <= 'z') && c != 'x') {
      num = 1;
      fprintf(dump, "%c", c);
    }
    else if (c >= 'A' && c <= 'Z') {
      num = 1;
      fprintf(dump, "%c", c+'a'-'A');
    }
    else if (c == ' ') {
      num = 0;
      fprintf(dump, " ");
    }
    else if (c == '\n') {
      while ((c = fgetc(source)) != '0')
	if (c == '\n')
	  fprintf(dump, "\n");
      num = 1;
      fprintf(dump, "\n");
    }
    else if (c == '/') {
      while ((c = fgetc(source)) != '\n')
	fprintf(dump, "%c", c);
      while ((c = fgetc(source)) != '0')
        if (c == '\n')
	  fprintf(dump, "\n");
	else if (c == '/') {
	  fprintf(dump, "\n");
	  while ((c = fgetc(source)) != '\n')
	    fprintf(dump, "%c", c);
	}
      num = 1;
      fprintf(dump, "\n");
    }
  fclose(source);
  fclose(dump);
}
