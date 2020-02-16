#include <stdlib.h>
#include <stdio.h>

//first arg is the source file, second is the target file
//third arg is the first buffer file, fourth is the other buffer file
//buffer files can be used to examine progress, but they are basically garbage
void main(int argc, char* argv[]) {
  FILE *source = fopen(argv[1], "r");
  FILE *target = fopen(argv[2], "w");
  FILE *clean = fopen(argv[3], "w+");
  FILE *mapped = fopen(argv[4], "w+");

  vsbclean(source, clean);
  vsbmap(clean, mapped);
  vsbpage(mapped, target);

  fclose(source);
  fclose(target);
  fclose(clean);
  fclose(mapped);
}

void vsbclean(FILE *source, FILE *clean) {
  char c;
  int i;
  for (c = fgetc(source); c != EOF; c = fgetc(source))
    if (c == '/')
      while ((c = fgetc(source)) != '\n')
	1;
    else if (c >= '0' && c <= '9') {
      for (i = 0; i < 4; i++, c = fgetc(source))
	fprintf(clean, "%c", c);
      c = fgetc(source);
      fgetc(source);
      fgetc(source);
      switch (c) {
      case 'j':
	if ((c = fgetc(source)) == 'i')
	  fprintf(clean, "00");
	else
	  fprintf(clean, "20");
	break;
      case 'o':
	if ((c = fgetc(source)) == '0')
	  fprintf(clean, "40");
	else
	  fprintf(clean, "60");
	break;
      case 'a':
	if ((c = fgetc(source)) == '0')
	  fprintf(clean, "80");
	else
	  fprintf(clean, "a0");
	break;
      case 'b':
	if ((c = fgetc(source)) == '0')
	  fprintf(clean, "c0");
	else
	  fprintf(clean, "e0");
	break;
      }
      c = fgetc(source);
      for (i = 0; i < 4; i++)
	fprintf(clean, "%c", (c = fgetc(source)));
      c = fgetc(source);
      for (i = 0; i < 4; i++)
	fprintf(clean, "%c", (c = fgetc(source)));
    }
}
      

void vsbmap(FILE *clean, FILE *mapped) {
  int i;
  for (c = fgetc(clean); c != EOF; c = fgetc(clean)) {
    1;}
}

void vsbpage(FILE *mapped, FILE *target) {
  1;
}
