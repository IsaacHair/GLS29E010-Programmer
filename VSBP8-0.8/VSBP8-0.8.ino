#define ADR 22
#define DATA 40
#define WE 50
#define OE 51
#define CE 52

char buff[200];

#define LEN 1140
long prog[LEN] = {0x0000, 0x00, 0x08, 0x40, 0x08, 0x60, 0x08, -1, 0x0080, 0x00, 0x08, 0x01, 0x0a, 0x40, 0x08, 0x44, 0x08, 0x48, 0x08, 0x4c, 0x08, -1, 0x0100, 0x00, 0x48, 0x60, 0x48, -1, 0x0180, 0x40, 0x48, 0x44, 0x48, 0x48, 0x48, -1, 0x0200, 0x00, 0x28, 0x40, 0x00, 0x60, 0x28, -1, 0x0280, 0x01, 0x00, 0x40, 0x30, 0x44, 0x30, 0x48, 0x30, -1, 0x0380, 0x40, 0x04, 0x44, 0x84, 0x48, 0x02, -1, 0x0400, 0x00, 0x10, 0x40, 0x10, 0x60, 0x10, -1, 0x0480, 0x00, 0x10, 0x01, 0x12, 0x40, 0x10, 0x44, 0x10, 0x48, 0x10, 0x4c, 0x00, -1, 0x0500, 0x00, 0x50, 0x60, 0x50, -1, 0x0580, 0x40, 0x50, 0x44, 0x50, 0x48, 0x50, -1, 0x0600, 0x00, 0x30, 0x40, 0x80, 0x60, 0x30, -1, 0x0680, 0x01, 0x00, 0x40, 0x68, 0x44, 0x68, 0x48, 0x68, -1, 0x0780, 0x40, 0x70, 0x44, 0x70, 0x48, 0x70, -1, 0x0800, 0x00, 0x18, 0x40, 0x20, 0x60, 0x18, -1, 0x0880, 0x00, 0x80, 0x01, 0x22, 0x40, 0x20, 0x44, 0x20, 0x48, 0x20, -1, 0x0900, 0x00, 0x58, 0x60, 0x58, -1, 0x0980, 0x40, 0x58, 0x44, 0x58, 0x48, 0x58, -1, 0x0a00, 0x00, 0x38, 0x60, 0x38, -1, 0x0a80, 0x40, 0x38, 0x44, 0x38, 0x48, 0x38, -1, 0x0b80, 0x40, 0x78, 0x44, 0x78, 0x48, 0x78, -1, 0x0c00, 0x00, 0x20, 0x60, 0x20, -1, 0x0d00, 0x00, 0x00, 0x60, 0x00, -1, 0x0d80, 0x40, 0x60, 0x44, 0x60, 0x48, 0x60, -1, 0x0e00, 0x00, 0x40, 0x60, 0x40, -1, 0x0e80, 0x40, 0x40, 0x44, 0x40, 0x48, 0x40, -1, 0x0f80, 0x40, 0x80, 0x44, 0x80, 0x48, 0x80, -1, 0x1000, 0x00, 0x08, 0x04, 0x08, 0x08, 0x08, 0x0c, 0x08, 0x40, 0x10, 0x44, 0x08, 0x45, 0x0a, 0x46, 0x09, 0x47, 0x0b, 0x50, 0x00, 0x48, 0x08, 0x49, 0x0a, 0x4a, 0x09, 0x4b, 0x0b, 0x60, 0x00, -1, 0x1080, 0x00, 0x08, 0x04, 0x08, 0x08, 0x08, 0x1c, 0x08, 0x20, 0x08, -1, 0x1100, 0x00, 0x48, 0x04, 0x48, 0x08, 0x48, 0x50, 0x00, 0x60, 0x00, -1, 0x1180, 0x00, 0x80, 0x20, 0x48, -1, 0x1200, 0x00, 0x30, 0x04, 0x30, 0x08, 0x30, 0x40, 0x00, 0x44, 0x80, 0x45, 0x81, 0x46, 0x10, 0x47, 0x50, 0x50, 0x00, 0x48, 0x80, 0x49, 0x81, 0x4a, 0x10, 0x4b, 0x50, 0x60, 0x00, -1, 0x1280, 0x00, 0x28, 0x04, 0x00, 0x08, 0x28, 0x1c, 0x00, 0x20, 0x28, -1, 0x1300, 0x00, 0x04, 0x04, 0x84, 0x08, 0x02, 0x50, 0x00, 0x60, 0x00, -1, 0x1400, 0x00, 0x10, 0x04, 0x10, 0x08, 0x10, 0x0c, 0x00, 0x44, 0x10, 0x45, 0x12, 0x46, 0x11, 0x47, 0x13, 0x50, 0x00, 0x48, 0x10, 0x49, 0x12, 0x4a, 0x11, 0x4b, 0x13, 0x60, 0x00, -1, 0x1480, 0x00, 0x10, 0x04, 0x10, 0x08, 0x10, 0x1c, 0x10, 0x20, 0x10, -1, 0x1500, 0x00, 0x50, 0x04, 0x50, 0x08, 0x50, 0x50, 0x00, 0x60, 0x00, -1, 0x1580, 0x20, 0x50, -1, 0x1600, 0x00, 0x68, 0x04, 0x68, 0x08, 0x68, 0x40, 0x30, 0x44, 0x04, 0x45, 0x05, 0x46, 0x18, 0x47, 0x58, 0x50, 0x00, 0x48, 0x04, 0x49, 0x05, 0x4a, 0x18, 0x4b, 0x58, 0x60, 0x00, -1, 0x1680, 0x00, 0x30, 0x04, 0x80, 0x08, 0x30, 0x1c, 0x80, 0x20, 0x30, -1, 0x1700, 0x00, 0x70, 0x04, 0x70, 0x08, 0x70, 0x50, 0x00, 0x60, 0x00, -1, 0x1800, 0x00, 0x20, 0x04, 0x20, 0x08, 0x20, 0x40, 0x20, 0x44, 0x20, 0x45, 0x22, 0x46, 0x21, 0x47, 0x23, 0x50, 0x00, 0x48, 0x20, 0x49, 0x22, 0x4a, 0x21, 0x4b, 0x23, 0x60, 0x00, -1, 0x1880, 0x00, 0x18, 0x04, 0x20, 0x08, 0x18, 0x1c, 0x20, 0x20, 0x18, -1, 0x1900, 0x00, 0x58, 0x04, 0x58, 0x08, 0x58, 0x50, 0x00, 0x60, 0x00, -1, 0x1980, 0x20, 0x58, -1, 0x1a00, 0x00, 0x38, 0x04, 0x38, 0x08, 0x38, 0x40, 0x00, 0x50, 0x00, 0x60, 0x00, -1, 0x1a80, 0x00, 0x38, 0x08, 0x38, 0x20, 0x38, -1, 0x1b00, 0x00, 0x78, 0x04, 0x78, 0x08, 0x78, 0x50, 0x00, 0x60, 0x00, -1, 0x1c00, 0x40, 0x28, 0x50, 0x00, 0x60, 0x00, -1, 0x1c80, 0x00, 0x20, 0x08, 0x20, 0x20, 0x20, -1, 0x1d00, 0x00, 0x60, 0x04, 0x60, 0x08, 0x60, 0x50, 0x00, 0x60, 0x00, -1, 0x1d80, 0x20, 0x00, -1, 0x1e00, 0x00, 0x40, 0x04, 0x40, 0x08, 0x40, 0x40, 0x00, 0x50, 0x00, 0x60, 0x00, -1, 0x1e80, 0x00, 0x40, 0x08, 0x00, 0x20, 0x40, -1, 0x1f00, 0x00, 0x80, 0x04, 0x80, 0x08, 0x80, 0x50, 0x00, 0x60, 0x00, -1, 0x2000, 0x40, 0x88, -1, 0x2080, 0x00, 0x88, 0x40, 0x00, 0x44, 0x00, 0x48, 0x00, -1, 0x2200, 0x40, 0x20, -1, 0x2280, 0x00, 0x00, -1, 0x2400, 0x40, 0x90, -1, 0x2480, 0x00, 0x90, 0x40, 0x00, 0x44, 0x00, 0x48, 0x00, -1, 0x2600, 0x40, 0x04, -1, 0x2680, 0x00, 0x00, -1, 0x2800, 0x40, 0xa0, -1, 0x2880, 0x00, 0xa0, -1, 0x3000, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x44, 0x88, 0x45, 0x8a, 0x46, 0x89, 0x47, 0x8b, 0x48, 0x88, 0x49, 0x8a, 0x4a, 0x89, 0x4b, 0x8b, -1, 0x3080, 0x00, 0x88, 0x04, 0x88, 0x1c, 0x88, -1, 0x3180, 0x00, 0xc8, -1, 0x3200, 0x44, 0x84, 0x45, 0x85, 0x46, 0x20, 0x47, 0x60, 0x48, 0x84, 0x49, 0x85, 0x4a, 0x20, 0x4b, 0x60, -1, 0x3280, 0x00, 0xa8, 0x04, 0x20, 0x1c, 0x20, -1, 0x3380, 0x00, 0xe8, -1, 0x3400, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x44, 0x90, 0x45, 0x92, 0x46, 0x91, 0x47, 0x93, 0x48, 0x90, 0x49, 0x92, 0x4a, 0x91, 0x4b, 0x93, -1, 0x3480, 0x00, 0x90, 0x04, 0x90, 0x1c, 0x90, -1, 0x3580, 0x00, 0xd0, -1, 0x3600, 0x44, 0x02, 0x45, 0x03, 0x46, 0x28, 0x47, 0x68, 0x48, 0x02, 0x49, 0x03, 0x4a, 0x28, 0x4b, 0x68, -1, 0x3680, 0x00, 0xb0, 0x04, 0x04, 0x1c, 0x04, -1, 0x3780, 0x00, 0xf0, -1, 0x3800, 0x44, 0xa0, 0x45, 0xa2, 0x46, 0xa1, 0x47, 0xa3, 0x48, 0xa0, 0x49, 0xa2, 0x4a, 0xa1, 0x4b, 0xa3, -1, 0x3880, 0x00, 0x98, 0x04, 0xa0, 0x1c, 0xa0, -1, 0x3980, 0x00, 0xd8, -1, 0x3a80, 0x00, 0xb8, -1, 0x3b80, 0x00, 0xf8, -1, 0x3c80, 0x00, 0xa0, -1, 0x3d80, 0x00, 0xe0, -1, 0x3e80, 0x00, 0xc0, -1, 0x3f80, 0x00, 0x04, -1, 0x4000, 0x40, 0x0c, -1, 0x4080, 0x00, 0x0c, -1, 0x4200, 0x40, 0x40, -1, 0x4280, 0x00, 0x00, -1, 0x4400, 0x40, 0x14, -1, 0x4480, 0x00, 0x14, -1, 0x4600, 0x40, 0x84, -1, 0x4680, 0x00, 0x00, -1, 0x4800, 0x40, 0x24, -1, 0x4880, 0x00, 0x24, -1, 0x5000, 0x44, 0x0c, 0x45, 0x0e, 0x46, 0x0d, 0x47, 0x0f, 0x48, 0x0c, 0x49, 0x0e, 0x4a, 0x0d, 0x4b, 0x0f, -1, 0x5080, 0x00, 0x0c, 0x04, 0x0c, 0x1c, 0x0c, -1, 0x5200, 0x44, 0x82, 0x45, 0x83, 0x46, 0x30, 0x47, 0x70, 0x48, 0x82, 0x49, 0x83, 0x4a, 0x30, 0x4b, 0x70, -1, 0x5280, 0x04, 0x00, 0x1c, 0x40, -1, 0x5400, 0x44, 0x14, 0x45, 0x16, 0x46, 0x15, 0x47, 0x17, 0x48, 0x14, 0x49, 0x16, 0x4a, 0x15, 0x4b, 0x17, -1, 0x5480, 0x00, 0x00, 0x04, 0x14, 0x1c, 0x14, -1, 0x5600, 0x44, 0x06, 0x45, 0x07, 0x46, 0x38, 0x47, 0x78, 0x48, 0x06, 0x49, 0x07, 0x4a, 0x38, 0x4b, 0x78, -1, 0x5680, 0x04, 0x00, 0x1c, 0x84, -1, 0x5800, 0x44, 0x24, 0x45, 0x26, 0x46, 0x25, 0x47, 0x27, 0x48, 0x24, 0x49, 0x26, 0x4a, 0x25, 0x4b, 0x27, -1, 0x5880, 0x04, 0x24, 0x1c, 0x24, -1, 0x6000, 0x40, 0x8c, -1, 0x6080, 0x00, 0x8c, -1, 0x6200, 0x40, 0x00, -1, 0x6280, 0x00, 0x00, -1, 0x6400, 0x40, 0x94, -1, 0x6480, 0x00, 0x94, -1, 0x6600, 0x40, 0x00, -1, 0x6680, 0x00, 0x00, -1, 0x6800, 0x40, 0xa4, -1, 0x6880, 0x00, 0xa4, -1, 0x7000, 0x44, 0x8c, 0x45, 0x8e, 0x46, 0x8d, 0x48, 0x8c, 0x49, 0x8e, 0x4a, 0x8d, -1, 0x7080, 0x1c, 0x8c, -1, 0x7200, 0x44, 0x86, 0x45, 0x00, 0x46, 0x40, 0x48, 0x86, 0x49, 0x00, 0x4a, 0x40, -1, 0x7280, 0x1c, 0x00, -1, 0x7400, 0x44, 0x94, 0x45, 0x96, 0x46, 0x95, 0x48, 0x94, 0x49, 0x96, 0x4a, 0x95, -1, 0x7480, 0x1c, 0x94, -1, 0x7600, 0x44, 0x01, 0x45, 0x08, 0x46, 0x48, 0x48, 0x01, 0x49, 0x08, 0x4a, 0x48, -1, 0x7680, 0x1c, 0x00, -1, 0x7800, 0x44, 0xa4, 0x45, 0xa6, 0x46, 0xa5, 0x48, 0xa4, 0x49, 0xa6, 0x4a, 0xa5, -1, 0x7880, 0x1c, 0xa4, -1};

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
  Serial.println(show(0x0080)); //should be 0x08
  Serial.println(show(0x0560)); //should be 0x50
}

void page()
{
  long i, j;
  int pagehere;
  long page;
  for (i = 0, pagehere = 1; i < LEN; i++) {
    if (pagehere) {
      def(0x5555, 0xAA);
      def(0x2AAA, 0x55);
      def(0x5555, 0xA0);
      page = prog[i];
      pagehere = 0;
      continue;
    }
    else if (prog[i] == -1) {
      pagehere = 1;
      digitalWrite(WE, HIGH);
      delay(20);
      continue;
    }
    else {
      def(page+prog[i], prog[i+1]);
      i++;
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
