//use arduino MEGA

#define ADR 22
#define DATA 40
#define WE 50
#define OE 51
#define CE 52
//data and adr are the 0th pins, counting up increments them on the chip
//lsb is pin 0 for both adr and data

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
    pinMode(ADR+i, OUTPUT);
  for (i = 0; i < 8; i++)
    pinMode(DATA+i, OUTPUT);

  /* def(0x5555, 0xAA);
  def(0x2AAA, 0x55);
  def(0x5555, 0xA0);
  delay(20);

  def(0x5555, 0xAA);
  def(0x2AAA, 0x55);
  def(0x5555, 0xA0);
  for (i = 0; i < 16; i++);
    def(0, 0xff);
  def(0, 2+136);
  digitalWrite(WE, HIGH);
  delay(200);

  def(0x5555, 0xAA);
  def(0x2AAA, 0x55);
  def(0x5555, 0xA0);
  for (i = 0; i < 16; i++)
    def(8192+1024, 0xff);
  def(8192+1024, 2+144);
  digitalWrite(WE, HIGH);
  delay(200);

  def(0x5555, 0xAA);
  def(0x2AAA, 0x55);
  def(0x5555, 0xA0);
  for (i = 0; i < 16; i++)
    def(8192+2048, 0xff);
  def(8192+2048, 6+152);
  digitalWrite(WE, HIGH);
  delay(200);

  def(0x5555, 0xAA);
  def(0x2AAA, 0x55);
  def(0x5555, 0xA0);
  for (i = 0; i < 16; i++)
    def(8192+3072, 0xff);
  def(8192+3072, 6+0);
  digitalWrite(WE, HIGH);
  delay(200);*/

  for (i = 0; i < 8; i++)
    pinMode(DATA+i, INPUT);

  show(0);
  show(8192+1024);
  show(8192+2048);
  show(8192+3072);
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
  digitalWrite(WE, LOW);
  for (i = 0; i < 8; i++)
    digitalWrite(DATA+i, LOW);
  for (i = 0; i < 8; i++)
    if (v & (1 << i))
      digitalWrite(DATA+i, HIGH);
}

void show(long a)
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

  Serial.println(val);
}

void loop() {}
