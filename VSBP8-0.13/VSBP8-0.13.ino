#define ADR 22
#define DATA 40
#define WE 50
#define OE 51
#define CE 52

char buff[200];

#define LEN 500
long prog[LEN] = {0x0000, 0x00, 0x01, 0x40, 0x01, 0x60, 0x06, -1, 0x0080, 0x00, 0x01, 0x01, 0x01, 0x40, 0x01, 0x44, 0x01, 0x48, 0x01, 0x4c, 0x01, -1, 0x0100, 0x00, 0x07, 0x60, 0x06, -1, 0x0180, 0x40, 0x05, 0x44, 0x05, 0x48, 0x05, -1, 0x0200, 0x00, 0x05, 0x40, 0x07, 0x60, 0x06, -1, 0x0280, 0x01, 0x06, 0x40, 0x06, 0x44, 0x06, 0x48, 0x06, -1, 0x0380, 0x40, 0x03, 0x44, 0x03, 0x48, 0x03, -1, 0x0400, 0x00, 0x05, 0x40, 0x05, 0x60, 0x06, -1, 0x0480, 0x00, 0x05, 0x01, 0x05, 0x40, 0x05, 0x44, 0x05, 0x48, 0x05, 0x4c, 0x05, -1, 0x0500, 0x00, 0x01, 0x60, 0x06, -1, 0x0580, 0x40, 0x03, 0x44, 0x03, 0x48, 0x03, -1, 0x0600, 0x00, 0x07, 0x40, 0x03, 0x60, 0x06, -1, 0x0680, 0x01, 0x06, 0x40, 0x06, 0x44, 0x06, 0x48, 0x06, -1, 0x0780, 0x40, 0x01, 0x44, 0x01, 0x48, 0x01, -1, 0x0800, 0x00, 0x07, 0x40, 0x04, 0x60, 0x06, -1, 0x0880, 0x00, 0x03, 0x01, 0x04, 0x40, 0x04, 0x44, 0x04, 0x48, 0x04, -1, 0x0900, 0x00, 0x05, 0x60, 0x06, -1, 0x0980, 0x40, 0x01, 0x44, 0x01, 0x48, 0x01, -1, -2};

void setup() {
  Serial.begin(115200);
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
  check();
}

void page()
{
  long i, j;
  int pagehere;
  long pagen;
  long count;
  for (i = 0, count = 0, pagehere = 1; i < LEN;) {
    if (prog[i] == -2)
      break;
    else if (pagehere) {
      def(0x5555, 0xAA);
      def(0x2AAA, 0x55);
      def(0x5555, 0xA0);
      pagen = prog[i];
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
      count++;
      def(pagen+prog[i], prog[i+1]);
      i += 2;
    }
  }
  Serial.print("wrote:");
  Serial.println(count);
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
  delayMicroseconds(5);
  for (val = 0, i = 0; i < 8; i++)
    if (digitalRead(DATA+i))
      val += (1 << i);
  digitalWrite(OE, HIGH);
  return (val);
}

void check()
{
  long i, j;
  long pagen;
  int pagehere;
  long err;
  for (i = 0, err = 0, pagehere = 1; i < LEN;) {
    if (prog[i] == -2)
      break;
    else if (pagehere) {
      pagen = prog[i];
      pagehere = 0;
      i++;
    }
    else if (prog[i] == -1) {
      pagehere = 1;
      i++;
    }
    else {
      if (!(show(pagen+prog[i]) == prog[i+1]))
        err++;
      i += 2;
    }
  }
  Serial.print("errors:");
  Serial.println(err);
  Serial.flush();
}

void loop() {}
