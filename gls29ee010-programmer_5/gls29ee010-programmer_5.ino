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
  Serial.begin(9600);
  while(!Serial)
    delay(10);
  long i;
  for (i = 22; i <= 53; i++) //setup
    pinMode(i, INPUT);
  pinMode(WE, OUTPUT);
  digitalWrite(WE, HIGH);
  pinMode(OE, OUTPUT);
  digitalWrite(OE, HIGH);
  pinMode(CE, OUTPUT);
  digitalWrite(CE, LOW);
  
  for (i = 0; i < 17; i++) //writing phase
    pinMode(adr[i], OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(data[i], OUTPUT);

  digitalWrite(WE, LOW);
  def(0x5555, 0xAA);
  next();
  def(0x2AAA, 0x55);
  next();
  def(0x5555, 0xA0);
  next();
  for (i = 0; i < 16; i++) {
    def(0, 0xFF);
    next();
  }
  def(0, 234);
  next();
  def(1, 83);
  next();
  def(2, 8);
  next();
  def(3, 127);
  next();
  digitalWrite(WE, HIGH);
  delay(20);
  
  for (i = 0; i < 17; i++) //reading phase
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

void next()
{
  digitalWrite(WE, HIGH);
  digitalWrite(WE, LOW);
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
  for (i = 0; i < 8; i++) //display data
    if ((int) (v/pow(2, i)) % 2)
      digitalWrite(data[i], HIGH);
    else
      digitalWrite(data[i], LOW);
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
  delay(1);
  for (i = 0, val = 0; i < 8; i++) //if the the data pin is one, make that bit in val one as well
    if (digitalRead(data[i]))
      val += (1 << i);
  return (val);
}

void loop() {}
