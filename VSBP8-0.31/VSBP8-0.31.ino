#define ADR 22
#define DATA 40
#define WE 50
#define OE 51
#define CE 52

int buff[200];

struct {
  int line[128];
  int data[128];
  int len;
  long adr;
} prog;


long examplec = 0;
long example[1141] = {0x0000, 0x00, 0x01, 0x40, 0x01, 0x60, 0x06, -1, 0x0080, 0x00, 0x01, 0x01, 0x01, 0x40, 0x01, 0x44, 0x01, 0x48, 0x01, 0x4c, 0x01, -1, 0x0100, 0x00, 0x07, 0x60, 0x06, -1, 0x0180, 0x40, 0x05, 0x44, 0x05, 0x48, 0x05, -1, 0x0200, 0x00, 0x05, 0x40, 0x07, 0x60, 0x06, -1, 0x0280, 0x01, 0x06, 0x40, 0x06, 0x44, 0x06, 0x48, 0x06, -1, 0x0380, 0x40, 0x03, 0x44, 0x03, 0x48, 0x03, -1, 0x0400, 0x00, 0x05, 0x40, 0x05, 0x60, 0x06, -1, 0x0480, 0x00, 0x05, 0x01, 0x05, 0x40, 0x05, 0x44, 0x05, 0x48, 0x05, 0x4c, 0x05, -1, 0x0500, 0x00, 0x01, 0x60, 0x06, -1, 0x0580, 0x40, 0x03, 0x44, 0x03, 0x48, 0x03, -1, 0x0600, 0x00, 0x07, 0x40, 0x03, 0x60, 0x06, -1, 0x0680, 0x01, 0x06, 0x40, 0x06, 0x44, 0x06, 0x48, 0x06, -1, 0x0780, 0x40, 0x01, 0x44, 0x01, 0x48, 0x01, -1, 0x0800, 0x00, 0x07, 0x40, 0x04, 0x60, 0x06, -1, 0x0880, 0x00, 0x03, 0x01, 0x04, 0x40, 0x04, 0x44, 0x04, 0x48, 0x04, -1, 0x0900, 0x00, 0x05, 0x60, 0x06, -1, 0x0980, 0x40, 0x01, 0x44, 0x01, 0x48, 0x01, -1, 0x0a00, 0x00, 0x01, 0x60, 0x06, -1, 0x0a80, 0x40, 0x07, 0x44, 0x07, 0x48, 0x07, -1, 0x0b80, 0x40, 0x05, 0x44, 0x05, 0x48, 0x05, -1, 0x0c00, 0x00, 0x01, 0x60, 0x06, -1, 0x0d00, 0x00, 0x07, 0x60, 0x06, -1, 0x0d80, 0x40, 0x05, 0x44, 0x05, 0x48, 0x05, -1, 0x0e00, 0x00, 0x05, 0x60, 0x06, -1, 0x0e80, 0x40, 0x01, 0x44, 0x01, 0x48, 0x01, -1, 0x0f80, 0x40, 0x04, 0x44, 0x04, 0x48, 0x04, -1, 0x1000, 0x00, 0x01, 0x04, 0x01, 0x08, 0x01, 0x0c, 0x01, 0x40, 0x00, 0x44, 0x01, 0x45, 0x01, 0x46, 0x01, 0x47, 0x01, 0x50, 0x02, 0x48, 0x01, 0x49, 0x01, 0x4a, 0x01, 0x4b, 0x01, 0x60, 0x06, -1, 0x1080, 0x00, 0x01, 0x04, 0x01, 0x08, 0x06, 0x1c, 0x01, 0x20, 0x06, -1, 0x1100, 0x00, 0x05, 0x04, 0x05, 0x08, 0x05, 0x50, 0x02, 0x60, 0x06, -1, 0x1180, 0x00, 0x03, 0x20, 0x06, -1, 0x1200, 0x00, 0x06, 0x04, 0x06, 0x08, 0x06, 0x40, 0x03, 0x44, 0x01, 0x45, 0x01, 0x46, 0x01, 0x47, 0x01, 0x50, 0x02, 0x48, 0x01, 0x49, 0x01, 0x4a, 0x01, 0x4b, 0x01, 0x60, 0x06, -1, 0x1280, 0x00, 0x05, 0x04, 0x07, 0x08, 0x06, 0x1c, 0x07, 0x20, 0x06, -1, 0x1300, 0x00, 0x07, 0x04, 0x07, 0x08, 0x07, 0x50, 0x02, 0x60, 0x06, -1, 0x1400, 0x00, 0x05, 0x04, 0x05, 0x08, 0x05, 0x0c, 0x05, 0x44, 0x05, 0x45, 0x05, 0x46, 0x05, 0x47, 0x05, 0x50, 0x02, 0x48, 0x05, 0x49, 0x05, 0x4a, 0x05, 0x4b, 0x05, 0x60, 0x06, -1, 0x1480, 0x00, 0x05, 0x04, 0x05, 0x08, 0x06, 0x1c, 0x05, 0x20, 0x06, -1, 0x1500, 0x00, 0x03, 0x04, 0x03, 0x08, 0x03, 0x50, 0x02, 0x60, 0x06, -1, 0x1580, 0x20, 0x06, -1, 0x1600, 0x00, 0x06, 0x04, 0x06, 0x08, 0x06, 0x40, 0x04, 0x44, 0x01, 0x45, 0x01, 0x46, 0x01, 0x47, 0x01, 0x50, 0x02, 0x48, 0x01, 0x49, 0x01, 0x4a, 0x01, 0x4b, 0x01, 0x60, 0x06, -1, 0x1680, 0x00, 0x03, 0x04, 0x03, 0x08, 0x06, 0x1c, 0x03, 0x20, 0x06, -1, 0x1700, 0x00, 0x01, 0x04, 0x01, 0x08, 0x01, 0x50, 0x02, 0x60, 0x06, -1, 0x1800, 0x00, 0x04, 0x04, 0x04, 0x08, 0x04, 0x40, 0x06, 0x44, 0x04, 0x45, 0x04, 0x46, 0x04, 0x47, 0x04, 0x50, 0x02, 0x48, 0x04, 0x49, 0x04, 0x4a, 0x04, 0x4b, 0x04, 0x60, 0x06, -1, 0x1880, 0x00, 0x03, 0x04, 0x04, 0x08, 0x06, 0x1c, 0x04, 0x20, 0x06, -1, 0x1900, 0x00, 0x01, 0x04, 0x01, 0x08, 0x01, 0x50, 0x02, 0x60, 0x06, -1, 0x1980, 0x20, 0x06, -1, 0x1a00, 0x00, 0x07, 0x04, 0x07, 0x08, 0x07, 0x40, 0x07, 0x50, 0x02, 0x60, 0x06, -1, 0x1a80, 0x00, 0x01, 0x08, 0x06, 0x20, 0x06, -1, 0x1b00, 0x00, 0x05, 0x04, 0x05, 0x08, 0x05, 0x50, 0x02, 0x60, 0x06, -1, 0x1c00, 0x40, 0x06, 0x50, 0x02, 0x60, 0x06, -1, 0x1c80, 0x00, 0x01, 0x08, 0x06, 0x20, 0x06, -1, 0x1d00, 0x00, 0x05, 0x04, 0x05, 0x08, 0x05, 0x50, 0x02, 0x60, 0x06, -1, 0x1d80, 0x20, 0x06, -1, 0x1e00, 0x00, 0x01, 0x04, 0x01, 0x08, 0x01, 0x40, 0x03, 0x50, 0x02, 0x60, 0x06, -1, 0x1e80, 0x00, 0x05, 0x08, 0x06, 0x20, 0x06, -1, 0x1f00, 0x00, 0x04, 0x04, 0x04, 0x08, 0x04, 0x50, 0x02, 0x60, 0x06, -1, 0x2000, 0x40, 0x01, -1, 0x2080, 0x00, 0x01, 0x40, 0x01, 0x44, 0x01, 0x48, 0x01, -1, 0x2200, 0x40, 0x07, -1, 0x2280, 0x00, 0x06, -1, 0x2400, 0x40, 0x05, -1, 0x2480, 0x00, 0x05, 0x40, 0x05, 0x44, 0x05, 0x48, 0x05, -1, 0x2600, 0x40, 0x03, -1, 0x2680, 0x00, 0x06, -1, 0x2800, 0x40, 0x04, -1, 0x2880, 0x00, 0x04, -1, 0x3000, 0x00, 0x01, 0x04, 0x01, 0x08, 0x01, 0x44, 0x01, 0x45, 0x01, 0x46, 0x01, 0x47, 0x01, 0x48, 0x01, 0x49, 0x01, 0x4a, 0x01, 0x4b, 0x01, -1, 0x3080, 0x00, 0x02, 0x04, 0x01, 0x1c, 0x01, -1, 0x3180, 0x00, 0x02, -1, 0x3200, 0x44, 0x01, 0x45, 0x01, 0x46, 0x01, 0x47, 0x01, 0x48, 0x01, 0x49, 0x01, 0x4a, 0x01, 0x4b, 0x01, -1, 0x3280, 0x00, 0x02, 0x04, 0x07, 0x1c, 0x07, -1, 0x3380, 0x00, 0x02, -1, 0x3400, 0x00, 0x05, 0x04, 0x05, 0x08, 0x05, 0x44, 0x05, 0x45, 0x05, 0x46, 0x05, 0x47, 0x05, 0x48, 0x05, 0x49, 0x05, 0x4a, 0x05, 0x4b, 0x05, -1, 0x3480, 0x00, 0x02, 0x04, 0x05, 0x1c, 0x05, -1, 0x3580, 0x00, 0x02, -1, 0x3600, 0x44, 0x01, 0x45, 0x01, 0x46, 0x01, 0x47, 0x01, 0x48, 0x01, 0x49, 0x01, 0x4a, 0x01, 0x4b, 0x01, -1, 0x3680, 0x00, 0x02, 0x04, 0x03, 0x1c, 0x03, -1, 0x3780, 0x00, 0x02, -1, 0x3800, 0x44, 0x04, 0x45, 0x04, 0x46, 0x04, 0x47, 0x04, 0x48, 0x04, 0x49, 0x04, 0x4a, 0x04, 0x4b, 0x04, -1, 0x3880, 0x00, 0x02, 0x04, 0x04, 0x1c, 0x04, -1, 0x3980, 0x00, 0x02, -1, 0x3a80, 0x00, 0x02, -1, 0x3b80, 0x00, 0x02, -1, 0x3c80, 0x00, 0x02, -1, 0x3d80, 0x00, 0x02, -1, 0x3e80, 0x00, 0x02, -1, 0x3f80, 0x00, 0x02, -1, 0x4000, 0x40, 0x01, -1, 0x4080, 0x00, 0x01, -1, 0x4200, 0x40, 0x07, -1, 0x4280, 0x00, 0x06, -1, 0x4400, 0x40, 0x05, -1, 0x4480, 0x00, 0x05, -1, 0x4600, 0x40, 0x03, -1, 0x4680, 0x00, 0x06, -1, 0x4800, 0x40, 0x04, -1, 0x4880, 0x00, 0x04, -1, 0x5000, 0x44, 0x01, 0x45, 0x01, 0x46, 0x01, 0x47, 0x01, 0x48, 0x01, 0x49, 0x01, 0x4a, 0x01, 0x4b, 0x01, -1, 0x5080, 0x00, 0x02, 0x04, 0x01, 0x1c, 0x01, -1, 0x5200, 0x44, 0x01, 0x45, 0x01, 0x46, 0x01, 0x47, 0x01, 0x48, 0x01, 0x49, 0x01, 0x4a, 0x01, 0x4b, 0x01, -1, 0x5280, 0x04, 0x07, 0x1c, 0x07, -1, 0x5400, 0x44, 0x05, 0x45, 0x05, 0x46, 0x05, 0x47, 0x05, 0x48, 0x05, 0x49, 0x05, 0x4a, 0x05, 0x4b, 0x05, -1, 0x5480, 0x00, 0x02, 0x04, 0x05, 0x1c, 0x05, -1, 0x5600, 0x44, 0x01, 0x45, 0x01, 0x46, 0x01, 0x47, 0x01, 0x48, 0x01, 0x49, 0x01, 0x4a, 0x01, 0x4b, 0x01, -1, 0x5680, 0x04, 0x03, 0x1c, 0x03, -1, 0x5800, 0x44, 0x04, 0x45, 0x04, 0x46, 0x04, 0x47, 0x04, 0x48, 0x04, 0x49, 0x04, 0x4a, 0x04, 0x4b, 0x04, -1, 0x5880, 0x04, 0x04, 0x1c, 0x04, -1, 0x6000, 0x40, 0x01, -1, 0x6080, 0x00, 0x01, -1, 0x6200, 0x40, 0x07, -1, 0x6280, 0x00, 0x06, -1, 0x6400, 0x40, 0x05, -1, 0x6480, 0x00, 0x05, -1, 0x6600, 0x40, 0x03, -1, 0x6680, 0x00, 0x06, -1, 0x6800, 0x40, 0x04, -1, 0x6880, 0x00, 0x04, -1, 0x7000, 0x44, 0x01, 0x45, 0x01, 0x46, 0x01, 0x48, 0x01, 0x49, 0x01, 0x4a, 0x01, -1, 0x7080, 0x1c, 0x01, -1, 0x7200, 0x44, 0x01, 0x45, 0x01, 0x46, 0x01, 0x48, 0x01, 0x49, 0x01, 0x4a, 0x01, -1, 0x7280, 0x1c, 0x07, -1, 0x7400, 0x44, 0x05, 0x45, 0x05, 0x46, 0x05, 0x48, 0x05, 0x49, 0x05, 0x4a, 0x05, -1, 0x7480, 0x1c, 0x05, -1, 0x7600, 0x44, 0x01, 0x45, 0x01, 0x46, 0x01, 0x48, 0x01, 0x49, 0x01, 0x4a, 0x01, -1, 0x7680, 0x1c, 0x03, -1, 0x7800, 0x44, 0x04, 0x45, 0x04, 0x46, 0x04, 0x48, 0x04, 0x49, 0x04, 0x4a, 0x04, -1, 0x7880, 0x1c, 0x04, -1, -2};

