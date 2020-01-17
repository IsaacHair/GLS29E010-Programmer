 #define LEN 65 //********make sure to get length correct
 #define JMP 0
 #define OUT 2
 #define ADR 4
 #define BUF 6
 #define I 0
 #define R 1
uint16_t prog[LEN][4]={
    {0x0000, ADR+0, 0xffff, 0x0001}, //reset
    {0x0001, ADR+1, 0x0000, 0x0002},
    {0x0002, BUF+0, 0x0000, 0x0003},

    {0x0003, ADR+0, 0xffff, 0x0004},
    {0x0004, ADR+1, 0x0001, 0x0005},
    {0x0005, BUF+0, 0x0000, 0x0006},
    
    {0x0006, ADR+0, 0xffff, 0x0007},
    {0x0007, ADR+1, 0x0002, 0x0008},
    {0x0008, BUF+0, 0x0000, 0x0009},

    {0x0009, ADR+0, 0xffff, 0x000a},
    {0x000a, ADR+1, 0x0003, 0x000b},
    {0x000b, BUF+0, 0x0000, 0x0010},

    {0x0010, OUT+0, 0xfff0, 0x1000}, //fix output

    {0x1000, ADR+0, 0xffff, 0x1001}, //add 1
    {0x1001, ADR+1, 0x0000, 0x1002},
    {0x1002, JMP+R, 0x0000, 0x1004},
    {0x1004, BUF+1, 0x0000, 0x1f00},
    {0x1005, BUF+0, 0x0000, 0x1010},

    {0x1010, ADR+0, 0xffff, 0x1011},
    {0x1011, ADR+1, 0x0001, 0x1012},
    {0x1012, JMP+R, 0x0000, 0x1014},
    {0x1014, BUF+1, 0x0000, 0x1f04},
    {0x1015, BUF+0, 0x0000, 0x1020},

    {0x1020, ADR+0, 0xffff, 0x1021},
    {0x1021, ADR+1, 0x0002, 0x1022},
    {0x1022, JMP+R, 0x0000, 0x1024},
    {0x1024, BUF+1, 0x0000, 0x1f08},
    {0x1025, BUF+0, 0x0000, 0x1030},

    {0x1030, ADR+0, 0xffff, 0x1031},
    {0x1031, ADR+1, 0x0003, 0x1032},
    {0x1032, JMP+R, 0x0000, 0x1034},
    {0x1034, BUF+1, 0x0000, 0x2000},
    {0x1035, BUF+0, 0x0000, 0x2000},

    {0x1f00, OUT+1, 0x0000, 0x1f01}, //equalize clock cycles spent to add
    {0x1f01, OUT+1, 0x0000, 0x1f02},
    {0x1f02, OUT+1, 0x0000, 0x1f03},
    {0x1f03, OUT+1, 0x0000, 0x1f04},
    
    {0x1f04, OUT+1, 0x0000, 0x1f05},
    {0x1f05, OUT+1, 0x0000, 0x1f06},
    {0x1f06, OUT+1, 0x0000, 0x1f07},
    {0x1f07, OUT+1, 0x0000, 0x1f08},
    
    {0x1f08, OUT+1, 0x0000, 0x1f09},
    {0x1f09, OUT+1, 0x0000, 0x1f0a},
    {0x1f0a, OUT+1, 0x0000, 0x1f0b},
    {0x1f0b, OUT+1, 0x0000, 0x2000},

    {0x2000, ADR+0, 0xffff, 0x2001}, //print
    {0x2001, ADR+1, 0x0000, 0x2002},
    {0x2002, JMP+R, 0x0000, 0x2004},
    {0x2004, OUT+0, 0x0001, 0x2010},
    {0x2005, OUT+1, 0x0001, 0x2010},

    {0x2010, ADR+0, 0xffff, 0x2011},
    {0x2011, ADR+1, 0x0001, 0x2012},
    {0x2012, JMP+R, 0x0000, 0x2014},
    {0x2014, OUT+0, 0x0002, 0x2020},
    {0x2015, OUT+1, 0x0002, 0x2020},

    {0x2020, ADR+0, 0xffff, 0x2021},
    {0x2021, ADR+1, 0x0002, 0x2022},
    {0x2022, JMP+R, 0x0000, 0x2024},
    {0x2024, OUT+0, 0x0004, 0x2030},
    {0x2025, OUT+1, 0x0004, 0x2030},

    {0x2030, ADR+0, 0xffff, 0x2031},
    {0x2031, ADR+1, 0x0003, 0x2032},
    {0x2032, JMP+R, 0x0000, 0x2034},
    {0x2034, OUT+0, 0x0008, 0x1000},
    {0x2035, OUT+1, 0x0008, 0x1000},
    };


void setup() {
  int i, j;

  for (i = 0; i < 54; i++)
    pinMode(i, OUTPUT);

  digitalWrite(52, HIGH);
  digitalWrite(53, HIGH);
  
  for (i = 0; i < 160; i++, delay(25)) //4 second delay to reset
    if (i%2)
      digitalWrite(19, HIGH);
    else
      digitalWrite(19, LOW);

  for (i = 0; i < LEN; i++) { //write instructions
    for (j = 0; j < 52; j++) //resetting pins
      digitalWrite(j, LOW);

    for (j = 0; j < 16; j++) //current address
      if ((int) (prog[i][0]/pow(2, 15-j)) % 2)
        digitalWrite(51-j*2, HIGH);

    for (j = 35; j < 51; j++) //next address
      if ((int) (prog[i][3]/pow(2, 50-j)) % 2)
        digitalWrite(120-j*2, HIGH);

    for (j = 16; j < 19; j++) //operation code
      if ((int) (prog[i][1]/pow(2, 18-j)) % 2)
        digitalWrite(j, HIGH);

    for (j = 19; j < 35; j++) //operand
      if ((int) (prog[i][2]/pow(2, 34-j)) % 2)
        digitalWrite(j-19, HIGH);

    delay(1);
    digitalWrite(52, LOW);
    delay(1);
    digitalWrite(52, HIGH);
    delay(1);
  }

  digitalWrite(52, HIGH);
  digitalWrite(53, LOW);

  for (i = 0; i < 52; i++)
    pinMode(i, INPUT);
}

void loop() {

}
