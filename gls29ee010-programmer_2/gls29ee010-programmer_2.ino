//use arduino MEGA
//with the indentation on the chip facing left
//attatch pins 22 thru 53 on the arduino in increasing order to the pins on the eeprom
//going left to right across the top
//then left to right across the bottom

int adr[17] = {49, 48, 47, 46, 45, 44, 43, 42,  27, 28, 31, 29, 41, 26, 23/**/, 40,  39};
int data[8] = {50, 51, 52, 37, 36, 35, 34, 33};
#define VDD 22
#define VSS 53
#define WE 25/**/
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
  pinMode(CE, OUTPUT);
  digitalWrite(CE, LOW);
  pinMode(VSS, OUTPUT);
  digitalWrite(VSS, LOW);
  pinMode(24, OUTPUT);
  digitalWrite(24, HIGH);

  for (i = 0; i < 17; i++) //writing phase
    pinMode(adr[i], OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(data[i], OUTPUT);

  for (i = 0; i < 17; i++)
    digitalWrite(adr[i], LOW);
  for (i = 8; i < 8; i++)
    digitalWrite(data[i], LOW);
  digitalWrite(data[1], HIGH);
  digitalWrite(WE, HIGH);
  delay(1);
  digitalWrite(WE, LOW);
  delay(1);
  digitalWrite(WE, HIGH);

  digitalWrite(adr[0], HIGH);
  digitalWrite(data[5], HIGH);
  digitalWrite(WE, HIGH);
  delay(1);
  digitalWrite(WE, LOW);
  delay(1);
  digitalWrite(WE, HIGH);

  delay(20);
  
  for (i = 0; i < 17; i++) //reading phase
    pinMode(adr[i], OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(data[i], INPUT);
    
  for (i = 0; i < 2; i++) {
    sprintf(buff, "%d", ret(i));
    Serial.println(buff);
  }
}

void def(long a, int v)
{
  sprintf(buff, "%ld: %d", a, v);
  Serial.println(buff);
  
  long i;
  digitalWrite(WE, HIGH);
  delay(1);
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
  //write
  digitalWrite(WE, LOW);
  delay(1);
  digitalWrite(WE, HIGH);
  delay(1);
}

int ret(long a)
{
  long i;
  int val;
  digitalWrite(OE, HIGH);
  delay(1);
  digitalWrite(OE, LOW);
  delay(1);
  for (i = 0; i < 17; i++) //display address
    if ((int) (a/pow(2, i)) % 2)
      digitalWrite(adr[i], HIGH);
    else
      digitalWrite(adr[i], LOW);
  for (i = 0, val = 0; i < 8; i++) //if the the data pin is one, make that bit in val one as well
    if (digitalRead(data[i]))
      val += (1 << i);
  digitalWrite(OE, HIGH);
  delay(1);
  return (val);
}

void loop() {}
