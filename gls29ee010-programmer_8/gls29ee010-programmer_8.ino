//use arduino MEGA
//with the indentation on the chip facing left
//attatch pins 22 thru 53 on the arduino in increasing order to the pins on the eeprom
//going left to right across the top
//then left to right across the bottom

int adr[17] = {49, 48, 47, 46, 45, 44, 43, 42,  27, 28, 31, 29, 41, 26, 25, 40,  39};
int data[8] = {50, 51, 52, 37, 36, 35, 34, 33};
#define WE 23
#define OE 30
#define CE 32
//assuming A0 on datasheet is the lsd and A16 is the msd
//assuming DQ0 on datasheet is the lsd and DQ7 is the msd
//here, adr[0] is the lsd and adr[16] is the msd
//direct mapping from datasheet to pins
//data is direct mapped as well

char buff[200];

void setup() {
  //setup
  Serial.begin(9600);
  while(!Serial)
    delay(10);
  long i;
  for (i = 22; i <= 53; i++)
    pinMode(i, INPUT);
  pinMode(WE, OUTPUT);
  digitalWrite(WE, HIGH);
  pinMode(OE, OUTPUT);
  digitalWrite(OE, HIGH);
  pinMode(CE, OUTPUT);
  digitalWrite(CE, LOW);
  pinMode(24, OUTPUT);
  digitalWrite(24, HIGH);

  for (i = 0; i < 17; i++)
    pinMode(adr[i], OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(data[i], OUTPUT);
  insert(0x5555, 0xAA);
  insert(0x2AAA, 0x55);
  insert(0x5555, 0xA0);
  insert(0, 0x55);
  insert(1, 0xAA);
  delay(20);

  for (i = 0; i < 8; i++)
    pinMode(data[i], INPUT);
  pull(0);
  pull(1);
}

void pull(long a)
{
  digitalWrite(OE, LOW);
  setadr(a);
  delayMicroseconds(10);
  Serial.println(getval());
  digitalWrite(OE, HIGH);
  delayMicroseconds(10);
}

void insert(long a, int v)
{
  setadr(a);
  setval(v);
  delayMicroseconds(10);
  digitalWrite(WE, LOW);
  delayMicroseconds(10);
  digitalWrite(WE, HIGH);
}

void setadr(long a)
{
  int i;
  for (i = 0; i < 17; i++)
    digitalWrite(adr[i], LOW);
  for (i = 0; i < 17; i++)
    if ((a >> i)%2)
      digitalWrite(adr[i], HIGH);
}

void setval(int v)
{
  int i;
  for (i = 0; i < 8; i++)
    digitalWrite(data[i], LOW);
  for (i = 0; i < 8; i++)
    if ((v >> i)%2)
      digitalWrite(data[i], HIGH);
}

int getval()
{
  int i;
  int ret;
  for (i = 0, ret = 0; i < 8; i++)
    if (digitalRead(data[i]))
      ret += (1 << i);
  return(ret);
}

void loop() {}
