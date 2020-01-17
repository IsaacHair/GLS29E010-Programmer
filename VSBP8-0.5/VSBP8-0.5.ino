#define ADR 22
#define DATA 40
#define WE 50
#define OE 51
#define CE 52

char buff[200];

long prog[128][2];

long example[10][2] = 
{
  {0x00, 46},
  {0x01, 55},
  {0x02, 3},
  {0x03, 11},
  {0x04, 12},
  {0x05, 17},
  {0x06, 69},
  {0x07, 1},
  {0x08, 2},
  {0x09, 49}
};

void setup() {
  Serial.begin(9600);
  while(!Serial)
    delay(10);
  int i;
  int len;
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
  len = 10;
  for (i = 0; i < 10; i++) {
    prog[i][0] = example[i][0];
    prog[i][1] = example[i][1];
  }
  page(len);

  for (i = 0; i < 8; i++)
    pinMode(DATA+i, INPUT);
  for (i = 0; i < len; i++, Serial.print(buff))
    sprintf(buff, "adr:%ld value:%d expected:%d\n",
            prog[i][0], show(prog[i][0]), prog[i][1]);
  Serial.println(show(0x1500));
}

void page(int len)
{
  long i;
  def(0x15555, 0xAA);
  def(0x12AAA, 0x55);
  def(0x15555, 0xA0);
  for (i = 0; i < len; i++)
    def(prog[i][0], prog[i][1]);
  digitalWrite(WE, HIGH);
  delay(20);
  def(0x15555, 0xAA);
  def(0x12AAA, 0x55);
  def(0x15555, 0xA0);
  def(0x1500, 44);
  digitalWrite(WE, HIGH);
  delay(20);
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
  setadr(a);
  digitalWrite(WE, HIGH);
  delayMicroseconds(5);
  digitalWrite(WE, LOW);
  setval(v);
}

int show(long a)
{
  long i;
  int val;
  digitalWrite(OE, LOW);
  setadr(a);
  for (val = 0, i = 0; i < 8; i++)
    if (digitalRead(DATA+i))
      val += (1 << i);
  digitalWrite(OE, HIGH);
  return (val);
}

void loop() {}
