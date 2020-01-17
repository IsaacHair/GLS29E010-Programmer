 #define LEN 8
uint16_t prog[LEN][4]={ //ram: 0000-0001 = index of pointer; 0100-0102 = counting flags; 0103 = carry flag; 0200-0203 = pointer; 0300-030F = number incremented
                        //program: 00XX -> reset each incrementation; 01XX -> increment index of pointer; 02XX -> increment pointer based on index; 03XX -> increment and print number
    {0x0000, B100, 0xFFFF, 0xff01}, //reset each incrementation
    {0xff01, B010, 0xFFFF, 0xff02},
    {0xff02, B101, 0xFFFF, 0xff03},
    {0xff03, B011, 0xFFFF, 0xff04},
    {0xff04, B010, 0x0000, 0xff05},
    {0xff05, B100, 0x0000, 0xff06},
    {0xff06, B011, 0x0000, 0xff07},
    {0xff07, B101, 0x0000, 0x0000}
    };


void setup() {
  int i, j;

  for (i = 0; i < 54; i++)
    pinMode(i, OUTPUT);

  digitalWrite(52, HIGH);
  digitalWrite(53, HIGH);
  
  for (i = 0; i < 160; i++, delay(25))
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
