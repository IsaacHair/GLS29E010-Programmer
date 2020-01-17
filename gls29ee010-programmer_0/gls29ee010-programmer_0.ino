//use arduino MEGA
//with the indentation on the chip facing left
//attatch pins 22 thru 53 on the arduino in increasing order to the pins on the eeprom
//going left to right across the top
//then left to right across the bottom

int adr[17] = {49, 48, 47, 46, 45, 44, 43, 42,  27, 28, 31, 29, 41, 26, /*25*/23, 40,  39};
int data[8] = {50, 51, 52, 37, 36, 35, 34, 33};
#define VDD 22
#define VSS 53
#define WE /*23*/ 25
/**/#define CE2 24
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
  pinMode(VDD, OUTPUT);
  digitalWrite(VDD, HIGH);
  pinMode(WE, OUTPUT);
  digitalWrite(WE, HIGH);
  pinMode(OE, OUTPUT);
  digitalWrite(OE, HIGH);
  pinMode(CE2, OUTPUT);
  digitalWrite(CE2, HIGH);
  pinMode(CE, OUTPUT);
  digitalWrite(CE, LOW);
  pinMode(VSS, OUTPUT);
  digitalWrite(VSS, LOW);

  for (i = 0; i < 17; i++) //writing phase
    pinMode(adr[i], OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(data[i], OUTPUT);
    
  def(0x5555, 0xAA);
  def(0x2AAA, 0x55);
  def(0x5555, 0xA0);
  def(0, 47);
  def(1, 55);
  def(2, 6);
  def(3, 244);
  
  for (i = 0; i < 17; i++) //reading phase
    pinMode(adr[i], OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(data[i], INPUT);
    
  for (i = 0x5555; i < 0x5556; i++) {
    sprintf(buff, "%d", ret(i));
    Serial.println(buff);
  }
}

void def(long a, int v)
{
  sprintf(buff, "%ld: %d", a, v);
  Serial.println(buff);
  
  long i;
  for (i = 0; i < 17; i++, a /= 2)
    if (a % 2)
      digitalWrite(adr[i], HIGH);
    else
      digitalWrite(adr[i], LOW);
  for (i = 0; i < 8; i++, v /= 2) //display data
    if (v % 2)
      digitalWrite(data[i], HIGH);
    else
      digitalWrite(data[i], LOW);
  //write
  digitalWrite(WE, LOW);
  delayMicroseconds(20);
  digitalWrite(WE, HIGH);
  delayMicroseconds(20);
}

int ret(long a)
{
  long i;
  int val;
  digitalWrite(OE, LOW);
  delayMicroseconds(20);
  for (i = 0; i < 17; i++, a /= 2) //display address
    if (a % 2)
      digitalWrite(adr[i], HIGH);
    else
      digitalWrite(adr[i], LOW);
  for (i = 0, val = 0; i < 8; i++) //if the the data pin is one, make that bit in val one as well
    if (digitalRead(data[i]))
      val += (1 << i);
  digitalWrite(OE, HIGH);
  delayMicroseconds(20);
  return (val);
}

void loop() {}
