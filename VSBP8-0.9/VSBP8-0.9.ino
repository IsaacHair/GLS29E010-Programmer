#define ADR 22
#define DATA 40
#define WE 50
#define OE 51
#define CE 52

char buff[200];

#define LEN 28
long prog[LEN] = {0x0000, 0x00, 0x08, 0x40, 0x08, 0x60, 0x08, -1, 0x0080, 0x00, 0x08, 0x01, 0x0a, 0x40, 0x08, 0x44, 0x08, 0x48, 0x08, 0x4c, 0x08, -1, 0x0100, 0x00, 0x48, 0x60, 0x48, -1};

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
  page();

  for (i = 0; i < 8; i++)
    pinMode(DATA+i, INPUT);
  Serial.println(show(0x0000)); //should be 0x08
  Serial.println(show(128)); //should be 0x50
}

void page()
{
  long i, j;
  int pagehere;
  long page;
  for (i = 0, pagehere = 1; i < LEN;) {
    if (pagehere) {
      def(0x5555, 0xAA);
      def(0x2AAA, 0x55);
      def(0x5555, 0xA0);
      page = prog[i];
      Serial.print("page:");
      Serial.println(page);
      pagehere = 0;
      i++;
    }
    else if (prog[i] == -1) {
      pagehere = 1;
      digitalWrite(WE, HIGH);
      delay(20);
      i++;
    }
    else {
      def(page+prog[i], prog[i+1]);
      Serial.print(page+prog[i]);
      Serial.print(":");
      Serial.print(prog[i+1]);
      Serial.print(" i:");
      Serial.println(i);
      i += 2;
    }
  }
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