void setup() {
  Serial.begin(9600);
  while(!Serial)
    delay(10);
  int i;
  pinMode(WE, OUTPUT);
  digitalWrite(WE, HIGH);
  pinMode(OE, OUTPUT);
  digitalWrite(OE, HIGH);
  pinMode(CE, OUTPUT);
  digitalWrite(CE, LOW);
  for (i = 0; i < 17; i++)
    pinMode(ADR+i, OUTPUT);
  
  while (grabpage()) {
    pagewrite();
    if (errors())
      pagewrite();
  }

  grabreset();
  while (grabpage()) {
    Serial.print("page:");
    Serial.print(prog.adr);
    Serial.print(" errors:");
    Serial.println(errors());
  }
}

int grabpage() {
  int i, j;
  i = examplec;
  if (example[i] == -2)
    return (0);
  prog.adr = example[i];
  i++;
  for (j = 0; 1; j++)
    if (example[i] == -1) {
      prog.len = j;
      examplec = i+1;
      return (1);
    }
    else {
      prog.line[j] = example[i];
      prog.data[j] = example[i+1];
      i += 2;
    }
}

void grabreset() {
  examplec = 0;
}

void pagewrite() {
  int j, k;
  int i;
  for (i = 0; i < 8; i++)
    pinMode(DATA+i, OUTPUT);
  digitalWrite(WE, HIGH);
  digitalWrite(OE, HIGH);
  digitalWrite(ADR+15, HIGH);
  digitalWrite(ADR+16, HIGH);
  setcomm(0x5555);
  setdata(0xAA);
  digitalWrite(WE, LOW);
  digitalWrite(WE, HIGH);
  setcomm(0x2AAA);
  setdata(0x55);
  digitalWrite(WE, LOW);
  digitalWrite(WE, HIGH);
  setcomm(0x5555);
  setdata(0xA0);
  digitalWrite(WE, LOW);
  digitalWrite(WE, HIGH);
  setpage(prog.adr);
  for (j = 0; j < prog.len; j++) {
    Serial.print("page:");
    Serial.print(prog.adr);
    Serial.print(" line:");
    Serial.print(prog.line[j]);
    Serial.print(" wrote data:");
    Serial.println(prog.data[j]);
    digitalWrite(WE, HIGH);
    setline(prog.line[j]);
    setdata(prog.data[j]);
    digitalWrite(WE, LOW);
  }
  digitalWrite(WE, HIGH);
  delay(25);
}

