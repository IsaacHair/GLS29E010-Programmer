//use arduino MEGA

#define ADR 22
#define DATA 40
#define WE 50
#define OE 51
#define CE 52
//data and adr are the 0th pins, counting up increments them on the chip

char buff[200];

#define JMP 0
#define OUT 2
#define ADR 4
#define BUF 6
#define I 0
#define R 1

#define TRUE 1
#define FALSE 0

//only programs the first 32 bits since no page overlaps
//trying to program past this will erase the first data value in that page
//not set up yet

#define LEN 10 //get correct
#define CHIP 0 
long prog[LEN][6] = 
{
  {0x00, B01100000, 0xff, 0xff, 0x00, 0x01},
  {0x01, B01000000, 0xff, 0xff, 0x00, 0x02},
  {0x02, B10100000, 0xff, 0xff, 0x00, 0x03},
  {0x03, B10000000, 0xff, 0xff, 0x00, 0x04},
  {0x04, B00000000, 0x00, 0x01, 0x00, 0x05},
  {0x05, B11100000, 0x00, 0x00, 0x00, 0x06},
  {0x06, B00100000, 0x00, 0x00, 0x00, 0x07},
  {0x07, B11000000, 0x00, 0x00, 0x00, 0x09},
  {0x09, B00100000, 0x00, 0x00, 0x00, 0x09},
  {0x08, B01000000, 0x00, 0x00, 0x00, 0x00}
};

void setup() {
  //setup
  Serial.begin(9600);
  while(!Serial)
    delay(10);
  long i;
  long err;
  for (i = 22; i <= 53; i++)
    pinMode(i, INPUT);
  pinMode(WE, OUTPUT);
  digitalWrite(WE, HIGH);
  pinMode(OE, OUTPUT);
  digitalWrite(OE, HIGH);
  pinMode(CE, OUTPUT);
  digitalWrite(CE, LOW);

  for (i = 0; i < 17; i++)
    pinMode(ADR+i, OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(DATA+i, OUTPUT);

  def(0x15555, 0xAA);
  def(0x12AAA, 0x55);
  def(0x15555, 0xA0);
  delay(20);

  for (i = 0; i < LEN; i++)
    page(i);

  for (i = 0; i < 8; i++)
    pinMode(DATA+i, INPUT);

  for (i = 0, err = 0; i < LEN; i++) {
    Serial.print("adr:");
    Serial.print(map32(prog[i][0]));
    Serial.print(" value:");
    Serial.print(show(map32(prog[i][0])));
    Serial.print(" expected:");
    Serial.print(pmalign(prog[i][CHIP+1]));
    Serial.print("\n");
    if (show(map32(prog[i][0])) != pmalign(prog[i][CHIP+1]))
      err++;
  }
  Serial.print("errors:");
  Serial.print(err);
  Serial.print("\n\n");
}

void page(long p)
{
  long i;
  def(0x15555, 0xAA);
  def(0x12AAA, 0x55);
  def(0x15555, 0xA0);
  def(map32(prog[p][0]), pmalign(prog[p][CHIP+1]));
  digitalWrite(WE, HIGH);
  delay(20);
}

int pmalign(long v)
{
  int ret;
  ret = 0;
  if (v & (1 << 0))
    ret += (1 << 3);
  if (v & (1 << 1))
    ret += (1 << 4);
  if (v & (1 << 2))
    ret += (1 << 5);
  if (v & (1 << 3))
    ret += (1 << 6);
  if (v & (1 << 4))
    ret += (1 << 7);
  if (v & (1 << 5))
    ret += (1 << 2);
  if (v & (1 << 6))
    ret += (1 << 1);
  if (v & (1 << 7))
    ret += (1 << 0);
  return (ret);
}

long map32(long pa)
{
  long ba;

  ba = 0;
  if (pa & (1 << 0))
    ba += (1 << 10);
  if (pa & (1 << 1))
    ba += (1 << 11);
  if (pa & (1 << 2))
    ba += (1 << 9);
  if (pa & (1 << 3))
    ba += (1 << 8);
  if (pa & (1 << 4))
    ba += (1 << 13);
  if (pa & (1 << 5))
    ba += (1 << 14);

  return (ba);
}

void setadr(long a)
{
  long i;

  for (i = 0; i < 17; i++)
    digitalWrite(ADR+i, LOW);
  for (i = 0; i < 17; i++)
    if (a & (1 << i))
      digitalWrite(ADR+i, HIGH);
}

void setval(int v)
{
  long i;
  
  for (i = 0; i < 8; i++)
    digitalWrite(DATA+i, LOW);
  for (i = 0; i < 8; i++)
    if (v & (1 << i))
      digitalWrite(DATA+i, HIGH);
}

void def(long a, int v)
{
  long i;

  for (i = 0; i < 17; i++)
    digitalWrite(ADR+i, LOW);
  for (i = 0; i < 17; i++)
    if (a & (1 << i))
      digitalWrite(ADR+i, HIGH);
  digitalWrite(WE, HIGH);
  delayMicroseconds(5);
  digitalWrite(WE, LOW);
  for (i = 0; i < 8; i++)
    digitalWrite(DATA+i, LOW);
  for (i = 0; i < 8; i++)
    if (v & (1 << i))
      digitalWrite(DATA+i, HIGH);
}

int show(long a)
{
  long i;
  int val;

  digitalWrite(OE, LOW);
  
  for (i = 0; i < 17; i++)
    digitalWrite(ADR+i, LOW);
  for (i = 0; i < 17; i++)
    if (a & (1 << i))
      digitalWrite(ADR+i, HIGH);

  for (val = 0, i = 0; i < 8; i++)
    if (digitalRead(DATA+i))
      val += (1 << i);

  digitalWrite(OE, HIGH);

  return(val);
}

void loop() {}
