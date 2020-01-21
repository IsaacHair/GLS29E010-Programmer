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
long example[1141] = {0x0000, 0x00, 0x01, 0x40, 0x01, 0x60, 0x06, -1, 0x0080, 0x00, 0x01, 0x01, 0x01, 0x40, 0x01, 0x44, 0x01, 0x48, 0x01, 0x4c, 0x01, -1, 0x0100, 0x00, 0x07, 0x60, 0x06, -1, 0x0180, 0x40, 0x05, 0x44, 0x05, 0x48, 0x05, -1, 0x0200, 0x00, 0x05, 0x40, 0x07, 0x60, 0x06, -1, 0x0280, 0x01, 0x06, 0x40, 0x06, 0x44, 0x06, 0x48, 0x06, -1, 0x0380, 0x40, 0x03, 0x44, 0x03, 0x48, 0x03, -1, 0x0400, 0x00, 0x05, 0x40, 0x05, 0x60, 0x06, -1, 0x0480, 0x00, 0x05, 0x01, 0x05, 0x40, 0x05, 0x44, 0x05, 0x48, 0x05, 0x4c, 0x05, -1, 0x0500, 0x00, 0x01, 0x60, 0x06, -1, 0x0580, 0x40, 0x03, 0x44, 0x03, 0x48, 0x03, -1, 0x0600, 0x00, 0x07, 0x40, 0x03, 0x60, 0x06, -1, 0x0680, 0x01, 0x06, 0x40, 0x06, 0x44, 0x06, 0x48, 0x06, -1, 0x0780, 0x40, 0x01, 0x44, 0x01, 0x48, 0x01, -1, 0x0800, 0x00, 0x07, 0x40, 0x04, 0x60, 0x06, -1, 0x0880, 0x00, 0x03, 0x01, 0x04, 0x40, 0x04, 0x44, 0x04, 0x48, 0x04, -1, 0x0900, 0x00, 0x05, 0x60, 0x06, -1, 0x0980, 0x40, 0x01, 0x44, 0x01, 0x48, 0x01, -1, 0x0a00, 0x00, 0x01, 0x60, 0x06, -1, 0x0a80, 0x40, 0x07, 0x44, 0x07, 0x48, 0x07, -1, -2};

void setup() {
  int i;
  delay(2500);
  Serial.begin(57600);
  while(!Serial)
    delay(10);
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
    i = errors();
    Serial.print("page:");
    Serial.print(prog.adr);
    Serial.print(" errors:");
    Serial.println(i);
    Serial.flush();
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
    Serial.flush();
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
    Serial.print(readdata());
    Serial.print(" expected:");
    Serial.println(prog.data[j]);
    Serial.flush();
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
