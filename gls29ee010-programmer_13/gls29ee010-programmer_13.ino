//use arduino MEGA

#define ADR 22
#define DATA 40
#define WE 50
#define OE 51
#define CE 52
//data and adr are the 0th pins, counting up increments them on the chip

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
  digitalWrite(OE, LOW);
  pinMode(CE, OUTPUT);
  digitalWrite(CE, HIGH);

  for (i = 0; i < 17; i++)
    pinMode(ADR+i, OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(DATA+i, OUTPUT);
    
  setadr(0x5555);
  digitalWrite(OE, HIGH);
  digitalWrite(CE, LOW);
  digitalWrite(WE, LOW);
  setval(0xAA);
  delayMicroseconds(1);
  setadr(0x2AAA);
  digitalWrite(WE, HIGH);
  setval(0x55);
  digitalWrite(WE, LOW);
  delayMicroseconds(1);
  setadr(0x5555);
  digitalWrite(WE, HIGH);
  setval(0x90);
  digitalWrite(WE, LOW);
  delayMicroseconds(1);
  digitalWrite(WE, HIGH);
  digitalWrite(CE, HIGH);
  for (i = 0; i < 8; i++)
    pinMode(DATA+i, INPUT);
  delayMicroseconds(15);
  digitalWrite(CE, LOW);
  digitalWrite(OE, LOW);

  show(0);
  show(1);
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

  digitalWrite(WE, HIGH);
  for (i = 0; i < 17; i++)
    digitalWrite(ADR+i, LOW);
  for (i = 0; i < 17; i++)
    if (a & (1 << i))
      digitalWrite(ADR+i, HIGH);
  digitalWrite(WE, LOW);
  for (i = 0; i < 8; i++)
    digitalWrite(DATA+i, LOW);
  for (i = 0; i < 8; i++)
    if (v & (1 << i))
      digitalWrite(DATA+i, HIGH);
  digitalWrite(WE, HIGH);
}

void show(long a)
{
  long i;
  int val;

  for (i = 0; i < 17; i++)
    digitalWrite(ADR+i, LOW);
  for (i = 0; i < 17; i++)
    if (a & (1 << i))
      digitalWrite(ADR+i, HIGH);

  for (val = 0, i = 0; i < 8; i++)
    if (digitalRead(DATA+i))
      val += (1 << i);

  Serial.println(val);
}

void loop() {}
