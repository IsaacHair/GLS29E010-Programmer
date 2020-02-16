#include <stdlib.h>
#include <stdio.h>

char buff[5][512][129][2];
//chip number, page number, line number, line address and data
//note: line address 128 stores the overall page address
//it needs 2 bytes

void main(int argc, char* argv[]) {
  FILE *source = fopen(argv[1], "r");
  FILE *dump = fopen(argv[2], "w");

  
