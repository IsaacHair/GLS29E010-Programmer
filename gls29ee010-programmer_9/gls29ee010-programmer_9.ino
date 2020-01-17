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
  digitalWrite(OE, HIGH);
  pinMode(CE, OUTPUT);
  digitalWrite(CE, LOW);
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);

  for (i = 0; i < 17; i++)
    pinMode(ADR+i, OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(DATA+i, OUTPUT);
    
  /*def(0x5555, 0xAA);
  def(0x2AAA, 0x55);
  def(0x5555, 0xA0);
  for (i = 0; i < 16; i++)
    def(0, 0xff);
  for (i = 0; i < 16; i++)
    def(i, i);
  delay(20);*/

  def(0x5555, 0xAA);
  def(0x2AAA, 0x55);
  def(0x5555, 0xA0);
  def(0x5555, 0xAA);
  def(0x2AAA, 0x55);
  def(0x5555, 0x20);
  for (i = 0; i < 16; i++)
    def(128, 0xff);
  for (i = 0; i < 16; i++)
    def(128+i, 250-i);
  delay(20);

  for (i = 0; i < 17; i++)
    pinMode(ADR+i, OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(DATA+i, INPUT);
    
  for (i = 0; i < 16; i++)
    show(0+i);
  Serial.println(" ");
  for (i = 0; i < 16; i++)
    show(0+i);
}

void def(long a, int v)
{
  long i;

  for (i = 0; i < 17; i++)
    digitalWrite(ADR+i, LOW);
  for (i = 0; i < 17; i++)
    if (a & (1 << i))
      digitalWrite(ADR+i, HIGH);
  for (i = 0; i < 8; i++)
    digitalWrite(DATA+i, LOW);
  for (i = 0; i < 8; i++)
    if (v & (1 << i))
      digitalWrite(DATA+i, HIGH);

  delayMicroseconds(5);
  digitalWrite(WE, LOW);
  delayMicroseconds(5);
  digitalWrite(WE, HIGH);
  delayMicroseconds(5);
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

  delayMicroseconds(5);
  digitalWrite(OE, LOW);
  delayMicroseconds(5);

  for (val = 0, i = 0; i < 8; i++)
    if (digitalRead(DATA+i))
      val += (1 << i);

  Serial.println(val);

  delayMicroseconds(5);
  digitalWrite(OE, HIGH);
  delayMicroseconds(5);
}

void loop() {}