void setdata(int data) {
  int k;
  for (k = 0; k < 8; k++)
    if (data & (1 << k))
      digitalWrite(DATA+k, HIGH);
    else
      digitalWrite(DATA+k, LOW);
}

void setpage(long page) {
  int k;
  for (k = 0; k < 17; k++)
    if (page & (1 << k))
      digitalWrite(ADR+k, HIGH);
    else
      digitalWrite(ADR+k, LOW);
}

void setcomm(int comm) {
  int k;
  for (k = 0; k < 15; k++)
    if (comm & (1 << k))
      digitalWrite(ADR+k, HIGH);
    else
      digitalWrite(ADR+k, LOW);
}

void setline(int line) {
  int k;
  for (k = 0; k < 7; k++)
    if (line & (1 << k))
      digitalWrite(ADR+k, HIGH);
    else
      digitalWrite(ADR+k, LOW);
}

int errors() {
  int j;
  int i;
  int err;
  for (i = 0; i < 8; i++)
    pinMode(DATA+i, INPUT);
  digitalWrite(WE, HIGH);
  digitalWrite(OE, LOW);
  setpage(prog.adr);
  for (j = 0, err = 0; j < prog.len; j++) {
    setline(prog.line[j]);
    if (readdata() != prog.data[j])
      err++;
    Serial.print("page:");
    Serial.print(prog.adr);
    Serial.print(" line:");
    Serial.print(prog.line[j]);
    Serial.print(" read data:");
    Serial.println(readdata());
  }
  return (err);
}

int readdata() {
  int k;
  int ret;
  for (k = 0, ret = 0; k < 8; k++)
    if (digitalRead(DATA+k))
      ret += (1 << k);
  return (ret);
}

void loop() {}
