//use arduino MEGA
//with the indentation on the chip facing left
//attatch pins 22 thru 53 on the arduino in increasing order to the pins on the eeprom
//going left to right across the top
//then left to right across the bottom

int adr[17] = {49, 48, 47, 46, 45, 44, 43, 42,  27, 28, 31, 29, 41, 26, 23, 40,  39};
int data[8] = {50, 51, 52, 37, 36, 35, 34, 33};
#define WE 25
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

  for (i = 0; i < 17; i++)
    pinMode(adr[i], OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(data[i], OUTPUT);
/*  def(0x5555, 0xAA);
  def(0x2AAA, 0x55);
  def(0x5555, 0xA0);
  def(0x5555, 0xAA);
  def(0x2AAA, 0x55);
  def(0x5555, 0x20);
*/  
  def(0, 0);
  for (i = 0; i < 16; i++)
    pagedef(0, 0);
  pagedef(1, 1);
  pagedef(2, 2);
  pagedef(3, 5);
  delay(200);

  for (i = 0; i < 17; i++)
    pinMode(adr[i], OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(data[i], INPUT);

  digitalWrite(OE, LOW);
  for (i = 0; i < 4; i++) {
    sprintf(buff, "%d", ret(i));
    Serial.println(buff);
  }
  digitalWrite(OE, HIGH);
}

void def(long a, int v)
{
  sprintf(buff, "%ld: %d", a, v);
  Serial.println(buff);
  
  long i;
  for (i = 0; i < 17; i++)
    if ((int) (a/pow(2, i)) % 2)
      digitalWrite(adr[i], HIGH);
    else
      digitalWrite(adr[i], LOW);
  digitalWrite(WE, LOW);
  for (i = 0; i < 8; i++) //display data
    if ((int) (v/pow(2, i)) % 2)
      digitalWrite(data[i], HIGH);
    else
      digitalWrite(data[i], LOW);
  digitalWrite(WE, HIGH);
}

void pagedef(long a, int v)
{
  sprintf(buff, "%ld: %d", a, v);
  Serial.println(buff);
  
  long i;
  for (i = 0; i < 7; i++)
    if ((int) (a/pow(2, i)) % 2)
      digitalWrite(adr[i], HIGH);
    else
      digitalWrite(adr[i], LOW);
  for (i = 0; i < 8; i++) //display data
    if ((int) (v/pow(2, i)) % 2)
      digitalWrite(data[i], HIGH);
    else
      digitalWrite(data[i], LOW);
  digitalWrite(WE, LOW);
  delayMicroseconds(10);
  digitalWrite(WE, HIGH);
  delayMicroseconds(10);
}

int ret(long a)
{
  long i;
  int val;
  for (i = 0; i < 17; i++) //display address
    if ((int) (a/pow(2, i)) % 2)
      digitalWrite(adr[i], HIGH);
    else
      digitalWrite(adr[i], LOW);
  delayMicroseconds(10);
  for (i = 0, val = 0; i < 8; i++) //if the the data pin is one, make that bit in val one as well
    if (digitalRead(data[i]))
      val += (1 << i);
  return (val);
}

void loop() {}
