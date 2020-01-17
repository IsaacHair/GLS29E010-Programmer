//use arduino MEGA

#define ADR 22
#define DATA 40
#define WE 50
#define OE 51
#define CE 52
//data and adr are the 0th pins, counting up increments them on the chip

#define JMP 0
#define OUT 2
#define ADR 4
#define BUF 6
#define I 0
#define R 1

//only programs the first 32 bits since no page overlaps
//trying to program past this will erase the first data value in that page
//not set up yet

//using msb of prog[x][1] as msb of address; leave at zero for zero in address
//note: this has not been implemented yet, merely able to do this
//using bit one less than msb of prog[x][1] as the flag to indicate whether
//it has been written or not
//note: it is a long, not an int

#define LEN 10 //get correct
#define CHIP 0
int prog[LEN][4] = 
{
  {0x0000, B011, 0xffff, 0x0001},
  {0x0001, B010, 0xffff, 0x0002},
  {0x0002, B101, 0xffff, 0x0003},
  {0x0003, B100, 0xffff, 0x0004},
  {0x0004, B000, 0x0001, 0x0005},
  {0x0005, B111, 0x0000, 0x0006},
  {0x0006, B001, 0x0000, 0x0007},
  {0x0007, B110, 0x0000, 0x0009},
  {0x0009, B001, 0x0000, 0x0009},
  {0x0008, B010, 0x0000, 0x0000}
};

#define FALSE 0
#define TRUE 1

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
  
  for (i = 0; i < LEN; i++)
    setflag(i, FALSE);

  for (i = 0; i < 17; i++)
    pinMode(ADR+i, OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(DATA+i, OUTPUT);

  for (i = 0; i < LEN; i++)
    page(i);

  for (i = 0; i < 8; i++)
    pinMode(DATA+i, INPUT);

  for (i = 0, err = 0; i < LEN; i++) {
    Serial.print("adr:");
    Serial.print(mapp(prog[i][0]));
    Serial.print(" value:");
    Serial.print(show(mapp(prog[i][0])));
    Serial.print(" expected:");
    Serial.print(pmalign(progval(i)));
    Serial.print("\n");
    if (show(mapp(prog[i][0])) != pmalign(progval(i)))
      err++;
  }
  Serial.print("err:");
  Serial.print(err);
}

byte progval(long p)
{  
  return (prog[p][(CHIP+1)/2+1]
      /(CHIP%2 ? 256 : 1)*(CHIP == 0 ? (1 << 5) : 1));
}

bool adr17(long p)
{
  return (prog[p][1] & (1 << 15));
}

bool flag(long p)
{
  return (prog[p][1] & (1 << 14));
}

void setflag(long p, bool v)
{
  prog[p][1] &= B10111111*256 + B11111111;
  if (v)
    prog[p][1] += (1 << 14);
}

bool page(long p)
{
  long i;
  def(0x15555, 0xAA);
  def(0x12AAA, 0x55);
  def(0x15555, 0xA0);
  def(mapp(prog[p][0]), pmalign(progval(p)));
  digitalWrite(WE, HIGH);
  delay(20);
  return (0);
}

byte pmalign(byte v)
{
  byte ret;
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

long mapp(long pa)
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
  if (pa & (1 << 6))
    ba += (1 << 0);
  if (pa & (1 << 7))
    ba += (1 << 1);
  if (pa & (1 << 8))
    ba += (1 << 2);
  if (pa & (1 << 9))
    ba += (1 << 3);
  if (pa & (1 << 10))
    ba += (1 << 4);
  if (pa & (1 << 11))
    ba += (1 << 5);
  if (pa & (1 << 12))
    ba += (1 << 6);
  if (pa & (1 << 13))
    ba += (1 << 7);
  if (pa & (1 << 14))
    ba += (1 << 12);
  if (pa & (1 << 15))
    ba += (1 << 15);
  if (pa & (1 << 16))
    ba += (1 << 16);
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

void setval(byte v)
{
  long i;
  
  for (i = 0; i < 8; i++)
    digitalWrite(DATA+i, LOW);
  for (i = 0; i < 8; i++)
    if (v & (1 << i))
      digitalWrite(DATA+i, HIGH);
}

void def(long a, byte v)
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

  Serial.print("OUT:");
  Serial.print(a);
  Serial.print("stores ");
  Serial.print(v);
  Serial.print("\n");
}

byte show(long a)
{
  long i;
  byte val;

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
  delayMicroseconds(5);

  return(val);
}

void loop() {}
