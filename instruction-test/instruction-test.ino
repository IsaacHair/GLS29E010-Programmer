 #define LEN 2 //********make sure to get length correct
 #define JMP 0
 #define OUT 2
 #define ADR 4
 #define BUF 6
 #define I 0
 #define R 1
uint16_t prog[LEN][4]={
    {0x0000, JMP+I, 0x0001, 0x0000},
    {0x0001, OUT+0, 0xffff, 0x0001},
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
